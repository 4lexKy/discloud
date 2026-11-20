
/*
 * Copyright 2026 Alex (alex.correu@pm.me)
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

/**
 * Creado 18.04.2025
 */
//#pragma once    //https://stackoverflow.com/questions/5776910/what-does-pragma-once-mean-in-c

#include "../includes.hpp"
#include "../namespaces.hpp"

#include "accesoArchivos.hpp"
#include "directorios.hpp"


/** abrirCrearArchivo()                     18.04.2025  -  hecho
 * Esta función abre un archivo (lo crea si no existe) y devuelve
 * el descriptor para poder usarlo.
 *
 * ARG1 - String, es la ruta al archivo a abrir.
 * RTRN - int, devuelve el descriptor del archivo:
 *         -> -1 si algo ha salido mal
 *         -> >0 si todo ha salido bien (el descriptor)
 *
 * 09.05.2025 - Mejorada para que cree la ruta de las carpetas si no existen.
 */
int abrirCrearArchivo(string ruta)
{
    //Obtenemos la ruta, solo las carpetas
    int tamanyo = ruta.length()-1;
    string rutaCarpetas = "//";

    //Procesamos la ruta para obtener solo las carpetas, sin el fichero
    while(rutaCarpetas=="//" && tamanyo>0)
    {
        //Primero avanzamos un caracter, si el archivo acaba en '/' no queremos borrarlo.
        tamanyo--;
        if(ruta[tamanyo] =='/')
        {
            rutaCarpetas = ruta;
            rutaCarpetas.erase(tamanyo+1,ruta.length()-1);
        }

    }
    //Si no existe el directorio lo creamos.
    crearDirectorio(rutaCarpetas);

                                         //O_TRUNC
    int descriptor = open(ruta.c_str(),O_RDWR|O_CREAT,S_IRWXU);
                                          //Abre archivo en modo lectura y escritura
                                                 //Crea el archivo si no existe
                                                         //crea el archivo con permiso lectura y escritura
    return descriptor;
}

/**     cerrarArchivo()                     18.04.2025 - hecho
 * Esta función cierra el archivocuyo descriptor
 * se pasa como único argumento.
 *
 * ARG1 -> int, descriptor del archivo a cerrar
 * RTRN -> int:
 *          -> 0 si se ha cerrado bien
 */
int cerrarArchivo(int descriptor)
{
    return close(descriptor);
}


/** leerArchivoDesdeDescriptor()                10.05.2025   -   hecho
 * Función que lee el contenido del archivo asocido
 * al descriptor abierto(ARG1) y devuelve su contenido
 * en un string.
 *
 * ARG1: int, descriptor abierto al fichero que queremos leer
 * RTRN: string, variable con el contenido del fichero.
 */
string leerArchivoDesdeDescriptor(int descriptor)
{
    //Inspirado en el lector de mi librería envrec.hpp

    char buffer[leerTamanyoFicheroDesdeDescriptor(descriptor)];
    memset(buffer, '0', sizeof(buffer));
    string info;
    long unsigned int n;

    n = read(descriptor,
         &buffer,   // no funciona -> (char*)(info.data()),
         leerTamanyoFicheroDesdeDescriptor(descriptor));

    buffer[n] = 0;
    info.assign(buffer, n);

    return info;
}

/** leerArchivoDesdeRuta()                      11.05.2025   -   hecha
 * Función que lee el contenido del archivo de la
 * ruta pasada como ARG1 y devuelve su contenido
 * en un string.
 *
 * ARG1: string, ruta del fichero a leer.
 * RTRN: string, variable con el contenido del fichero.
 */
string leerArchivoDesdeRuta(string ruta)
{
    //Inspirado en el lector de mi librería envrec.hpp

    string info;
    int tamanyo = leerTamanyoFicheroDesdeRuta(ruta);
    char buffer[tamanyo];
    memset(buffer, '0', sizeof(buffer));
    long unsigned int n;

    int descriptor = abrirCrearArchivo(ruta);

    n = read(descriptor,
         &buffer,   // no funciona -> (char*)(info.data()),
         tamanyo);

    cerrarArchivo(descriptor);

    buffer[n] = 0;
    info.assign(buffer, n);

    return info;
}

/** escribirArchivoDesdeDescriptor()        10.05.2025   -   hecha
 * Función que accede al descriptor de un
 * archivo abierto y escribe en él el contenido
 * del string pasadocomo segundo parámetro.
 *
 * ARG1: int, descriptor del archivo a escribir.
 * ARG2: string, variable con el contenido a escribir.
 *
 * ### FALTA teneren cuenta que si un archivo se escibe, ya existia
 *              y el nuevo es mas pequeño no se borra lo último.
 *          Ej:
 *
 *             Viejo        nuevo
 *             Viejo        nuevo
 *             Viejo   ->   nuevo
 *             Viejo   ->   nuejo
 *             Viejo        Viejo
 *             Viejo        Viejo
 */
