
/*
 * Copyright 2026 Alex (alex.correu@pm.me)
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

// ### DESCARTADOS ###
/*
#include <fcntl.h> //????????????????
#include <direct.h> //Windows
*/

// ### INCLUDES ###
#include "includes.hpp"
#include "namespaces.hpp"
#include "utilidades/directorios.hpp"
#include "utilidades/comunicacionServidor.hpp"
#include "utilidades/comunicacionCliente.hpp"
#include "utilidades/accesoArchivos.hpp"
#include "utilidades/envioArchivos.hpp"
#include "utilidades/vigilaFicheros.hpp"
#include "discloudLib/discloudLib.hpp"
#include "estructuras/listadoFicheros.hpp"
#include "estructuras/nodo.hpp"


// ### PRUEBAS ###



int main (int argc, char *argv[])
{
    cout << "Empieza la prueba" << endl;


    // ###
    /*
    string ruta("./CarpetaOrigen");

    cout << "obteniendo archivos" << endl;
    InfoArchivo infoArchivo(ruta);
//      cout << "mostrando archivos" << endl;
//      infoArchivo.mostrarDirectoriosYFicheros();

    cout << "Listar directorios" << endl;
    vector<Directorio> vD = infoArchivo.leerListaDirectorios();
    for (Directorio d : vD )
        cout << d.ruta << endl;


    vector<string> vecDir,vecFich;
    do{
        cout << endl << endl << "Monitorizar ficheros: " << endl << endl;
        monitorizarFicheros(infoArchivo,vecDir,vecFich,true,3);

        cout << "Carpetas modificadas: "<< endl;
        for(string d:vecDir)
        {
            cout <<"\t"<< d << endl;
        }

        cout << "Ficheros modificados: "<< endl;
        for(string d:vecFich)
        {
            cout <<"\t"<< d << endl;
        }

        cout << "3" << endl;
        sleep_for(seconds(1));
        cout << "2" << endl;
        sleep_for(seconds(1));
        cout << "1" << endl;
        sleep_for(seconds(1));
        if(vecDir.size() != 0 || vecFich.size() != 0)
        {
            cout <<"Actualizando arbol" << endl;
            infoArchivo.actualizarDatos();
        }
    }while (true);
*/


    // ###






//     cout << "Sin *: " << respuesta << endl;     //Contenido
//     cout << "Con *: " << *respuesta << endl;    //1
//     cout << "Con *: " << respuesta* << endl;    //??
//     cout << "Con &: " << &respuesta << endl;    //Direccion de memoria
    cout << "Termina la prueba " << endl;
    return 0;
}










