
/*
 * Copyright 2026 Alex (alex.correu@pm.me)
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

#pragma once

struct FicheroModificado
{
    //Datos
    string mod;
    string ruta;
    time_t fechaModificacion;

    //Constructor
    FicheroModificado();
    FicheroModificado(string mod,
                      string ruta,
                      time_t fechaModificacion);
};


struct DirectorioModificado
{
    //Datos
    string mod;
    string ruta;
    time_t fechaModificacion;

    //Constructor
    DirectorioModificado();
    DirectorioModificado(string mod,
                         string ruta,
                         time_t fechaModificacion);
};

class Modificaciones{
    private:
        vector<FicheroModificado> ficheros;
        vector<DirectorioModificado> directorios;
    public:
        //Constructores
        Modificaciones();
        Modificaciones(vector<FicheroModificado> vfm,
                       vector<DirectorioModificado> vdm);
        //Funciones
        void vaciarObjeto();
        void vaciarFicheros();
        void vaciarDirectorios();
        //Funciones I/O
        void anyadirNuevoFichero(FicheroModificado fm);
        void anyadirNuevoDirectorio(DirectorioModificado dm);
        void guardarListaFicheros(vector<FicheroModificado> vfm);
        void guardarListaDirectorios(vector<DirectorioModificado> vdm);
        void guardarListasFicherosYDirectorios(vector<FicheroModificado> vfm,
                                               vector<DirectorioModificado> vdm);
        vector<FicheroModificado> leerListaFicheros();
        vector<DirectorioModificado> leerListaDirectorios();
        //Serializacion
        string serializarEnString();
        bool desSerializar(string datos);
        void desSerializarAuxiliarIterador(
                        vector<string>::iterator & iterador,
                        string & auxIt,
                        string & ref,
                        string & dato,
                        vector<string> & lineas);
};
