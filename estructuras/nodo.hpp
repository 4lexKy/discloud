
/*
 * Copyright 2026 Tu Nombre y colaboradores
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

//Estructura de la información de cada elemento.
#pragma once

#include <string>

class Nodo{    //  09.05.25   -   hecha
    private:
        //Datos
        int idNodo;
        string rutaRaiz;
//         time_t fechaModificacion;
    public:
        // Constructor
        Nodo(int);
        //Funciones
        int leerIdNodo();
        void modificarIdNodo(int nuevoId);
        void cambiarRutaRaiz(string);   //No implementada
        // Constructor que no se como usar separando el cpp
        ////    : rutaRaiz(nuevaRuta) rellenarDirectoriosYFicheros() {}
};
