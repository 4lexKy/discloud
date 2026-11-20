
/*
 * Copyright 2026 Alex (alex.correu@pm.me)
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

/*
███████╗██╗   ██╗███╗   ██╗  ██████╗ ██╗  ██████╗  ███╗   ██╗ ███████╗ ███████╗
██╔════╝██║   ██║████╗  ██║ ██╔════╝ ██║ ██╔═══██╗ ████╗  ██║ ██╔════╝ ██╔════╝
█████╗  ██║   ██║██╔██╗ ██║ ██║      ██║ ██║   ██║ ██╔██╗ ██║ █████╗   ███████╗
██╔══╝  ██║   ██║██║╚██╗██║ ██║      ██║ ██║   ██║ ██║╚██╗██║ ██╔══╝   ╚════██║
██║     ╚██████╔╝██║ ╚████║ ╚██████╗ ██║ ╚██████╔╝ ██║ ╚████║ ███████╗ ███████║
╚═╝      ╚═════╝ ╚═╝  ╚═══╝  ╚═════╝ ╚═╝  ╚═════╝  ╚═╝  ╚═══╝ ╚══════╝ ╚══════╝
*/

// #pragma once        //https://stackoverflow.com/questions/5776910/what-does-pragma-once-mean-in-c

//INCLUDES
#include "importsComunicaciones.hpp"
#include "envrec.hpp"

//DEFINICION DE CONSTANTES
#define PORT 56030          //Puerto de escucha
#define IPsv INADDR_ANY     //IP de escucha del servidor (cualquiera)
#define IPcl "127.0.0.1"    //IP del servidor, para uso del cliente

using namespace std;

//FUNCIONES DE SERVIDOR
//     int crearSocket(int maxConexiones)
//     int aceptarNuevaComunicacion(int socketEscucha)
// void pruebaSockets()
//int escuchaAlCliente(string &palabra)



/**     Crear Socket            ### TERMINADA ###
 * Info: Esta funcion genera todo lo necesario para crear un socket
 *      que se usara para recibir conexiones de clientes, tantas
 *      como el argumento indique. Al terminar esta funcion solo
 *      se debe poner el socket devuelto a esperar conexiones con accept(),
 *      o en este caso la funcion aceptarNuevaComunicacion().
 *
 * ARG1: El numero maximo de conexiones a escuchar, en caso de ser mas se pierden
 * RTRN: Se devuelve el entero que identifica al socket creado.
 *
 * Modificaciones:
 *  -14.06.2024 He anyadido la funcion listen, para no tener que llamar a crear socket desde otra funcion
 */
int crearSocket(int maxConexiones)
{
    //Declarar variables
    int socketEscucha;
    struct sockaddr_in direccionServidor;   //datos de dirección

    //Crear socket escucha (con seguridad por si falla)
    socketEscucha = socket(AF_INET, SOCK_STREAM, 0);
        /**
        * Arg1: AF_INET  - IPv4
        *       AF_INET6 - IPv6
        *       AF_UNIX  - Unix Domain Sockets
        *       AF_UNSPEC- No especificado
        * Arg2: SOCK_STREAM    - Byte-stream socket
        *       SOCK_SEQPACKET - Sequence-packet socket
        *       SOCK_RAW       - Raw protocol interface
        *       SOCK_DGRAM     - Datagram socket
        * Arg3: 0 es protocolo IP
        * info en: https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_socket.h.html
        */

    //Asigno dirección al struct
        //Lleno el variables con '0', 48 en ASCII (evitar basura)
    memset(&direccionServidor, '0', sizeof(direccionServidor));
        /** memset llena de bits en memoria
        * Arg1: Puntero de la variable a rellenar
        * Arg2: Relleno byte a byte, cada byte de la traducción del valor de arg2
        *       Si es un 255 serán todo unos, si es '0' será el valor ASCII de 0.
        * Arg3: Relleno la variable de Arg3 bytes, es decir pongo el valor binario
        *       de Arg2 el número de veces = Arg3. Siempre desde el byte menos significativo.
        * Ejemplo:https://en.cppreference.com/w/cpp/string/byte/memset
        */

        //Asigno dirección del servidor
    direccionServidor.sin_family = AF_INET;         //IPv4      (indico versión del protocolo de internet)
    direccionServidor.sin_addr.s_addr = htonl(IPsv);  //IP        (Añado IP de escucha)
    direccionServidor.sin_port = htons(PORT);       //Puerto    (Añado puerto de escucha)


    //Unimos socket y direccion
    bind(socketEscucha, (struct sockaddr*)&direccionServidor, sizeof(direccionServidor));

    listen(socketEscucha , maxConexiones);

    return socketEscucha;
}

