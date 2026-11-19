
/*
 * Copyright 2026 Tu Nombre y colaboradores
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

#include "../includes.hpp"
#include "../namespaces.hpp"

#include "./nodo.hpp"

/**                                 09.05.25   -   hecha
 * Constructor básico del objeto
 */
Nodo::Nodo(int id)
{
    this->idNodo = id;
}

/** leerIdNodo()             09.05.25   -   hecha
 * Función básica de I/O entrada salida de datos del objeto
 * devuelve el identificador del objeto.
 */
int Nodo::leerIdNodo()
{
    return this->idNodo;
}

/** modificarIdNodo()         09.05.25   -   hecha
 * función que modifica el id del nodo
 * Esta función solo se usa en momentos puntutales
 * por ejemplo en la creación de una lista de nodos.
 */
void Nodo::modificarIdNodo(int nuevoId)
{
    this->idNodo = nuevoId;
}

void Nodo::cambiarRutaRaiz(string ruta)   //No implementada
{
    return;
}
