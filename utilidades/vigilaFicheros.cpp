
/*
 * Copyright 2026 Alex (alex.correu@pm.me)
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

#include "../includes.hpp"
#include "../namespaces.hpp"

#include "vigilaFicheros.hpp"

#include "../estructuras/listadoFicheros.hpp"
#include "../estructuras/modificaciones.hpp"
#include "../utilidades/accesoArchivos.hpp"
#include "../utilidades/directorios.hpp"


/**  monitorizarFicheros()              23.04.2025
 *
 *  Función que comprueba cada X segundos si se ha
 * modificado algun elemento de la carpeta raiz o su interior
 * En caso de encontrar un cambio la función acaba.
 *
 * Devolverá la lista de ficheros que se han modificado y
 * una lista de las carpetas que contienen alguno de estos
 * ficheros o bien que se han cambiado el nombre. Esta lista
 * de directorios es secundaria.
 *
 * Se comprobará si el fichero se ha modificado respecto al
 * historial local si el ARG3 es false, y con la BD si el
 * ARG3 es true.
 *
 * ARG1: InfoArchivo &, objeto con la información de todas las carpetas
 * ARG2: vector<string> &, vector por referencia que devuelve los directorios modificados
 * ARG3: vector<string> &, vector por referencia que devuelve los ficheros modificados
 * ///### ARG4: & BDiscloud, Objeto para conectar con la BD.
 * ARG5: bool, true para comparar con la bd en vez del fichero local
 * ARG6: int, frecuencia de comprobación en segundos
 * RTRN: void
 *
 * 12.05.2025 - Modificada para usar los structs del objeto Modificaciones
 */
void monitorizarFicheros(InfoArchivo & ia,
                        vector<DirectorioModificado> & directoriosModificados, //vector<string> & directoriosModificados,
                        vector<FicheroModificado> & ficherosModificados, //vector<string> & ficherosModificados,
                        /*BDiscloud & bdloud*/
                        bool BD = true,
                        int frecuenciaDeComprobacionEnSegundos = 1)/*Tiempo predeterminado 1 seg.*/
{
    //Adaptar a comprobar todos los directorios
        //funcion de leer carpetas que contienen elementos dentro.
        //Comprobar fechas de estas carpetas
    //Adatar a nuevos datos (comparar con la lista que tengo)
    //Adaptar a datos eliminados


    //Declaraciones
    bool noHayCambios = true;
    vector<string> listaDirectoriosAComprobar;
    vector<string>::iterator itLista;
    Directorio dirAux;
    time_t fecha1, fecha2;

    //### COSAS PARA COMPROBACIONES
    int contadorInnecesario = 0;

    //Rellenamos la lista de todos los directorios que contiene Discloud
    listaDirectoriosAComprobar = listarDirectoriosConOrigen(ia.leerRutaRaiz());

    //Bucle comprobar cambios + nuevos archivos
    do
    {
        //Pausa
        sleep_for(seconds(frecuenciaDeComprobacionEnSegundos));

        //Comprobamos modificaciones en directorios
        itLista = listaDirectoriosAComprobar.begin();
        do{
            //Obtenemos la fecha actual
            fecha1 = fechaModificacionDeDirectorio(*itLista);
            //Obtenemos la fecha guardada
            if (*itLista == ia.leerRutaRaiz())
            {
                //Obtenemos fecha de la carpeta raiz
                fecha2 = ia.leerFechaModificacion();
            } else
            {
                //Obtenemos struct del directorio.
                dirAux = obtenerDirectorioPorNombre(*itLista,ia);
                //Obtenemos la fecha de modificación anterior
                fecha2 = dirAux.fechaModificacion;
            }
            //Comparamos las fechas
            if (fecha1 != fecha2)
                noHayCambios = false;   //Si hay algún cambio salimos del bucle.
            //Avanzamos el iterador
            itLista++;
        } while (itLista != listaDirectoriosAComprobar.end() && noHayCambios);
        cout << "Comprobación "<<contadorInnecesario<<" hecha." << endl;
        contadorInnecesario++;
    } while (noHayCambios);
    //Salimos del bucle porque hemos encontrado una modificación

        //EMPEZAMOS ANÁLISIS DE LAS MODIFICACIONES ACONTECIDAS:
    //Buscamos los directorios que han sido modificados o sus elementos
    directoriosModificados = detectarDirectoriosLlenosModificadosEnStruct(ia);

    //Buscamos solo los ficheros modificados
    ficherosModificados = detectarFicherosModificadosEnStruct(directoriosModificados,ia);






    //HHHHHHHHHHHHHHHHHHHHHHHH ### ### HHHHHHHHHHHHHH ME HE QUEDADO AQUÍ








    //Buscamos los elementos que han sido Renombrados Eliminados o Creados

//     rutasModificadas = detectarElementoEliminado(ia.leerRutaRaiz(),ia);
//     rutasModificadas = detectarElementoNuevo(ia.leerRutaRaiz(),ia);

    //Actualizar ia
    ia.actualizarDatos();

    return;
}


