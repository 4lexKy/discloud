
/*
 * Copyright 2026 Tu Nombre y colaboradores
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

#pragma once
//https://stackoverflow.com/questions/5776910/what-does-pragma-once-mean-in-c



bool enviar(int socketRespuesta, string palabra);//char* respuesta)

bool recibir(int socketRespuesta, string & respuesta);
