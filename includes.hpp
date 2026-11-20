
/*
 * Copyright 2026 Alex (alex.correu@pm.me)
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

#pragma once
/*
Dependencias entre archivos
(los de la izquierda necesitan los que están a su abajo a la derecha)

discloud
    -directorios
    -comunicaciones
        -envrec
        -importscomunicaciones
    -envíoArchivos
        accesoArchivos

includes    (todos)
namespaces  (todos)
makefile    (todos)

*/





// #include <cstdlib>
        //C Standard General Utulities Library
        //stdlib.h está deprecated y sirve exactamente para lo mismo, es la que se usaba en C, cstdlib es c++
        //https://cplusplus.com/reference/cstdlib/
        //https://conclase.net/c/librerias/stdlib
        //atoy, rand, mallc, calloc, free, div...

//IN OUT Y STRINGS
#include <fstream>
        //Librería para lees y escribir ficheros
        //https://archivossistemasunefa.blogspot.com/2022/01/la-libreria-y-sus-clases.html
        //Incluye a iostream
#include <iostream>
        // fstream incluye a <iostream>
        // iostream incluye a cstdio
        // iostream incluye a string
        //la .h es la antigua //cin y cout
#include <string>
        //Para manejar palabras
        //string está incluida en iostream
#include <cstring>
        //Versión para c++ de la librería en c string.h
        //Para funciones como strcmp(string1, string2) (compara strings)
#include <cstdio>
        //Esta librería permite el uso de funciones relacionadas
        //con la entrada y salida del programa.
        //https://www.geeksforgeeks.org/cpp-cstdio/
        //https://cplusplus.com/reference/cstdio/
        //https://conclase.net/c/librerias/stdio
        //cstdio incluye a stdio.h
        //cstdio está incluida en iostream
        //printf, scanf, fopen...

#include <vector>
        //Para el uso de vectores estandar en C++
        //Ej. vector<string> palabras;
        //ej2. palabras.push_back(palabra);
        //using std::vector;

//ADMINITRACIÓN DE DIRECTORIOS
// #include <filesystem>
#include <experimental/filesystem>
        //Librería para manejar carpetas/directorios
        //usa el espacio de nombres filesystem
        //create_directories(ruta) remove(ruta)
        //namespace fs = std::experimental::filesystem;

//PAUSA Y CONTADOR DE TIEMPO
#include <chrono> // nanoseconds, system_clock, seconds
#include <thread> // sleep_for, sleep_until
    //Definidos en namespaces:
    //using namespace std::this_thread;
    //using namespace std::chrono;
    //Usos:
    //sleep_for(seconds(2));
    //sleep_for(nanoseconds(10));
    //sleep_until(system_clock::now() + seconds(1));

//ACCESO A FICHEROS
//#include <fstream> (ya incluida)
#include <fcntl.h>          //open() creat()
#include <unistd.h>         //close() read() fstat
#include <sys/types.h>  //fstat https://linux.die.net/man/2/fstat
#include <sys/stat.h>   //fstat https://linux.die.net/man/2/fstat

//GESTIÓN DE DIRECTORIOS (y ficheros)
#include <dirent.h>
    //Para acceder a la información de última modificación por ejemplo


#include <ctime>
    //Para el uso de la unidad de tiempo //time_t tiempo
    //Se usa por ejemplo al obtener la fecha de un archivos
    //o mostrarla
    //time_t tiempo;
    //fechalegible = ctime(&tiempo)










/*
#include <omp.h>        //OpenMP
#include <unistd.h>     //Sleep
#include <math.h>       //devuelve el numero en absoluto de un double fabs(double)
#include <stdlib.h>     //Dinamic memory allocation
#include <time.h>       //Contar tiempo



typedef
.h y el otro
funciones
hilos y procesos
punteros
*/

/** Bibliografía

-std=c++17
15.04.2025
https://es.stackoverflow.com/questions/68937/c%C3%B3mo-saber-la-versi%C3%B3n-del-est%C3%A1ndar-c-que-estoy-utilizando-en-c%C3%B3digo

clang++-16 compilador
15.04.2025
https://stackoverflow.com/questions/9148488/how-do-i-compile-c-with-clang
https://rodin.uca.es/bitstream/handle/10498/16912/clang_tutorial.pdf

-lstdc++fs opción de g++ para librería experimental filesystem
15.04.2025
https://stackoverflow.com/questions/49249349/undefined-reference-when-using-experimental-filesystem

str.c_str() y srt.data()  conversión de string a cons char y char
15.04.2025
https://stackoverflow.com/questions/7352099/stdstring-to-char

#include <chrono> y <thread>, para la pausa: sleep_for(seconds(2));
15.04.2025
https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program

remove, eliminar carpetas con filesystem
15.04.2025
https://en.cppreference.com/w/cpp/filesystem/remove

filesystem
18.04.25
https://en.cppreference.com/w/cpp/header/experimental/filesystem

fstat, info sobre directorios y archivos
03.05.2025
https://linux.die.net/man/2/fstat

iteradores
03.05.2025
https://www.w3schools.com/cpp/cpp_iterators.asp

asio, para gestión de hilos eficiente NO IMPLEMENTADO, necesitaría mucha dedicacion
05.05.2025
https://stackoverflow.com/questions/3719462/sockets-and-threads-using-c
https://www.boost.org/doc/libs/1_41_0/doc/html/boost_asio.html

valgrind, de dice en compilacion los errores que hay y tal.
08.05.2025
https://stackoverflow.com/questions/5134891/how-do-i-use-valgrind-to-find-memory-leaks
sudo apt install valgrind
valgrind --verbose ./pr2.o

*/
