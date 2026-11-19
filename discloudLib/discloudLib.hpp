
/*
 * Copyright 2026 Tu Nombre y colaboradores
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

#pragma once        //https://stackoverflow.com/questions/5776910/what-does-pragma-once-mean-in-c

#include <string>
#include "../estructuras/listadoFicheros.hpp"

int almacenamientoLocal(std::string ruta);


void escuchandoAClientes(InfoArchivo & ia);

void bucleDeDeteccionYenvioDeficheros(InfoArchivo & ia);

bool existeIAguardado(string rutaIAGuardada);
