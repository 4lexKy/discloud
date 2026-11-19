
/*
 * Copyright 2026 Tu Nombre y colaboradores
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

/**
 * Creado 18.04.2025
 */
#pragma once    //https://stackoverflow.com/questions/5776910/what-does-pragma-once-mean-in-c

#include <ctime>    //time_t tiempo
#include <string>

;
int abrirCrearArchivo(string ruta);

int cerrarArchivo(int descriptor);

//Funciones de lectura y escriptura de archivos
string leerArchivoDesdeDescriptor(int descriptor);
string leerArchivoDesdeRuta(string ruta);
void escribirArchivoDesdeDescriptor(int descriptor, string info);
void escribirArchivoDesdeRuta(string ruta, string info);

int leerTamanyoFicheroDesdeDescriptor(int descriptor);
int leerTamanyoFicheroDesdeRuta(string ruta);

vector<string> listarFicheros(string ruta);

bool esFichero(string ruta);

bool existeFichero(string const& ruta);

time_t fechaModificacionDeFichero(string ruta);

string mostrarFechaLegible(time_t fechaCruda);

void mostrarDatos(string ruta);

string obtenerRutaDirectorioDesdeRutaFichero(string rutaFichero);
