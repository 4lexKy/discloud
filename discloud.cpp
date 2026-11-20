
/*
 * Copyright 2026 Alex (alex.correu@pm.me)
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
 * - Código del servidor Discloud.
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

void casoNuevaModificacion(string dato, InfoArchivo ia, int socketEscucha)
{
    //Declaraciones
    Modificaciones mods;        //Objeto que contiene modificaciones
    vector<FicheroModificado>    vfm;
    vector<DirectorioModificado> vdm;
    string rutaAdaptada;

    //Informa por consola
    cout << "[SRV]-> Se recibe modificaciones de cliente codigo:CMS..." << endl;

    //Cargamos las modificaciones en el objeto
    mods.desSerializar(dato);

    //Obtenemos las listas de los elementos modificados
    vfm = mods.leerListaFicheros();
    vdm = mods.leerListaDirectorios();

    cout << "Enviado tam: " << vfm.size() << endl;

    //Actualizamos los ficheros
    for(FicheroModificado fm : vfm)
    {
        //Leer qué hacer
        if(fm.mod == "CFM")
        {
            //Recibir archivo
            rutaAdaptada = sustituirDirectorioRaiz(fm.ruta, ia.leerRutaRaiz());
            cout << "la ruta: " << fm.ruta << endl;
            cout << "la ruta: " << rutaAdaptada << endl;
            if (recibirArchivoSVSocketPropio(rutaAdaptada,socketEscucha)== 0)
            {   //El archivo se ha recibido correctamente.
                //Actualizamos fecha de fichero en infoArchivo
                // ### PROBLEMITAS CON PUNTEROS
                //ia.modificarFechaFicheroSinDirectorio(fm.ruta, fm.fechaModificacion);
            }
        }
        if(fm.mod == "CFN");
        if(fm.mod == "CFE");
        if(fm.mod == "CFC");
        if(fm.mod == "CFV");
    }

    //Actualizamos los directorios ( en caso de que cambie algo mas que la fecha
    //      Sino lo ideal sería cambiarlo cuando actualizamos un archivo
    for(DirectorioModificado dm : vdm)
    {
        ;
/*
        CDN
        CDE
        CDC
        CDV*/

    }

    return;
}


int main(int argc, char *argv[])
{
    //Defines ###
    int maxConexiones = 20;
    string rutaIAGuardada = "./InfoArchivo.dat";

    //Declaraciones
    string rutaRaiz = "./CarpetaServidor";
    InfoArchivo ia;


    //Encendemos nodo (cargar el struct de datos)
    cout << "[SRV]-> Iniciando Nodo..." << endl;
    if (existeIAguardado(rutaIAGuardada ) == true)
    {
        //Si existe archivo se desserializa.
        ia.desSerializarDesdeRuta(rutaIAGuardada);
    }
    else
    {
        //Si no existe el archivo guardado se lee.
        //Podemos llegar aquí por:
            // -> Ser la primera vez que se inicia el nodo
            // -> Haber sufrido un error y no poder leer el archivo serializado.
        ia.inicializarInfoArchivo(rutaRaiz);
    }

//#############################################################################################

    // SIMULTANEO 1/3 Atendemos a los clientes
    int socketEscucha = crearSocket(maxConexiones);
    string mensajeDelCliente;
    string  ref;
    int tamDato;
    string dato;
    while (true)
    {
        cout << "[SRV]-> Escuchamos clientes..." << endl;

        //Recibimos mensaje
        escuchaAlSocketCliente(mensajeDelCliente, socketEscucha);

        cout << "mensajeRecibido: " << mensajeDelCliente << endl;

        //Detectamos tipo mensaje
        ref     = mensajeDelCliente.substr(0,3);
        tamDato = mensajeDelCliente.length()-3;
        dato    = mensajeDelCliente.substr(4,tamDato); //No es 3 y sí 4 para saltar el salto de linea

        //Actuamos en consecuencia
//         if(ref=="NEW") casoInicioSesion();
//         if(ref=="OUT") casoCierreSesion();
//         if(ref=="CEN") casoNuevoCliente();
//         if(ref=="CEV") casoClienteViejo();
        if(ref=="CMS") casoNuevaModificacion(dato,ia,socketEscucha);
    }

    // SIMULTANEO 2/3 Escuchamos a los nodos

    // SIMULTANEO 3/3 Escuchamos al admin (apagar, desconectar nodo...)

    // SIMULTANEO 4/3 (a futuro) Vigilar ficheos
            //Así podremos usar el nodo como un cliente más para cargar datos.






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