/**  detectarDirectoriosModificados()              3.05.2025   -   hecha
 *
 * Función que analiza todas las carpetas que contiene
 * archivos, devolviendo una lista con las carpetas
 * que han sido modificadas. Esto significa que puede
 * haber cambiado su nombre y/o alguno de los elementos
 * que contiene.
 *
 * ### No comprueba si el fichero modificado es de una
 *      fecha anterior a la que se tiene guardada, es
 *      decir, que no se tiene en cuenta que haya un
 *      retroceso de versiones y salte el aviso de
 *      un fallo de versiones. Esto NO está contemplado.
 *
 * ARG1: InfoArchivo, objeto con el contenido de los elementos de la nube
 * RTRN: vector<string>, que devuelve la lista de carpetas
 *       que han sido modificadas.
 */
vector<string> detectarDirectoriosLlenosModificados(InfoArchivo &ia)
{
    //Declaraciones
    vector<string> listaDirectoriosAComprobar;      //Lista directorios completa
    vector<string> listaDirectoriosModificados;     //Lista directorios modificados
    Directorio dirAux;                              //Struct directorio auxiliar para aceder a sus elementos.
    time_t fecha1, fecha2;                          //Variables para comparar fechas

    //Obtenemos lista de todos los directorios y subdirectorios de la carpeta raiz
    //Listar directorios (de forma recursiva e incluyendo carpeta raiz)
    listaDirectoriosAComprobar = listarDirectoriosConOrigen(ia.leerRutaRaiz());

    //Si contienen elementos, añadimos los modificados
    for(string s : listaDirectoriosAComprobar)
    {
        //Procesamos solo los directorios que contengan algún elemento
        //ya se pueden haber modificado.
        if (directorioVacio(s) == false)
        {
            //Comprobamos si se ha modificado el directorio (y/o uno de los elementos que contiene)
            fecha1 = fechaModificacionDeDirectorio(s);  //Obtenemos fecha de modificacion actual.

            //Distinguimos la forma de obtener la fecha de la carpeta raiz y el resto.
            if (s == ia.leerRutaRaiz())
            {
                dirAux = obtenerDirectorioPorNombre(s,ia);  //Obtenemos struct del directorio.
                fecha2 = ia.leerFechaModificacion();        //Obtenemos fecha de la carpeta raiz
            } else
            {
                dirAux = obtenerDirectorioPorNombre(s,ia);  //Obtenemos struct del directorio.
                fecha2 = dirAux.fechaModificacion;          //Obtenemos la fecha de modificación anterior
            }

            //Si se ha modificado lo guardamos como modificado
            if( fecha1 != fecha2 )
                listaDirectoriosModificados.push_back(s);   //Lista de los directorios modificados.
        }
    }

    return listaDirectoriosModificados;
}

