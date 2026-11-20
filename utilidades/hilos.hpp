
/*
 * Copyright 2026 Alex (alex.correu@pm.me)
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

#include <pthread.h>


struct DisPack{
    int entero;
    string palabra;
};

//Función que hace un hilo estandar
void* thread_run(void* data)
{
//     sleep(1);
    printf("[TH_1:%ld]: Hello from the thread \n", pthread_self());

    DisPack dp = *(DisPack*)data;
//     int a = *(int*)data;

    string aux = "El hilo recibe: "+std::to_string(dp.entero)+" y tambien: "+ dp.palabra;
    cout << aux << endl;
    printf("[TH_1:%ld]: To exit...............\n",pthread_self());
//     free((DisPack*)data);
//     delete (DisPack*)data;

    pthread_exit(&dp);
//     pthread_exit(&a);
}


// void lanzarHilo(pthread_t &thread, auto &data)
    //En C++17 prohibido auto como parámetro
    //En C++20 Permitido
    //En C++17 sí se permite esto:
    //https://cplusplus.com/forum/beginner/268895/
template <typename T> void lanzarHilo(pthread_t &thread, T * data )
{
    int thread_rc;
    DisPack dp = *data;

    cout << "Mi funcion recibe: " << dp.palabra << dp.entero << endl;
    if ((thread_rc=pthread_create(&thread,NULL,thread_run,(void *)data))!=0) //Probando (void *)
    {
        printf("Error creating the thread. Code %i",thread_rc);
    }
    pthread_detach(thread);

    return;
}

/*
void* unirHilo(pthread_t thread)//,int ** ptr_output_data3)
{
    void * retorno;
    pthread_join(thread,&retorno);
//     pthread_join(thread1,NULL);  //Sin retorno

    return retorno;
    //Para leer este retorno después hay que hacer
//     void * devuelto = unirHilo(vHilos[i]);
//     cout << *(int*)devuelto << endl;
}
*/
