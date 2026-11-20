
/*
 * Copyright 2026 Alex (alex.correu@pm.me)
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

// #pragma once    //https://stackoverflow.com/questions/5776910/what-does-pragma-once-mean-in-c

#include "../includes.hpp"
#include "../namespaces.hpp"

#include "directorios.hpp"

#include "accesoArchivos.hpp"

/** crearDirectorio()
 *
 * Esta función crea un directorio si no existe en la
 * ruta pasada comoparámetro
 *
 * ARG1: string, ruta absoluta o relativa, ej. "./nuevaCarpeta"
 * RTRN: int    0 si no ha creado la carpeta porque ya existía
 *              1 si ha creado carpeta o subcarpetas, ej. "./nuevaCarpeta/nuevaTambien"
 *
 */
int crearDirectorio(string ruta)
{
    //Creamos/accedemos al directorio
    /** rcreate_directories()
     * 0 - no ha creado nada
     * 1 - ha funcionado (crea incluso subdirectorios)
     */
    return (int)fs::create_directories(ruta);
}


/** eliminarDirectorio()               15.04.2025 - Hecho
 *
 * Esta función elimina el directorio que se le pasa
 * como parámetro.
 *
 * Uso:
 *      eliminarDirectorio("./pruebaBorrar");
 *      eliminarDirectorio(); Para borrar la carpeta predeterminada "./datosNube"
 *
 * returns:
 * 0 todo correcto
 * 1 error desconocido
 * 2 directorio no eliminado porque no existe
 */
int eliminarDirectorio(string ruta = " sinruta")
{
    int res = 1;

    //Obtenemos ruta a crear/acceder
    if (ruta == " sinruta")
        ruta =  "./datosNube";
    else
        cout << "\nRuta introducida" << endl;

    //Traducimos de string a cont char*
    const char *rutaC = ruta.c_str();

    /** remove()
     *  remove( const std::filesystem::path& p ) == true
     *
     * Forma parte de la librería filesystem.
     * Borra el directorio deseado.
     *
     * return
     *  false -> se ha borrado el directorio
     *  true  -> No existe el fichero a borrar
     */
    remove( rutaC )
        ? res = 2   //Directorio no eliminado (no existe)
        : res = 0;  //Directorio eliminado
//     Alternativa:
//     if (remove( rutaC ) == true)
//         res = 2;    //Directorio no eliminado, no existe
//     else
//         res = 0;    //Directorio eliminado

    return res;
}




/** listarDirectorios()                 19.04.2025    -    hecha
 * Función recursiva que devuelve la lista de directorios recursivos
 * (con la ruta relativa siendo '.' la ruta, ej:  ./carpeta1)
 * que contiene la ruta que se le ha pasado como parámetro
 * usando un vector estándar de C++
 *
 * NO incluye la carpeta de origen, la pasada como ARG1.
 *
 * ARG1: un string con una ruta ej. "./carpetaEnLaQueBuscar"
 * RTRN: vector estándar de strings con todas las
 *       carpetas y subcarpetas. ej:
 *                 Directorio: ./CarpetaOrigen/4
 *                 Directorio: ./CarpetaOrigen/4/aa
 *                 Directorio: ./CarpetaOrigen/Carpeta sin título
 *                 Directorio: ./CarpetaOrigen/Carpeta sin título/s
 *                 Directorio: ./CarpetaOrigen/Carpeta sin título/Carpeta sin título2
 *
 * Necesita la función auxiliar esDirectorio(string ruta)
 */
vector<string> listarDirectorios(string ruta)
{
    vector<string> directorios;

    //Declaraciones
    struct dirent *datosDirectorios;
    DIR * directorio;

    //Abrir directorio
    directorio = opendir(ruta.c_str());

    //Control de errores

    if (directorio == NULL)
    {
        perror("opendir");
        //return -1;
    }


    //Cada vez que haya un directorio se añade
    while((datosDirectorios = readdir(directorio)))
    {
        //puts(datosDirectorios->d_name);
        if (strcmp(datosDirectorios->d_name, "..")!=0 &&        //Si ambos strings son distintos
            strcmp(datosDirectorios->d_name,  ".")!=0 &&
            esDirectorio(ruta+"/"+datosDirectorios->d_name))    //Si la ruta es un directorio
        {
            //Guardamos el directorio en la lista
            directorios.push_back(ruta+"/"+datosDirectorios->d_name);
            //Comprobamos si tiene subdirectorios para añadirlos
            vector<string> aux = listarDirectorios(ruta+"/"+datosDirectorios->d_name);
            //Añadimos subdirectorios a la lista.
            for (string au : aux)
                directorios.push_back(au);
        }
    }

    //Cerramos directorio
    closedir(directorio);

    return directorios;
}