/**                     12.05.2025   -   SIN PROBAR
 *
 * copia de  detectarDirectoriosLlenosModificados
 *
 *  ### indicativo "CDF" un poco sin sentido aquí
 */ // ### Sin explicacion
vector<DirectorioModificado> detectarDirectoriosLlenosModificadosEnStruct(InfoArchivo &ia)
{
    //Declaraciones
    vector<DirectorioModificado> vectorDirectoriosModificados;
    vector<string> listaDirectoriosAComprobar;      //Lista directorios completa
    vector<DirectorioModificado> listaDirectoriosModificados;     //Lista directorios modificados
    Directorio dirAux;                              //Struct directorio auxiliar para aceder a sus elementos.
    time_t fecha1, fecha2;                          //Variables para comparar fechas
    DirectorioModificado dm;                        //Variable auxiliar para llenar el vector de directorios modificados

    //Obtenemos lista de todos los directorios y subdirectorios de la carpeta raiz
    //Listar directorios (de forma recursiva e incluyendo carpeta raiz)
    listaDirectoriosAComprobar = listarDirectoriosConOrigen(ia.leerRutaRaiz());

    //Si contienen elementos, añadimos los modificados
    for(string s : listaDirectoriosAComprobar)
    {
        //Procesamos solo los directorios que contengan algún elemento
        //ya se pueden haber modificado.
        if (directorioVacio(s) == false)
        {
            //Comprobamos si se ha modificado el directorio (y/o uno de los elementos que contiene)
            fecha1 = fechaModificacionDeDirectorio(s);  //Obtenemos fecha de modificacion actual.

            //Distinguimos la forma de obtener la fecha de la carpeta raiz y el resto.
            if (s == ia.leerRutaRaiz())
            {
                dirAux = obtenerDirectorioPorNombre(s,ia);  //Obtenemos struct del directorio.
                fecha2 = ia.leerFechaModificacion();        //Obtenemos fecha de la carpeta raiz
            } else
            {
                dirAux = obtenerDirectorioPorNombre(s,ia);  //Obtenemos struct del directorio.
                fecha2 = dirAux.fechaModificacion;          //Obtenemos la fecha de modificación anterior
            }

            //Si se ha modificado lo guardamos como modificado
            if( fecha1 != fecha2 )
            {
                dm = DirectorioModificado("CDF",dirAux.ruta,fecha1);  // ### "CDF" Sin mucha utilidad aquí.
                listaDirectoriosModificados.push_back(dm); //Lista de los directorios modificados.
            }
        }
    }

    return listaDirectoriosModificados;
}


/** detectarFicherosModificados()                  3.05.2025   -   hecha
 * Función que busca en la lista de carpetas que se le
 * pasa como ARG1 para encontrar todos los ficheros
 * que se han modificado. Se devolverá una lista con
 * estos elementos.
 *
 * ARG1: vector<string>, lista de directorios que pueden tener elementos modificados.
 * ARG2: InfoArchivo &, objeto que contiene toda la información de los ejementos.
 * RTRN: vector<string>, lista de todos los elementos que han sido modificados.
 */
vector<string> detectarFicherosModificados(vector<string> directoriosModificados, InfoArchivo &ia)
{
    //Declaciones
    Directorio dirAux;
    Fichero fichAux;
    vector<string> listaAuxFicheros;
    vector<string> listaFicherosModificados;
    time_t fecha1, fecha2;

    //Recorremos lista de directorios
    for(string dir: directoriosModificados)
    {
        //Listamos los ficheros que existen en cada directorio
        listaAuxFicheros = listarFicheros(dir);
        //Para cada fichero comprobamos si se ha modificado.
        for(string fich: listaAuxFicheros)
        {
            //Obtenemos fecha actual del archivo
            fecha1 = fechaModificacionDeFichero(fich);
            //Obtenemos al fecha guardada de la última modificación
            fichAux = obtenerFicheroPorNombreYDirectorio(dir,fich,ia);
            fecha2 = fichAux.fechaModificacion;
            //Comparamos fechas
            if( fecha1 != fecha2 && fichAux.ruta != "//")     //Si fecha2 == "//" -> Fichero no existe.
            {
                //Si las fechas difieren añadimos fichero a lista de modificados
                listaFicherosModificados.push_back(fich);
                //Los ficheros que no existen no los contemplamos en esta función
            }
        }
    }

    return listaFicherosModificados;
}