void escribirArchivoDesdeDescriptor(int descriptor, string info)
{

    write(descriptor,
         (char*)(info.data()),
         info.length());

    return;
}

/** escribirArchivoDesdeRuta()               11.05.2025   -   hecha
 * Función que escribe la información pasada como
 * string por el ARG2 en el fichero cuya ruta se
 * pasa por el ARG1.
 *
 * Esta función simplemente es una adaptación para
 * llamar a escribirArchivoDesdeDescriptor().
 *
 * ARG1: string, ruta al fichero que escribir.
 * ARG2: string, información a escribir en el fichero.
 */
void escribirArchivoDesdeRuta(string ruta, string info)
{
    int descriptor;
    descriptor = abrirCrearArchivo(ruta);

    //Funció improtante.
    escribirArchivoDesdeDescriptor(descriptor, info);

    cerrarArchivo(descriptor);
    return;
}

/** leerTamanyoFicheroDesdeDescriptor()         10.05.2025   -   hecho
 * Función que lee el tamaño del fichero cuyo
 * descriptor abierto se ha pasado como ARG1.
 *
 *  * Esta función usa una librería diferente
 *  a leerTamanyoFicheroDesdeRuta().
 *
 * ARG1: int, descriptor abierto del fichero.
 * RTRN: int, tamaño del fichero en bytes.
 */
int leerTamanyoFicheroDesdeDescriptor(int descriptor)
{
    struct stat infoFichero;
    fstat(descriptor, &infoFichero);

    return infoFichero.st_size;
}

/** leerTamanyoFicheroDesdeRuta()         10.05.2025   -   hecho
 * Función que lee el tamaño del fichero cuya
 * ruta se ha pasado como ARG1.
 *
 * Esta función usa una librería diferente
 *  a leerTamanyoFicheroDesdeDescriptor().
 *
 * ARG1: string, ruta del fichero.
 * RTRN: int, tamaño del fichero en bytes.
 */
int leerTamanyoFicheroDesdeRuta(string ruta)
{
    struct stat infoFichero;
    if (stat(ruta.c_str(), &infoFichero) == -1)
        cout << "Cagaste..."<< endl;

    return infoFichero.st_size;
}


/** listarFicheros()                 20.04.2025   -   hecha
 * Función que devuelve la lista de ficheros
 * (con la ruta relativa siendo '.' la ruta, ej:  ./carpeta1)
 * que contiene la ruta que se le ha pasado como parámetro
 * usando un vector estándar de C++
 *
 * ARG1: un tring con una ruta ej. ./carpetaEnLaQueBuscar
 * RTRN: vector estándar de strings con todas las
 *
 * Necesita la función auxiliar esDirectorio(string ruta)
 */
vector<string> listarFicheros(string ruta)
{
    vector<string> ficheros;

    //Declaraciones
    struct dirent *datosFicheros;
    DIR * directorio;

    //Abrir directorio
    directorio = opendir(ruta.c_str());

    //Control de errores
    if (directorio == NULL)
    {
        perror("opendir");
        //return -1;
    }


    //Cada vez que haya un fichero se añade
    while((datosFicheros = readdir(directorio)))
    {
        //puts(datosFicheros->d_name);
        if (strcmp(datosFicheros->d_name, "..")!=0 &&        //Si ambos strings son distintos
            strcmp(datosFicheros->d_name,  ".")!=0 &&
            esFichero(ruta+"/"+datosFicheros->d_name))    //Si la ruta es un fichero
        {
            //Guardamos el fichero en la lista
            ficheros.push_back(ruta+"/"+datosFicheros->d_name);
        }
    }

    //Cerramos directorio
    closedir(directorio);

    return ficheros;
}

/** esFichero()                     20.04.2025   -   hecha
 * Función auxiliar
 * Esta función devuelve TRUE si la ruta pasada
 * como único argumento es un fichero. Devolverá
 * un FALSE en caso de ser un directorio.
 */
bool esFichero(string ruta)
{
    bool res = false;

    struct stat infoArchivo;
    if (stat(ruta.c_str(), &infoArchivo) == -1)
        cout << "Cagaste..."<< endl;

    if ((infoArchivo.st_mode & S_IFMT)==S_IFREG)
        res = true;

    return res;
}


/** existeFichero()                 11.05.2025   -   hecha
 * Esta función informa si existe el fichero que se
 * le pasa como primer argumento.
 *
 * Esta función no crea ningún fichero.
 *
 * ARG1: string const&, ruta del fichero a comprobar
 * RTRN: bool, true  -> Si el fichero existe
 *             false -> Si el fichero no existe
 */
