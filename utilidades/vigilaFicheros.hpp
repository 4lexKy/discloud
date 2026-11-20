
/*
 * Copyright 2026 Alex (alex.correu@pm.me)
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

#pragma once    //https://stackoverflow.com/questions/5776910/what-does-pragma-once-mean-in-c

#include <string>
#include "../estructuras/listadoFicheros.hpp"
#include "../estructuras/modificaciones.hpp"


void monitorizarFicheros(InfoArchivo & ia,
                        vector<DirectorioModificado> & directoriosModificados,//vector<string> & directoriosModificados,
                        vector<FicheroModificado> & ficherosModificados,//vector<string> & ficherosModificados,
                        /*BDiscloud & bdloud*/
                        bool BD,
                        int frecuenciaDeComprobacionEnSegundos);/*Tiempo predeterminado 1 seg.*/

vector<string> detectarDirectoriosLlenosModificados(InfoArchivo &ia);
vector<DirectorioModificado> detectarDirectoriosLlenosModificadosEnStruct(InfoArchivo &ia);

vector<string> detectarFicherosModificados(vector<string> directoriosModificados, InfoArchivo &ia);
vector<FicheroModificado> detectarFicherosModificadosEnStruct(vector<DirectorioModificado> directoriosModificados, InfoArchivo &ia);

bool contarCambiosEnFicheros(string ruta,
                             InfoArchivo &ia,
                             int &cantidadFicherosModificados,
                             string &ultimoFicheroModificado);
bool contarCambiosEnDirectorios(string ruta,
                             InfoArchivo &ia,
                             int &cantidadDirectoriosModificados,
                             string &ultimoDirectorioModificado);

Directorio obtenerDirectorioPorNombre(string rutaContenedora, InfoArchivo &ia);

Fichero obtenerFicheroPorNombreYDirectorio(string rutaContenedora, string ficheroABuscar, InfoArchivo &ia);