/**                     12.05.2025   -   SIN PROBAR
 *
 * copia de  detectarFicherosModificados
 */ // ### Sin explicacion
vector<FicheroModificado> detectarFicherosModificadosEnStruct(vector<DirectorioModificado> directoriosModificados, InfoArchivo &ia)
{
    //Declaciones
    Directorio dirAux;
    Fichero fichAux;
    vector<string> listaAuxFicheros;
    vector<FicheroModificado> listaFicherosModificados;
    time_t fecha1, fecha2;
    FicheroModificado fm;

    //Recorremos lista de directorios
    for(DirectorioModificado dir: directoriosModificados)
    {
        //Listamos los ficheros que existen actualmente en cada directorio
        listaAuxFicheros = listarFicheros(dir.ruta);
        //Para cada fichero comprobamos si se ha modificado.
        for(string fich: listaAuxFicheros)
        {
            //Obtenemos fecha actual del archivo
            fecha1 = fechaModificacionDeFichero(fich);
            //Obtenemos al fecha guardada de la última modificación
            fichAux = obtenerFicheroPorNombreYDirectorio(dir.ruta,fich,ia);
            fecha2 = fichAux.fechaModificacion;
            //Comparamos fechas
            if( fecha1 != fecha2 && fichAux.ruta != "//")     //Si fecha2 == "//" -> Fichero no existe.
            {
                //Si las fechas difieren añadimos creamos el struct FicheroModificado
                fm = FicheroModificado("CFM",fichAux.ruta,fecha1);
                //Añadimos el struct a la lista de modificados
                listaFicherosModificados.push_back(fm);
                //Los ficheros que no existen no los contemplamos en esta función
            }
        }
    }

    return listaFicherosModificados;
}


/** contarCambiosEnFicheros()                       02.05.2025  -  hecha
 * Función auxiliar que comprueba fichero a fichero cuantos se han
 * modificado. Devolviendo true si hay modificaciones, false si
 * no las hay. Y devolviendo por el ARG3, que es por referencia,
 * la cantidad exacta de modificaciones. Devolverá también por
 * referencia el último archivo comprovado (ARG4).
 *
 * Ejemplo de llamada:
 *
 *                contarCambiosEnFicheros(carpetaContenedora,
 *                                        ia,
 *                                        cantidadFicherosModificados,
 *                                        ultimoFicheroModificado);
 *
 *
 * ARG1 String, ruta contenedora en la que comprobar las carpetas
 * ARG2 InfoArchivo, objeto para comprobar las fechas de modificacion
 * ARG3 int &, entero por referencia que cuenta las modificaciones
 * ARG4 string &, string por referencia que devuelve la última
 *              modificación a la que se ha accedido. Devuelve un
 *              "//" en caso de no haber ningún fichero modificado.
 * RTRN bool, boleano que indicará si hay modificaciones o no.
 *              true: existe 1 o mas modificaciones
 *              false: no hay modificacion de directorios.
 */
