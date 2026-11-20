
/*
 * Copyright 2026 Alex (alex.correu@pm.me)
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

#include "../includes.hpp"
#include "../namespaces.hpp"
#include "accesoArchivos.hpp"           //abrirCrearArchivo()
                                        //cerrarArchivo()
#include "comunicacionServidor.hpp"     //crearSocket()
                                        //aceptarNuevaComunicacion()
#include "comunicacionCliente.hpp"      //conexion()
#include "importsComunicaciones.hpp"



/** enviarArchivoCL()                     18.04.2025   -   Hecho
 * Función CLIENTE que envía un archivoa ( se pasa
 * su ruta como argumento ) través de
 * la red hasta otro ordenador.
 *
 *  ### Deben existir los directorios donde se aloja el archivo
 *
 * Secuencia:  1. Se conecta a servidor
 *             2. Envía el dato
 *             3. Se desconecta.
 *
 * ARG1 -> string, ruta al archivo a enviar ej: "./CarpetaOrigen/unDocumentoCualquiera.txt"
 * RTRN -> int, devuelve 0 si todo ha salido bien.
 */
int enviarArchivoCL(string rutaArchivo)
{
    //Declaraciones
    int res = 1;            //return, se cambia a 0 si todo ha salido bien.
    char buffer[BUFSIZ];    //Bufer para enviar fragmentos del archivo
    int descriptor;         //Descriptor para acceder al archivo a enviar
    int socketLlamada;      //Socket para contactar con el servidor
    bool enviando;          //Condición de final del bucle de envío.
    ssize_t bytesLeidos;    //Cantidad de bytes leidos por read()

    //Abrimos archivo a enviar
    descriptor = abrirCrearArchivo(rutaArchivo);

    //Llamamos al servidor
    conexion(socketLlamada);

    //Bucle de envío
    enviando = true;
    while (enviando)
    {
        //Lee de descriptor y lo pone en bufer
        bytesLeidos                         //Tamaño de bytes escritos, (0 si ya se ha acabado el archivo)
                        = read(descriptor,  //Descriptor del archivo a enviar (origen)
                               buffer,      //Bufer donde almacenar fragmentos(destino)
                               BUFSIZ);     //Tamaño del bufer (bytes máximos copiados de origen a destino)

        if (bytesLeidos == 0)
        {
            //En caso de acabar de leer el archivo terminamos el bucle.
            cout << "Archivo enviado con éxito." << endl;
            res = 0;            //Return de éxito.
            enviando = false;   //Se acaba el bucle.
        }
        else
        {
            //Lee de bufer y lo pone en el socket de envío
            //return: numero de bytes escritos
            write(socketLlamada,        //Socket para contactar con el servidor de recepción (destino)
                  buffer,               //Fragmento que envía al servidor               (origen)
                  bytesLeidos);         //Cantidad de bytes máximos a leer de buffer    (tamaño)
        }
    }

    //Cerrar archivo enviado
    cerrarArchivo(descriptor);

    //Cerrar socket de envío en red
    close(socketLlamada);

    return res;
}



/**  recibirArchivoSV()                    18.04.2025   -   Hecho
 *  Función SERVIDOR que recibe un archivo a través de
 *  la red desde otro ordenador.
 *
 *  ### Deben existir los directorios donde se aloja el archivo
 *
 *  Secuencia:  1. Se pone a escuchar
 *              2. Recibe una conexión
 *              3. Recibe un archivo
 *              4. Se desconecta
 *
 *  ARG1 -> string, ruta donde se desea que se almacene el archivo ej: "./CarpetaDestino/unDocumentoCualquiera(copia).txt"
 *  RTRN -> int, 0 si todo ha ido bien
 */
int recibirArchivoSV(string rutaArchivo)
{
    int res = 1;                //return, se cambiará a 0 si todo ha ido bien.
    ssize_t returnLectura;      //Cantidad de bytes leidos por read()
    char buffer[BUFSIZ];        //Bufer para recibir fragmentos del archivo
    int descriptor;             //Descriptor para almacenar el archivo a recibir
    int soquetEscucha;          //Socket de servidor de escucha
    int socketRespuesta;        //Socket para leer datos del cliente (origen del mensaje)

    //Creamos socket
    soquetEscucha = crearSocket(2);

    //Abrimos archivo a escribir
    descriptor = abrirCrearArchivo(rutaArchivo);

    //Informamos si no se puede abrir el archivo
    if (descriptor == -1)//!descriptor)
        cout << "Algo ha ido mal abriendo archivo" << endl;

    //Esperamos conexión
    socketRespuesta = aceptarNuevaComunicacion(soquetEscucha);

    //Bucle de lectura
    do{
        //Leemos un fragmento del archivo del socket
        returnLectura = read(socketRespuesta,   //Origen de los bytes (red)
                                buffer,         //Destino de los bytes
                                BUFSIZ);        //Bytes máximos a pasar

        //Guardamos el gragmento del archivo del socket
        write(descriptor,       //Destino de los bytes
                buffer,           //Origen de los bytes
                returnLectura);   //Cantidad de bytes máximos
    } while (returnLectura > 0);

    if (returnLectura <= 0)
    {
        res = 0;
        printf("Archivo recibido con éxito.\n");
    }

    //Cerramos archivo
    cerrarArchivo(descriptor);
    //Cerramos sockets comunicación
    close(socketRespuesta);
    //Cerramos sockets escucha
    close(soquetEscucha);
    shutdown(soquetEscucha, SHUT_RDWR);

    return res;
}

/** recibirArchivoSVSocketPropio()                      09.05.2025   -   hecha
 * Misma función que recibirArchivoSV() pero no creas el
 * socket en ella sino que lo recibes por el segundo argumento.
 */
int recibirArchivoSVSocketPropio(string rutaArchivo,int soquetEscucha)
{
    int res = 1;                //return, se cambiará a 0 si todo ha ido bien.
    ssize_t returnLectura;      //Cantidad de bytes leidos por read()
    char buffer[BUFSIZ];        //Bufer para recibir fragmentos del archivo
    int descriptor;             //Descriptor para almacenar el archivo a recibir
    int socketRespuesta;        //Socket para leer datos del cliente (origen del mensaje)

    //Abrimos archivo a escribir
    descriptor = abrirCrearArchivo(rutaArchivo);

    //Informamos si no se puede abrir el archivo
    if (descriptor == -1)//!descriptor)
        cout << "Algo ha ido mal abriendo archivo" << endl;

    //Esperamos conexión
    socketRespuesta = aceptarNuevaComunicacion(soquetEscucha);

    //Bucle de lectura
    do{
        //Leemos un fragmento del archivo del socket
        returnLectura = read(socketRespuesta,   //Origen de los bytes (red)
                                buffer,         //Destino de los bytes
                                BUFSIZ);        //Bytes máximos a pasar

        //Guardamos el gragmento del archivo del socket
        write(descriptor,       //Destino de los bytes
                buffer,           //Origen de los bytes
                returnLectura);   //Cantidad de bytes máximos
    } while (returnLectura > 0);

    if (returnLectura <= 0)
    {
        res = 0;
        printf("Archivo recibido con éxito.\n");
    }

    //Cerramos archivo
    cerrarArchivo(descriptor);
    //Cerramos sockets comunicación
    close(socketRespuesta);
    //Cerramos sockets escucha
//     close(soquetEscucha);
//     shutdown(soquetEscucha, SHUT_RDWR);

    return res;
}