/** listarDirectoriosConOrigen()          03.05.2025    -    hecha
 * Función recursiva que devuelve la lista de directorios recursivos
 * (con la ruta relativa siendo '.' la ruta, ej:  ./carpeta1)
 * que contiene la ruta que se le ha pasado como parámetro
 * usando un vector estándar de C++
 *
 * INCLUYE la carpeta de origen, la pasada como ARG1.
 *
 * ARG1: un string con una ruta ej. "./carpetaEnLaQueBuscar"
 * RTRN: vector estándar de strings con todas las
 *       carpetas y subcarpetas. ej:
 *                 Directorio: ./CarpetaOrigen/4
 *                 Directorio: ./CarpetaOrigen/4/aa
 *                 Directorio: ./CarpetaOrigen/Carpeta sin título
 *                 Directorio: ./CarpetaOrigen/Carpeta sin título/s
 *                 Directorio: ./CarpetaOrigen/Carpeta sin título/Carpeta sin título2
 *
 * Necesita la función auxiliar esDirectorio(string ruta)
 */
vector<string> listarDirectoriosConOrigen(string ruta)
{
    vector<string> directorios;

    //Declaraciones
    struct dirent *datosDirectorios;
    DIR * directorio;

    //Abrir directorio
    directorio = opendir(ruta.c_str());

    //Control de errores

    if (directorio == NULL)
    {
        perror("opendir");
        //return -1;
    }

    //Añadimos directorio de origen
    directorios.push_back(ruta);

    //Cada vez que haya un directorio se añade
    while((datosDirectorios = readdir(directorio)))
    {
        //puts(datosDirectorios->d_name);
        if (strcmp(datosDirectorios->d_name, "..")!=0 &&        //Si ambos strings son distintos
            strcmp(datosDirectorios->d_name,  ".")!=0 &&
            esDirectorio(ruta+"/"+datosDirectorios->d_name))    //Si la ruta es un directorio
        {
            //Guardamos el directorio en la lista
            directorios.push_back(ruta+"/"+datosDirectorios->d_name);
            //Comprobamos si tiene subdirectorios para añadirlos
            vector<string> aux = listarDirectorios(ruta+"/"+datosDirectorios->d_name);
            //Añadimos subdirectorios a la lista.
            for (string au : aux)
                directorios.push_back(au);
        }
    }

    //Cerramos directorio
    closedir(directorio);

    return directorios;
}

/** listarDirectoriosSinRecursion()     20.04.2025    -    hecha
 * Función NO recursiva que devuelve la lista de directorios
 * (con la ruta relativa siendo '.' la ruta, ej:  ./carpeta1)
 * que contiene la ruta que se le ha pasado como parámetro
 * usando un vector estándar de C++
 *
 * No muestra la carpeta contenedora, la que se pasa com ARG1
 *
 * ARG1: un tring con una ruta ej. ./carpetaEnLaQueBuscar
 * RTRN: vector estándar de strings con todas las
 * carpetas y subcarpetas. ej:
 *                 Directorio: ./CarpetaOrigen/4
 *                 Directorio: ./CarpetaOrigen/Carpeta sin título
 *                      ** NO MOSTRARÁ : **
 *                 Directorio: ./CarpetaOrigen/4/aa
 *                 Directorio: ./CarpetaOrigen/Carpeta sin título/s
 *                 Directorio: ./CarpetaOrigen/Carpeta sin título/Carpeta sin título2
 *
 * Necesita la función auxiliar esDirectorio(string ruta)
 */
vector<string> listarDirectoriosSinRecursion(string ruta)
{
    vector<string> directorios;

    //Declaraciones
    struct dirent *datosDirectorios;
    DIR * directorio;

    //Abrir directorio
    directorio = opendir(ruta.c_str());

    //Control de errores
    if (directorio == NULL)
    {
        perror("opendir");
        //return -1;
    }

    //Cada vez que haya un directorio se añade
    while((datosDirectorios = readdir(directorio)))
    {
        //puts(datosDirectorios->d_name);
        if (strcmp(datosDirectorios->d_name, "..")!=0 &&        //Si ambos strings son distintos
            strcmp(datosDirectorios->d_name,  ".")!=0 &&
            esDirectorio(ruta+"/"+datosDirectorios->d_name))    //Si la ruta es un directorio
        {
            //Guardamos el directorio en la lista
            directorios.push_back(ruta+"/"+datosDirectorios->d_name);
            //NO COMPROBAMOS LAS CARPETAS RECURSIVAMENTE
        }
    }

    //Cerramos directorio
    closedir(directorio);

    return directorios;
}

