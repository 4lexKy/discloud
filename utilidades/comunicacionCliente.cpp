
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

//FUNCIONES DE CLIENTE
//     bool conexion(int& socketLlamada)
// void pruebaSocketsCliente()
// int informarAlServidor(string &palabra)



//falta decidir htos https://trspos.com/hton-htonl-htons-c/#que_son_las_funciones_hton_htonl_y_htons_
bool conexion(int& socketLlamada)
{
    bool res;
    short resultado;
    socketLlamada = 0;
    struct sockaddr_in direccionServidor;   //Variable que contendrá la dirección del servidor
    string respuesta;//[1024];

    //Creación del socket
    socketLlamada = socket(AF_INET, SOCK_STREAM, 0);

    //Seguridad de que no falle???

    //Asignamos la dirección
    direccionServidor.sin_family = AF_INET;                 //Protocolo IPV4
    direccionServidor.sin_port = htons(PORT);               //Puerto de destino
    direccionServidor.sin_addr.s_addr = inet_addr(IPcl);      //Direccion destino

    //Establecemos conexion
    resultado = connect(socketLlamada, (struct sockaddr *)&direccionServidor, sizeof(direccionServidor));
        /**
        * Arg1: socket del servidor
        * Arg2: Puntero al struct de la dirección
        * Arg3: Tamaño de la variable de direccion
        */

    if ( resultado == 0 )
        res = true;
    else
        res = false;

    return res;
}

/** conexionDetallada()                     09.05.25   -   hecha
 * Versión de la función conexion() a la que se le puede
 * especificar la ip y puerto del destino a conectar.
 *
 * ARG1: int&, socket de llamada para devolverlo.
 * ARG2: string, ip del servidor a conectar en formato "127.0.0.1"
 * ARG3: int, puerto a usar para la conexión con el servidor
 * RTRN: bool, devuelve un true en caso de que haya ido bien la conexión.
 */
bool conexionDetallada(int& socketLlamada,
                       string ip,
                       int puerto)
{
    bool res;
    short resultado;
    socketLlamada = 0;
    struct sockaddr_in direccionServidor;   //Variable que contendrá la dirección del servidor
    string respuesta;//[1024];

    //Creación del socket
    socketLlamada = socket(AF_INET, SOCK_STREAM, 0);

    //Seguridad de que no falle???

    //Asignamos la dirección
    direccionServidor.sin_family = AF_INET;                 //Protocolo IPV4
    direccionServidor.sin_port = htons(puerto);             //Puerto de destino
    direccionServidor.sin_addr.s_addr = inet_addr(ip.c_str());      //Direccion destino

    //Establecemos conexion
    resultado = connect(socketLlamada, (struct sockaddr *)&direccionServidor, sizeof(direccionServidor));
        /**
        * Arg1: socket del servidor
        * Arg2: Puntero al struct de la dirección
        * Arg3: Tamaño de la variable de direccion
        */

    if ( resultado == 0 )
        res = true;
    else
        res = false;

    return res;
}

/** Prueba Socket  ### TERMINADA ###
 * Funcion que demuestra que la conexion con las funciones hechas
 * por mi funcionan y se establece una conexion
 * Se debe llamar a la funcion con el mismo nombre en el servidor
 */
void pruebaSocketsCliente()
{
    //Declarar variables
    int socketLlamada;
    string respuesta;


    //Pedimos conexion al servidor
    conexion(socketLlamada);


    //Creacion variable a enviar'
    respuesta = "hola desde el cliente";


    //Enviar primer mensaje
    enviar(socketLlamada, respuesta);
        cout << "Enviado:\n" << respuesta << endl;

    //Recibiendo mensaje (2)
    recibir(socketLlamada, respuesta);
        cout << "\nRecibido\n" << respuesta;

    //Cerramos el socket
    close(socketLlamada);
    cout << "\nSocket cerrado\n";

    return;
}

/** informarAlServidor()              17.04.2025 - hecho
 *
 * Función para enviar datos al servidor, como ping
 * o que necesita información. Siempre corto.
 *  función complementaria: escuchaAlCliente(string &palabra)
 *
 *  El string a enviar ya no puede ser por referencia
 * para un funcionamiento mas facil poniendo una función
 * que devuelve un string como argumento de esta. Actualización: 12.05.2025
 *
 * Argumento: un string.
 * Return
 *      0 -> todo ha ido bien.
 */
int informarAlServidor(string palabra)
{
    int res = 1;
    int socketLlamada;
    string respuesta;

    //Pedimos conexion al servidor
    if (conexion(socketLlamada)!=true)
    {
        cout << "Fallo al conectar"<< endl;
    }
    else
    {

        //Enviar primero mensaje
        enviar(socketLlamada, palabra);

        //Recibir la respuesta
        recibir(socketLlamada, palabra);

        //Cerramos el socket
        close(socketLlamada);
//         cout << "\nSocket cerrado\n";
    }
    res = 0;

    return res;
}