/** Aceptar Nueva Comunicacion   ### TERMINADA ###
 *
 * Info: Esta funcion se pone a la escucha parando el programa hasta
 *      establecer una conexion TCP al socket de escucha pasado como
 *      valor (el unico argumento). Al finalizar devuelve el valor
 *      del socket con el que se ha establecido comunicacion
 *
 * ARG1: Socket de escucha en el que se espera una conexion (pasado como valor)
 * RTRN: Se devuelve el socket del cliente (quien ha establecido conexion)
 *
 * Modificaciones:
 *  -14.04.2024 Hecha la documentacion
 *
 */
int aceptarNuevaComunicacion(int socketEscucha)
{
    //Generamos direccion y datos para aceptar al conexion
    struct sockaddr_in direccionCliente;   //datos de dirección cliente
    int addrlen = sizeof(direccionCliente);

    //Esperamos conexion
    return accept(socketEscucha, (struct sockaddr*)&direccionCliente, (socklen_t*)&addrlen);
}

/** Prueba Socket  ### TERMINADA ###
 * Funcion que demuestra que la conexion con las funciones hechas
 * por mi funcionan y se establece una conexion
 * Se debe llamar a la funcion con el mismo nombre en el cliente
 */
void pruebaSockets()
{
        //Declaracion de Variables
    int socketEscucha;          //Socket escucha, (especifica de quien recibe)
    int socketRespuesta = 0;    //Socket origen de la conexion, para responder
    string palabra;             //Variable para almacenar mensajes (enviar/recibir)



    //Creamos y ponemos el socket a escuchar
    socketEscucha = crearSocket(20);


    //Aceptamos nueva comunicación
    socketRespuesta = aceptarNuevaComunicacion(socketEscucha);


    //Escuchamos Nuevo mensaje
    recibir(socketRespuesta, palabra);     //Leemos entrada de datos
        cout << "\nRecibido:" << endl << "--" << palabra << "--" << endl;


    //Creamos mensaje a enviar
    palabra = "1234567890prueba desde string";


    //Enviamos mensaje
    enviar(socketRespuesta, palabra);
        cout << "\nEnviado:" << endl << "--" << palabra << "--" << endl;


    //Cerramos servidor
    close(socketRespuesta);
    shutdown(socketEscucha, SHUT_RDWR);
        cout << "Socket cerrado" << endl;

    return;
}

/** escuchaAlCliente()              17.04.2025 - hecho
 *
 * Función para recibir datos del cliente, como ping
 * o que necesita información. Siempre corto.
 *  función complementaria: informarAlServidor(string &palabra)
 *
 * Argumento: un string por referencia.
 * Return
 *      0 -> todo ha ido bien.
 */
int escuchaAlCliente(string &palabra)
{
    int res = 1;

    //Declaracion de Variables
    int socketEscucha;          //Socket escucha, (especifica de quien recibe)
    int socketRespuesta = 0;    //Socket origen de la conexion, para responder

    //Creamos y ponemos el socket a escuchar
    socketEscucha = crearSocket(20);
    //Aceptamos nueva comunicación

    socketRespuesta = aceptarNuevaComunicacion(socketEscucha);

    //Escuchamos Nuevo mensaje
    recibir(socketRespuesta, palabra);     //Leemos entrada de datos

    //Enviamos mensaje
    enviar(socketRespuesta, "recibido");

    //Cerramos servidor
    close(socketRespuesta);
    shutdown(socketEscucha, SHUT_RDWR);

    res = 0;

    return res;
}


/** escuchaAlSocketCliente()                    09.05.2025   -   hecha
 * Función que escucha un socket al que contactará un cliente.
 * Para la conexión se ha dar el socket ya creado como argumento
 * devolverá por referencia la información que el cliente haya enviado.
 *
 * ARG1: string &, palabra que se recibe del cliente
 * ARG2: int, socket de escucha, creado con crearSocket();
 * RTRN: int, devuelve 0 si ha ido bien. 1 si ha ido mal.
 */
int escuchaAlSocketCliente(string &palabra, int socketEscucha)
{
    int res = 1;

    //Declaracion de Variables
    int socketRespuesta = 0;    //Socket origen de la conexion, para responder

    //Aceptamos nueva comunicación
    socketRespuesta = aceptarNuevaComunicacion(socketEscucha);

    //Escuchamos Nuevo mensaje
    recibir(socketRespuesta, palabra);     //Leemos entrada de datos

    //Enviamos mensaje
    enviar(socketRespuesta, "recibido");

    //Cerramos servidor
    close(socketRespuesta);

    res = 0;

    return res;
}

/** cerrarSocket()                   09.05.2025   -   hecha
 * Función que cierra el socket de escucha pasado como argumento.
 *
 * ARG1: int, socket que se desea cerrar.
 */
void cerrarSocket(int socketEscucha)
{
    close(socketEscucha);
    shutdown(socketEscucha, SHUT_RDWR);
    return;
}