bool existeFichero(string const& ruta)
{
    bool esUnFichero = false;
    struct stat infoArchivo;

    if (stat(ruta.c_str(), &infoArchivo) == 0)
        esUnFichero = true;
    else
        esUnFichero = false;

    return esUnFichero;
}


/** fechaModificacionDeFichero()            20.04.2025   -   hecho
 * Función basica general que nos muestra, a partir
 * de la ruta de un archivo, su fecha de modificación.
 *
 * ARG1: string, ruta al archivo.
 * RTRN: int, el valor de la fecha de modificación en crudo.
 *          para mostrar en formato legible: ctime(valor)
 *          Si se usa .st_mtime se mostraran las modificaciones pero no el cambio de nombre
 *          Si se usa .st_ctime la fecha tendrá en cuenta también el cambio de nombre.
 *          El valor de retorno será 0 si no existe el fichero.
 */
time_t fechaModificacionDeFichero(string ruta)
{
    struct stat infoFichero;
    time_t tiempo;

    if (stat(ruta.c_str(), &infoFichero) == -1)
    {
        cout << "Cagaste... leyendo fecha fichero"<< endl;
        tiempo = 0;
    } else
    {
        tiempo = infoFichero.st_ctime;
    }

    //https://linux.die.net/man/2/fstat
    //return infoFichero.st_mtime;    //Fecha de modificación (no cuenta cambio de nombre)
    //return infoFichero.st_ctime;    //Fecha de cambio de estado (cuenta nombre y interior)
    return tiempo;
}

/** mostrarFechaLegible()           20.04.2025   -   hecho
 * Función que muestra de manera legible
 * la fecha pasada como parámetro.
 *
 * ARG1: entero, fecha en crudo de un archivo.
 * RTRN: string, texto traducido a humano.
 */
string mostrarFechaLegible(time_t tiempo)//int fechaCruda)
{
    return ctime(&tiempo);
}



/** Función de pruebas       19.04.2025
 *
 */
void mostrarDatos(string ruta = "./CarpetaOrigen")
{
//    string ruta("./CarpetaOrigen/unDocumentoCualquiera.txt");
    struct stat infoFichero;
    if (stat(ruta.c_str(), &infoFichero) == -1)
        cout << "Cagaste..."<< endl;

    switch (infoFichero.st_mode & S_IFMT) {
        case S_IFBLK:  printf("block device\n");            break;
        case S_IFCHR:  printf("character device\n");        break;
        case S_IFDIR:  printf("directory\n");               break;
        case S_IFIFO:  printf("FIFO/pipe\n");               break;
        case S_IFLNK:  printf("symlink\n");                 break;
        case S_IFREG:  printf("regular file\n");            break;
        case S_IFSOCK: printf("socket\n");                  break;
        default:       printf("unknown?\n");                break;
    }

    printf("File size:                %lld bytes\n",
            (long long) infoFichero.st_size);
    printf("Blocks allocated:         %lld\n",
            (long long) infoFichero.st_blocks);

    printf("Last status change:       %s", ctime(&infoFichero.st_ctime));
    printf("Last file access:         %s", ctime(&infoFichero.st_atime));
    cout << "acceso" << infoFichero.st_atime << endl;
    printf("Last file modification:   %s", ctime(&infoFichero.st_mtime));
    cout << infoFichero.st_mtime << endl;
}


/** obtenerRutaDirectorioDesdeRutaFichero() 12.05.2025   -   SIN PROBAR
 * Función que, pasada la ruta de un fichero
 * en el ARG1, obtiene la carpeta que contiene
 * a dicho fichero y la devuelve en el return.
 *
 * ARG1: string, ruta al fichero del que se desea saber su directorio
 * RTRN: string, ruta del directorio que contiene al fichero
 */
string obtenerRutaDirectorioDesdeRutaFichero(string rutaFichero)
{
    //Declaraciones
    int posicionInicial = 0;
    int posicionActual = -1;
    int ultimaPos = 0;
    string rutaDirectorio;

    //Lógica
    do {
        //Actualiza la posicion a la úlima coincidencia encontrada
        ultimaPos = posicionActual;
        posicionInicial = posicionActual+1;

        //Obtenemos la siguiente posicion de apareción de una '/'
        posicionActual = rutaFichero.find('/',posicionInicial); //devuelve -1 si no encuentra
    } while(posicionActual != -1);

    //Obtenemos la ruta del directorio que contiene el fichero
    rutaDirectorio = rutaFichero.substr(0,ultimaPos+1);

    return rutaDirectorio;
}

