
/*
 * Copyright 2026 Tu Nombre y colaboradores
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


// ### PRUEBAS ###
#include <pthread.h>
        //Librería de hilos en C y C++
        //Usa Posix, necesita -lpthread como opción en GCC
        //https://iq.opengenus.org/std-thread-vs-pthread/
        //No quiere enlazar con -lpthread
#include "utilidades/hilos.hpp"
using namespace std;
// ### PRUEBAS ###



int main (int argc, char *argv[])
{
    cout << "Empieza la prueba" << endl;
    // ###


    //Declaraciones
//     pthread_t thread;       //Declaración de un hilo
    int *ptr_output_data = new int;   //Datos devueltos
    *ptr_output_data = 1;
    DisPack disPack;
    disPack.entero = 1;
    disPack.palabra = "hola";
//     vector<pthread_t> vHilos;
    pthread_t vHilos[21];
//     int enteros[21];


    //Hilo principal
    printf("[MAIN:%ld]: Main lanza 20 hilos. \n",pthread_self());

    //Lanzamos hilos
    int i = 1;
    if (true) //for(int i = 0; i<20; i++)
    {
        disPack.entero = i;

        DisPack dp;
        dp.palabra = disPack.palabra;
        dp.entero = disPack.entero;

        //En C++ el malloc debe ser casteado
        DisPack *newdp = (DisPack*)malloc(sizeof(dp));
        *newdp = dp;

        lanzarHilo(vHilos[i],newdp);
//             free(newdp);
        //     delete (DisPack*)data;
    }
    if (true)//for(int i=0; i<20; i++)
        cout << i*100<<(int)vHilos[i] << endl;
    printf("[MAIN:%ld]: Hilos lanzados (2segundos)\n",pthread_self());
    sleep(2);


    //Unimos los hilos
    for(int i=0; i<20; i++)
    {
//         void * devuelto = unirHilo(vHilos[i]);
//         cout << *(int*)devuelto << endl;
    }

    //Si no está la memoria reservada de una cosa en el printf da violacion del segmento
//     printf("[MAIN:%ld]: Thread returns %d \n",pthread_self(), *ptr_output_data1);

    /*
    vector<pthread_t> threads;
    pthread_t t;
    int *count = new int(0);
    for (int i = 0; i<=10; i++)
    {
        threads.push_back(t);
        pthread_create( &threads.at(i), NULL, &funcionHilar, count);
    }


    cout << "principal" << endl;

*/






    // ###
    cout << "Termina la prueba " << endl;
    return 0;
}


