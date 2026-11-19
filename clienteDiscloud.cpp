
/*
 * Copyright 2026 Tu Nombre y colaboradores
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

/*********************************************************
 * Alex - 10.04.2025
 * alex.correu@pm.me
 *
 *      TFG - Discloud
 *
 * - Nube distribuida privada de código abierto.
 *
 * - Código del cliente Discloud.
 */

// ### Includes ###
#include "includes.hpp"       //Fichero que contiene todos los includes necesarios para Discloud

// ### Definición de espacios de nombres ###
#include "namespaces.hpp"

// ### Mis funciones ###
#include "utilidades/directorios.hpp"
#include "utilidades/comunicacionServidor.hpp"
#include "utilidades/comunicacionCliente.hpp"
#include "utilidades/accesoArchivos.hpp"
#include "utilidades/envioArchivos.hpp"
#include "utilidades/vigilaFicheros.hpp"
#include "discloudLib/discloudLib.hpp"
#include "estructuras/listadoFicheros.hpp"

// ### Defines ###
// #DEFINE RUTA "./datosNube???
#define _XOPEN_SOURCE 700   //https://stackoverflow.com/questions/5378778/what-does-d-xopen-source-do-mean

// ### Funciones ###




int main(int argc, char *argv[])
{
    //Defines
    string rutaIAGuardada = "./infoArchivo.dat";
    string rutaRaiz = "./CarpetaOrigen";

    //Declaraciones
    InfoArchivo ia;

    //Encendemos cliente (cargar el struct de datos)
    ia.inicializarInfoArchivo(rutaRaiz);

    //Informa del estado actual de los datos
    if(true)    //Si la rutaraiz contiene algo == true ###
    {
        //El cliente es viejo y tiene datos (informa de ellos)
        informarAlServidor("CEV\n"+ia.serializarEnString());    //Enviamos ia actual
    }
    else
    {
        //El cliente es nuevo y no tiene datos
        informarAlServidor("CEN\n");    //Enviamos ia actual
    }

    //Para debuging
    escribirArchivoDesdeRuta("./serializa.dat", ia.serializarEnString());

//#############################################################################################

    // EN SERIE Envío inicial


    // SIMULTANEO 1/3 Vigilar ficheros e informar (enviar modificaciones)
    cout << "[CLI]-> Comprobando Modificaciones" << endl;
    bucleDeDeteccionYenvioDeficheros(ia);

    // SIMULTANEO 2/3 Escuchar a los nodos.(recibir modificaciones)

    // SIMULTANEO 3/3 Escuchar opciones de usuario.(apagar, pausar...)




    //exit(EXIT_SUCCESS);
    return 0;
}















/**
 * 11.04.2025
 *      - Resuelto librerías
 *      - Resuelto los archivos .h
 *      - Resuelto cout y namespace
 *      - Resuelto predeclaración librerías
 *      - if alterantivo sin if comprendido => pregunta ? op1 : op2;
 *
 *      Hacer clases hpp??
 *
 */
