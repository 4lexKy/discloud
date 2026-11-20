
/*
 * Copyright 2026 Alex (alex.correu@pm.me)
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

//Estructura de la información de cada elemento.
#pragma once

#include <string>
#include <ctime>    //time_t tiempo
using std::time_t;
using std::string;


//ARCHIVO .HPP  -> DECLARACIONES

//Archivos
struct Fichero
{
    string ruta;
    time_t fechaModificacion;

    ///Fichero(string nuevaRuta, int fechaMod) : ruta(nuevaRuta), fechaModificacion(fechaMod) {}
};

//Carpetas
struct Directorio
{
    string ruta;
    time_t fechaModificacion;
    vector <string> subdirectorios;
    vector <Fichero> ficheros;
};

/** InfoArchivo                         20.04.2025   -   hecho
 * Objeto InfoArchivo, que contiene todos los elementos
 * del directorio sincronziado en Discloud
 */
class InfoArchivo{
    private:
        //Datos
        string rutaRaiz;
        time_t fechaModificacion;
    public:
        //Datos masivos
        vector<Directorio> directorios; //Público para no malgastar memoria copiando.

        // Constructor
        InfoArchivo();
        InfoArchivo(string);
        //Funciones
        void inicializarInfoArchivo(string);
        void rellenarDirectoriosYFicheros();
        void mostrarDirectoriosYFicheros();
        Fichero generarFichero(string);
        void actualizarDatos();
        //Funciones I/O
        time_t leerFechaModificacion();
        vector<Directorio> leerListaDirectorios();
        string leerRutaRaiz();
        void modificarFechaFicheroSinDirectorio(string rutaFichero,
                                                time_t nuevaFecha);
        void modificarFechaFichero(string rutaDirectorio,
                                   string rutaFichero,
                                   time_t nuevaFecha);
        Directorio* obtenerPrtDirectorio(string rutaDirectorio);
        //Serialización
        void serializarEnRuta(string rutaFichero);          //Pasar de objeto a string a ruta(fichero)
        string serializarEnString();                        //Pasar de objeto a string
        bool desSerializarDesdeRuta(string rutaFichero);    //Pasar de ruta(fichero) a string a objeto
        bool desSerializarDesdeString(string datos);        //Pasar de string a objeto
        void desSerializarDesdeStringAuxiliarIterador(
                        vector<string>::iterator & iterador,
                        string & auxIt,
                        string & ref,
                        string & dato,
                        vector<string> & lineas);
        // Constructor que no se como usar separando el cpp
        ////    : rutaRaiz(nuevaRuta) rellenarDirectoriosYFicheros() {}
};
