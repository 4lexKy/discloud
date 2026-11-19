
/*
 * Copyright 2026 Tu Nombre y colaboradores
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

#pragma once        //https://stackoverflow.com/questions/5776910/what-does-pragma-once-mean-in-c


//falta decidir htos https://trspos.com/hton-htonl-htons-c/#que_son_las_funciones_hton_htonl_y_htons_
bool conexion(int& socketLlamada);

bool conexionDetallada(int& socketLlamada,
                       string ip,
                       int puerto);

void pruebaSocketsCliente();

int informarAlServidor(string palabra);