bool contarCambiosEnFicheros(string ruta,
                             InfoArchivo &ia,
                             int &cantidadFicherosModificados,
                             string &ultimoFicheroModificado)
{
    //Declaraciones
    bool cambioFichero;
    vector<string> listaFicheros;
    Fichero fichAux;
    time_t fecha1, fecha2;

        //Leer cambios en Ficheros usando de guía el archivo local modificado.
    ultimoFicheroModificado = "//";         //Respuesta predeterminada por seguridad
    cambioFichero = false;                  //Reseteamos variable de aviso
    listaFicheros = listarFicheros(ruta);   //Obtenemos la lista de ficheros locales

    //Comprobar ficheros existentes
    cantidadFicherosModificados = 0;       //Reseteamos cantidad de modificaciones
    for(string fich : listaFicheros)
    {
        //Obtenemos fecha guardada del fichero
        fichAux = obtenerFicheroPorNombreYDirectorio(ruta, fich, ia);
        fecha1 = fichAux.fechaModificacion;

        //Obtenemos fecha de modificacion actual
        fecha2 = fechaModificacionDeFichero(ruta);

        //Comprobamos si hay cambios
        if (fecha1 != fecha2)
        {
            //Si hay cambios avisamos y sumamos
            cambioFichero = true;
            cantidadFicherosModificados++;
            ultimoFicheroModificado = fich;
        }
    }
    return cambioFichero;
}



/** contarCambiosEnDirectorios()                       02.05.2025  -  hecha
 * Función auxiliar que comprueba directorio a directorio cuantos se han
 * modificado. Devolviendo true si hay modificaciones, false si
 * no las hay. Y devolviendo por el ARG3, que es por referencia,
 * la cantidad exacta de modificaciones. Devolverá también por
 * referencia la última carpeta comprovada (ARG4).
 *
 * Ejemplo de llamada:
 *                      contarCambiosEnDirectorios(carpetaContenedora,
 *                                         ia,
 *                                         cantidadDirectoriosModificados,
 *                                         ultimoDirectorioModificado);
 *
 * ARG1 String, ruta contenedora en la que comprobar las carpetas
 * ARG2 InfoArchivo, objeto para comprobar las fechas de modificacion
 * ARG3 int &, entero por referencia que cuenta las modificaciones
 * ARG4 string &, string por referencia que devuelve la última
 *              modificación a la que se ha accedido. Devuelve un
 *              "//" en caso de no haber ningún directorio modificado.
 * RTRN bool, boleano que indicará si hay modificaciones o no.
 *              true: existe 1 o mas modificaciones
 *              false: no hay modificacion de directorios.
 */
bool contarCambiosEnDirectorios(string ruta,
                             InfoArchivo &ia,
                             int &cantidadDirectoriosModificados,
                             string &ultimoDirectorioModificado)
{
    //Declaraciones
    bool cambioDirectorio;
    vector<string> listaDirectorios;
    Directorio dirAux;
    time_t fecha1, fecha2;

    //Leer cambios en Directorios usando de guía el archivo local modificado.
    ultimoDirectorioModificado = "//";      //Respuesta predeterminada por seguridad
    cambioDirectorio = false;               //Reseteamos la variable de aviso
    listaDirectorios = listarDirectoriosSinRecursion(ruta);

    //Comprobamos Directorios existentes
    for(string dir : listaDirectorios)
    {
        //Obtenemos fecha guardada del directorio
        dirAux = obtenerDirectorioPorNombre(dir, ia);
        fecha1 = dirAux.fechaModificacion;

        //Obtenemos fecha de modificación actual
        fecha2 = fechaModificacionDeDirectorio(dir);

        //Comprobamos si hay cambios
        if(fecha1 != fecha2)
        {
            //Si hay cambios, aviso y cuento
            cambioDirectorio = true;
            cantidadDirectoriosModificados++;
            ultimoDirectorioModificado = dir;
        }
    }

    return cambioDirectorio;
}




/** obtenerDirectorioPorNombre()           02.05.2025   -   hecho
 * Función que a partir del arbol de datos y la ruta a
 * un directorio puede localizar el struct que corresponde
 * a tal directorio.
 *
 * ### Esta función debería ser parte del objeto InfoArchivo
 *      Así además podría, creo, poner la lista de directorios en private
 *
 * ARG1: string, ruta al directorio deseado
 * ARG2: InfoArchivo &, objeto por referencia con todos los directorios
 * RTRN: Directorio, devuelve el struct del directorio deseado.
 */