/** esDirectorio()                 19.04.2025    -    hecha
 * Función auxiliar
 * Esta función devuelve TRUE si la ruta pasada
 * como único argumento es un directorio. Devolverá
 * un FALSE en caso de ser un fichero.
 */
bool esDirectorio(string ruta)
{
    bool res = false;

    struct stat infoDato;
    if (stat(ruta.c_str(), &infoDato) == -1)
        cout << "Cagaste..."<< endl;

    if ((infoDato.st_mode & S_IFMT)==S_IFDIR)
        res = true;

    return res;
}




/** fechaModificacionDeDirectorio()            20.04.2025   -   hecho
 * Función basica general que nos muestra, a partir
 * de la ruta de un directorio, su fecha de cambio (modificación+cambio de nombre),
 * incluyendo la modificación de cualquier elemento que contenga.
 *
 * ARG1: string, ruta al directorio.
 * RTRN: int, el valor de la fecha de modificación en crudo.
 *          para mostrar en formato legible: ctime(valor)
 *          Si se usa .st_mtime se mostraran las modificaciones pero no el cambio de nombre
 *          Si se usa .st_ctime la fecha tendrá en cuenta también el cambio de nombre.
 *          El valor de retorno será 0 si no existe el directorio.
 */
time_t fechaModificacionDeDirectorio(string ruta)
{
    struct stat infoDirectorio;
    time_t fecha;

    if (stat(ruta.c_str(), &infoDirectorio) == -1)
    {
        cout << "Cagaste... leyendo fecha directorio"<< endl;
        fecha = 0;
    } else
    {
        fecha = infoDirectorio.st_ctime;
    }

    //https://linux.die.net/man/2/fstat
    //return infoDirectorio.st_mtime;   //Fecha de modificación (no cuenta cambio de nombre)
    //return infoDirectorio.st_ctime;     //Fecha de cambio de estado (cuenta nombre y interior)
    return fecha;
}


/** directorioVacio()                           02.05.2025   -   hecha
 * Función que nos devuelve un true si la carpeta
 * pasada como parámetro está vacía, es decir, que
 * no contiene ni archivos ni otras carpetas.
 *
 * ARG1: string, ruta a la carpeta que queremos comprobar
 * RTRN: bool, informa sobre el estado de la carpeta:
 *          TRUE:  Si la carpeta está vacía
 *          FALSE: Si la carpeta contiene algun elemento
 */
bool directorioVacio(string ruta)
{
    bool res = true;
    int cantidad = 0;

    //Contamos la cantidad de elementos que contiene la carpeta pasada como argumento.
    cantidad = cantidadDeElementosEnDirectorio(ruta);

    if (cantidad == 0)
        res = true;     //Si no contiene elementos devuelve false
    else
        res = false;

    return res;
}

/** cantidadDeElementosEnDirectorio()           02.05.2025   -   hecha
 * Función que cuenta la cantidad de elementos que hay
 * en la carpeta indicada en el ARG1.
 *
 * ARG1: String, ruta a la carpeta deseada
 * RTRN: int, cantidad de elementos que contiene la carpeta.
 */
int cantidadDeElementosEnDirectorio(string ruta)
{
    int cantidad = 0;
    vector<string> elementosD;
    vector<string> elementosF;

    //Obtenemos los elementos que contiene una carpeta
    elementosD = listarDirectoriosSinRecursion(ruta);
    elementosF = listarFicheros(ruta);

    //Contamos la cantidad de elementos que tiene una carpeta.
    cantidad = elementosD.size() + elementosF.size();

    return cantidad;
}




/** sustituirDirectorioRaiz()           12.05.2025   -   hecha
 * Función que sustiyuye la carpeta raiz de la ruta
 * para introducir otra. Es útil para sincronizar,
 * ya que cuando llega la ruta al servidor contiene
 * la carpeta raiz del cliente, y vicecersa.
 *
 * ARG1: string, ruta completa que queremos adaptar.
 * ARG2: string, nueva raiz que queremos usar.
 * RTRN: string, ruta completa con la raiz nueva.
 */
string sustituirDirectorioRaiz(string ruta, string nuevaRaiz)
{
    string nuevaRuta;

    int posicion = ruta.find('/',3);

    nuevaRuta = nuevaRaiz + ruta.substr(posicion, ruta.length());

    return nuevaRuta;
}






















