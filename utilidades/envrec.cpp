
/*
 * Copyright 2026 Tu Nombre y colaboradores
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

// #pragma once
//https://stackoverflow.com/questions/5776910/what-does-pragma-once-mean-in-c

//Includes
#include "importsComunicaciones.hpp"

//Declaracion funciones
//Al parecer hay que declaarlas en el propio cpp

//Implementacion funciones:

using namespace std;


/**     ENVIAR          ### FALTA LIMPIAR UN POCO COMENTARIOS ###
 *  En esta funcion envia el contenido del string palabra pasado como valor
 *  al socket que se indica. Devuelve true si ha ido bien
 *
 *  ARG1: Entero que contiene el socket donde enviar el mensaje
 *  ARG2: String que contiene los datos a enviar
 *  RTRN: Devuelve el resultado del intento de envio
 *          >=0 si ha ido bien (indicando el numero de bytes mandados)
 *          -1 ha ido mal
 *
 *  *  Modificaciones:
 *      -14.06.2024 Funciona, revisado
 */
bool enviar(int socketRespuesta, string palabra)//char* respuesta)
{
    bool aux = false;
    short resultado = -1;

    /* //NO USADA, FUNCIONA, Creando mensaje a enviar (desde char *)
    char respuesta[256];
    memset(respuesta, '0', sizeof(respuesta));
    snprintf(respuesta, sizeof(*respuesta), "%d holas",3);   //Funciona, pero ya no lo necesito
    */
        /**
         * Arg1: punterovariable a rellenar
         * Arg2: tamaño de variable
         * Arg3: contenido a introducir desde el puntero
         * Arg+4:variables a introducir en la cadena Arg3, como en print()
         * explicación en  https://cplusplus.com/reference/cstdio/snprintf/
         */

    //Traduciendo mensaje a enviar (desde STRING a char)
    char *respuesta;
    respuesta = new char[palabra.size()];
    for (long unsigned int i = 0; i < palabra.size();i++)
    {
        respuesta[i] = palabra[i];
    }

    //Enviar
    resultado = send(socketRespuesta, respuesta, palabra.size(),0);
        /**
        * Arg1: Socket destino
        * Arg2: Puntero a mensaje a transmitir
        * Arg3: Tamaño del mensaje   char *buffer
        * Arg4: Flags
        * Return:   correcto si =  0 o numero de bytes enviados
        *         ha fallado si = -1
        * Info de: https://www.ibm.com/docs/en/zos/2.1.0?topic=functions-send-send-data-socket
        */

    if(resultado>=0)
        aux = true;     //Si ha ido bien
    else
        aux = false;    //si algo ha fallado

    return aux;
}

/**     Recibir              ### Falta saber alguans dudas //??  y quitar comentarios ###
 *  Esta funcion espera a recibir los datos que el socketRespuesta nos envie
 *  Como dato, el bucle sirve por si los datos son mayores que el buffer,
 *  primero se llena, se vacia y se sigue recibiendo.
 *  La respuesta final se devuelve por referencia.
 *
 *  ARG1: Es un entero que contiene el socket a escuchar
 *
 *  ARG2: Es un string por referencia, donde se devuelve el resultado recibido.
 *
 *  RTRN: Se devuelve true si ha llegado hasta ese punto.
 *
 *  *En caso de querer pasar buffer como un argumento usar solo en la declaracion de la funcion: char* buffer
 *
 *  Modificaciones:
 *      -14.06.2024 Funciona de todo con valor mayor que el buffer
 */
bool recibir(int socketRespuesta, string & respuesta)
{
    //Declacion variables
    char buffer[64];//255];// = { 0 };         //Datos recibidos
    long unsigned int n;

    //Inicializacion necesaria de variables
    memset(buffer, '0', sizeof(buffer));        //Llenar de 0s
    string temp = "";
    respuesta = "";

    //Bucle de recepcion
    do
    {
        n = read(socketRespuesta, &buffer, sizeof(buffer)-1); //-1??
            /**
             * Arg1: socket de conexion con el servidor
             * Arg2: variable para almacenar los datos de llegada
             * Arg3: tamaño de la variable
             * Info de: https://www.ibm.com/docs/en/zos/2.1.0?topic=functions-read-read-from-file-socket
             */
        buffer[n] = 0;      //??
        // if(fputs(buffer, stdout) == EOF) //??
        // {
        //     printf("\nStandard output error");
        // }

        //Convertimos char* a string para trabajar mejor
        temp.assign(buffer, n);
            /**
             * arg1 el char* que queremos pasar a string
             * arg2 el lo caracteres que tiene char*, puede ser sizeof(buffer) para la variable buffer entera
             */

        //Anyadimos la lectura parcial a la respuesta total
        respuesta += temp;

    } while ( n == sizeof(buffer)-1 );

    return true; //Si ha llegado aqui ha ido bien
}