Directorio obtenerDirectorioPorNombre(string rutaContenedora, InfoArchivo &ia)
{
    Directorio dir;
    bool buscando;

    vector<Directorio>::iterator iteradorCarpeta = ia.directorios.begin();
    buscando = true;
    do {
        dir = *iteradorCarpeta;
        if (dir.ruta == rutaContenedora)
            buscando = false;
        else
            iteradorCarpeta++;
    } while(iteradorCarpeta != ia.directorios.end() && buscando);

    //Obtenemos struct de la carpeta contenedora
    dir = *iteradorCarpeta;

    return dir;
}



/** obtenerFicheroPorNombreYDirectorio()    01.05.2025   -   hecho
 *
 * Esta función usa iteradores para obtener a partir
 * de un archivo y la carpeta que lo contiene, el
 * struct con la informacion del archivo.
 *
 * ARG1: String, es la ruta de la carpeta en la que buscar el archivo
 * ARG2: String, ruta del archivo que queremos buscar
 * ARG3: InfoArchivo, el objeto con todos los elementos
 *          sincronizados de discloud y su informacion
 * RTRN: Fichero, se devuelve un tipo fichero con los datos
 *          de este. Existen 2 respuestas alternativas.
 *          -Si la carpeta del ARG1 NO existe, se devuelve fichero.ruta="///"
 *          -Si el fichero del ARG2 NO existe, se devuelve fichero.ruta="//"
 */
Fichero obtenerFicheroPorNombreYDirectorio(string rutaContenedora, string ficheroABuscar, InfoArchivo &ia)
{

    /*Malditos iteradores (esto ni caso)
    //Obtengo struct directorio
    std::vector<Directorio>::iterator itCarpeta =
            std::find_if (ia.directorios.begin(),
                          ia.directorios.end(),
                          [&rutaContenedora](string s) {return rutaContenedora == s.ruta;});
    //en *it tengo el struct del directorio contenedor

    //Busco el struct carpeta en la lista de carpetas del directorio
    std::vector<Fichero>::iterator itFichero =
            std::find_if (itCarpeta.ficheros.begin(),
                          itCarpeta.ficheros.end(),
                          [&ficheroABuscar](string ss) {return ficheroABuscar == ss.ruta;});
    */

    //Declaraciones
    bool buscando;      //Variable para salir del bucle de busqueda
    Directorio dir;     //Variable auxialiar para guardar un tipo directorio
    Fichero fich;       //Variable auxialiar para guardar un tipo fichero

    //Busqueda del struct de la carpeta contenedora
    vector<Directorio>::iterator iteradorCarpeta = ia.directorios.begin();
    buscando = true;
    do {
        dir = *iteradorCarpeta;
        if (dir.ruta == rutaContenedora)
            buscando = false;
        else
            iteradorCarpeta++;
    } while(iteradorCarpeta != ia.directorios.end() && buscando);

    //Obtenemos struct de la carpeta contenedora
    dir = *iteradorCarpeta;

    //Preparación de la busqueda del fichero
    if(buscando == true)
    {
        //Caso de que no exista la carpeta introducida
        fich.ruta = "///";
        buscando = false;
    }
    else
    {
        //Si la carpeta existe podemos buscar en ella.
        buscando = true;
        //Busqueda del struct del archivo deseado
        std::vector<Fichero>::iterator iteradorArchivo = dir.ficheros.begin();
        while(iteradorArchivo != dir.ficheros.end() && buscando)
        {
            fich = *iteradorArchivo;
            if (fich.ruta == ficheroABuscar)
                buscando = false;
            else
                iteradorArchivo++;
        }

        //Obtenermos el struct del fichero deseado
        if (buscando == true)   //Fichero no encontrado
        {
            fich.ruta = "//";
        }
        else
        {
            fich = *iteradorArchivo;
        }
    }

    //Devolvemos el struct del fichero deseado
    return fich;
}






