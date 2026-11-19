
/*
 * Copyright 2026 Tu Nombre y colaboradores
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */


#include "../includes.hpp"
#include "../namespaces.hpp"

#include "./modificaciones.hpp"

        /**
         * CEN - Cliente Encendido Nuevo (nunca sincronizado)
         * CEV - Cliente Encendido Viejo (ya se ha sincronizado antes)
         * CMS - Cliente con Modificaciones Serializadas
         * CFM - en Cliente Fichero Modificado
         * CFN - en Cliente Fichero con cambio de Nombre
         * CFE - en Cliente Fichero Eliminado
         * CFC - en Cliente Fichero Creado
         * CFV - en Cliente Fichero Movido
         * CDN - en Cliente Directorio con cambio de Nombre
         * CDE - en Cliente Directorio Eliminado
         * CDC - en Cliente Directorio Creado
         * CDV - en Cliente Directorio Movido
         *
         */




//      CONSTRUCTORES DE STRUCTS
/**             12.04.25   -   SIN PROBAR
 */
FicheroModificado::FicheroModificado()
{
    this->mod = "//";
    this->ruta = "//";
    this->fechaModificacion = -1;
}
/** CONSTRUCTOR DE STRUCT FicheroModificado      12.04.25   -   SIN PROBAR
 * Función de constructor que inicializa las
 * variables del struct FicheroModificado,
 * así de esta forma crearlo con los datos
 * directamente.
 *
 * ARG1: string, modificacion que presenta (existen varias)
 * ARG2: string, ruta del fichero modificado.
 * ARG3: time_t, fecha de la última modificacion del fichero.
 */
FicheroModificado::FicheroModificado(string mod,
                      string ruta,
                      time_t fechaModificacion)
{
    this->mod = mod;
    this->ruta = ruta;
    this->fechaModificacion = fechaModificacion;
}
DirectorioModificado::DirectorioModificado()
{
    this->mod = "//";
    this->ruta = "//";
    this->fechaModificacion = -1;
}
/** CONSTRUCTOR DE STRUCT DirectorioModificado     12.04.25   -   SIN PROBAR
 * Función de constructor que inicializa las
 * variables del struct DirectorioModificado,
 * así de esta forma crearlo con los datos
 * directamente.
 *
 * ARG1: string, modificacion que presenta (existen varias)
 * ARG2: string, ruta del directorio modificado.
 * ARG3: time_t, fecha de la última modificacion del directorio.
 */
DirectorioModificado::DirectorioModificado(string mod,
                         string ruta,
                         time_t fechaModificacion)
{
    this->mod = mod;
    this->ruta = ruta;
    this->fechaModificacion = fechaModificacion;
}





//      FUNCIONES DE LA CLASE "MODIFICACIONES"

/**     CONSTRUCTOR #1                    12.05.2025   -   SIN PROBAR
 * Función constructor que crea el objeto Modificaciones
 * como no hay nada que hacer se limpian los vectores
 * por si hubiese algo.
 */
Modificaciones::Modificaciones()
{
    this->ficheros.clear();
    this->directorios.clear();
}
/**     CONSTRUCTOR #2                    12.05.2025   -   SIN PROBAR
 * Función constructor que inicializa los vectores
 * de ficheros y directorios que tiene la estructura.
 */
Modificaciones::Modificaciones(vector<FicheroModificado> ficherosMod,
                               vector<DirectorioModificado> directoriosMod)
{
    this->ficheros = ficherosMod;
    this->directorios = directoriosMod;
}

    //Funciones

/** vaciarObjeto()                        12.05.2025   -   SIN PROBAR
 * Función que vacia todas las variables del
 * objeto, ya sea para reusarlo o para
 * asegurarse de que está vacío antes
 * de añadir elementos.
 */
void Modificaciones::vaciarObjeto()
{
    this->ficheros.clear();
    this->directorios.clear();
    return;
}

/** vaciarFicheros()                        12.05.2025   -   SIN PROBAR
 * Función que vacia la lista de ficheros
 * del objeto, ya sea para reusarla o para
 * asegurarse de que está vacía antes
 * de añadir elementos.
 */
void Modificaciones::vaciarFicheros()
{
    this->ficheros.clear();
    return;
}

/** vaciarDirectorios()                        12.05.2025   -   SIN PROBAR
 * Función que vacia la lista de directorios
 * del objeto, ya sea para reusarla o para
 * asegurarse de que está vacía antes
 * de añadir elementos.
 */
void Modificaciones::vaciarDirectorios()
{
    this->directorios.clear();
    return;
}

    //Funciones I/O

/** anyadirNuevoFichero()                     12.05.2025   -   SIN PROBAR
 * Función básica de I/O para añdir un fichero
 * a la lista del objeto.
 *
 * ARG1: FicheroModificado, struct con el fichero a añadir.
 */
void Modificaciones::anyadirNuevoFichero(FicheroModificado fm)
{
    this->ficheros.push_back(fm);
    return;
}

/** anyadirNuevoDirectorio()                 12.05.2025   -   SIN PROBAR
 * Función básica de I/O para añdir un directorio
 * a la lista del objeto.
 *
 * ARG1: DirectorioModificado, struct con el directorio a añadir.
 */
void Modificaciones::anyadirNuevoDirectorio(DirectorioModificado dm)
{
    this->directorios.push_back(dm);
    return;
}

/** guardarListaFicheros()                  12.05.2025   -   SIN PROBAR
 * Función que guarda el vector pasado
 * como argumento como nuevo vector
 * de ficheros modificados.
 *
 * ARG1: vector<FicheroModificado>, nuevo vector de ficheros.
 */
void Modificaciones::guardarListaFicheros(vector<FicheroModificado> vfm)
{
    this->ficheros = vfm;
    return;
}

/** guardarListaDirectorios()                  12.05.2025   -   SIN PROBAR
 * Función que guarda el vector pasado
 * como argumento como nuevo vector
 * de directorios modificados.
 *
 * ARG1: vector<DirectorioModificado>, nuevo vector de directorios.
 */
void Modificaciones::guardarListaDirectorios(vector<DirectorioModificado> vdm)
{
    this->directorios = vdm;
    return;
}

/** guardarListasFicherosYDirectorios()         12.05.2025   -   SIN PROBAR
 * Función que guarda los vectores pasados
 * como argumentos como nuevos vectores
 * de ficheros y directorios modificados
 * respectivamente.
 *
 * ARG1: vector<FicheroModificado>, nuevo vector de ficheros.
 * ARG2: vector<DirectorioModificado>, nuevo vector de directorios.
 */
void Modificaciones::guardarListasFicherosYDirectorios(vector<FicheroModificado> vfm,
                                       vector<DirectorioModificado> vdm)
{
    this->ficheros = vfm;
    this->directorios = vdm;
    return;
}

/** leerListaFicheros()                         12.05.2025   -   SIN PROBAR
 * Función que devuelve la lista de
 * ficheros que contiene el objeto.
 *
 * RTRN: vector<FicheroModificado>, lista de ficheros modificados.
 */
vector<FicheroModificado> Modificaciones::leerListaFicheros()
{
    return this->ficheros;
}

/** leerListaDirectorios()                     12.05.2025   -   SIN PROBAR
 * Función que devuelve la lista de
 * directorios que contiene el objeto.
 *
 * RTRN: vector<DirectorioModificado>, lista de directorios modificados.
 */
vector<DirectorioModificado> Modificaciones::leerListaDirectorios()
{
    return this->directorios;
}

//Serializacion

        /**
         *  ESTRUCTURA:
         *
         * AAA -> Tres primeras letras del mensaje
         *          Son el índice inicial, indica qué
         *          contiene y el estado del cliente.
         *
         * En bucle:
         *      BBB -> Tres letras, infica la modificación
         *          que sigue a estas tres letras
         *      En bucle:
         *          CC -> indica qué dato en concreto sigue
         *                a estas letras.
         *
         *    ==> Todos los campos están separados por '\n' <==
         *    ==> Salvo los CC de los Datos.                <==
         *
         * Ej:  AAABBBCCDato1CCDato2BBBCCDato3CCdato4
         *      ^Tipo de mensaje (ej recibir modificaciones)
         *         ^Informa que modificacion (ej, fichero modificado)
         *            ^Indica que informacion le sigue (ej. una ruta de fichero)
         *              ^La información de la ruta
         *                   ^Infidica que información le sigue (ej. una fecha de fichero)
         *                     ^La información de la fecha
         */

        /**
         *  ÍNDICE INICIAL (qué objeto viene)
         * NEW - Solicita conexión con usuario y contraseña (inicio sesion)
         * OUT - Solicita cerrar sesión.
         * CEN - Cliente Encendido Nuevo (nunca sincronizado)
         * CEV - Cliente Encendido Viejo (ya se ha sincronizado antes)
         * CMS - Cliente con Modificaciones Serializadas
         *
         *  INDICE SECUNDARIO (cuando el principal es CMS)
         * CFM - en Cliente Fichero Modificado
         * CFN - en Cliente Fichero con cambio de Nombre
         * CFE - en Cliente Fichero Eliminado
         * CFC - en Cliente Fichero Creado
         * CFV - en Cliente Fichero Movido
         * CDF - en Cliente Directorio nueva fecha modificacion (elemento interior cambiado)
         * CDN - en Cliente Directorio con cambio de Nombre
         * CDE - en Cliente Directorio Eliminado
         * CDC - en Cliente Directorio Creado
         * CDV - en Cliente Directorio Movido
         *
         *  ÍNDICE PARCIAL (qué parte del objeto es)
         * RR - Ruta Raiz del objeto
         * RF - Fecha Modificacion de RR
         * DR - Ruta de Directorio
         * DF - Fecha de modificacion de Directorio
         * SD - Subdirectorio
         * FR - Ruta de Fichero
         * FF - fecha de modificacion de fichero
         */

string Modificaciones::serializarEnString()
{
    string serializacion = "";

    for(FicheroModificado fm : this->ficheros)
    {
        serializacion += fm.mod + "\n";
        serializacion += "FR" + fm.ruta + "\n";
        serializacion += "FF" + to_string(fm.fechaModificacion) + "\n";
    }

    for(DirectorioModificado dm : this->directorios)
    {
        serializacion += dm.mod + "\n";
        serializacion += "DR" + dm.ruta + "\n";
        serializacion += "DF" + to_string(dm.fechaModificacion) + "\n";
    }

    return serializacion;
}

/** desSerializar()         12.05.2025   -   SIN PROBAR
 *
 */ // ###
bool Modificaciones::desSerializar(string datos)
{
    bool res = true;    //False si no detecta los indicativos en datos
    int posicionInicial = 0;
    int posicionDeSalto = 0;
    vector<string> lineas;
    vector<string>::iterator iterador;
    string ref, dato, auxIt;
    DirectorioModificado dirAux;
    FicheroModificado fichAux;

    /**
     * RR - Ruta Raiz del objeto
     * RF - Fecha Modificacion de RR
     * DR - Ruta de Directorio
     * DF - Fecha de modificacion de Directorio
     * SD - Subdirectorio
     * FR - Ruta de Fichero
     * FF - fecha de modificacion de fichero
     */

    //Ponemos cada línea del fichero en un string del vector lineas
    do{
        posicionDeSalto = datos.find('\n',posicionInicial);
        int resta = posicionDeSalto-posicionInicial;
        auxIt = datos.substr(posicionInicial,resta);
        if (auxIt !="\n")   //Evitamos líneas vacías, como la última del fichero
        {
            lineas.push_back( auxIt );
        }
        posicionInicial = posicionDeSalto +1;
    } while(posicionDeSalto != -1);

    //Reseteamos variables
    this->vaciarObjeto();
    //Obtenermos el iterador
    iterador = lineas.begin();
    //Obtenemos el string en cuestión
    auxIt = *iterador;
    //Obtenemos los indicadores
    ref = auxIt.substr(0,2);
    //Obtenemos la información
    dato = auxIt.substr(2,auxIt.length()-2);
    while (iterador != lineas.end())
    {
            //Actuamos según los indicadores
        //Si estamos ante el índice segundario (indica que modificación tiene)
        if(ref=="CF"||ref=="CD")
        {
            //Añadimos la letra que falta a la referencia.
            ref += dato[0];

            //Guardamos la referencia donde toque.
            if (ref[1] == 'F')      //Se trata de un fichero
            {
                //Guardamos la modificacion
                fichAux.mod = ref;
                //Pasamos al siguiente campo
                desSerializarAuxiliarIterador(
                            iterador,auxIt,ref,dato,lineas);

                //Guardamos la ruta
                fichAux.ruta = dato;
                //Pasamos al siguiente campo
                desSerializarAuxiliarIterador(
                            iterador,auxIt,ref,dato,lineas);

                //Guaradamos la fecha de modificacion
                fichAux.fechaModificacion = stoi(dato);
                //Pasamos al siguiente campo
                desSerializarAuxiliarIterador(
                            iterador,auxIt,ref,dato,lineas);

                //Guardamos el fichero en la lista
                ficheros.push_back(fichAux);
            }else //ref[1] == 'D'   //Se trata de un directorio
            {
                //Guardamos la modificacion
                dirAux.mod = ref;
                //Pasamos al siguiente campo
                desSerializarAuxiliarIterador(
                            iterador,auxIt,ref,dato,lineas);

                //Guardamos la ruta
                dirAux.ruta = dato;
                //Pasamos al siguiente campo
                desSerializarAuxiliarIterador(
                            iterador,auxIt,ref,dato,lineas);

                //Guaradamos la fecha de modificacion
                dirAux.fechaModificacion = stoi(dato);
                //Pasamos al siguiente campo
                desSerializarAuxiliarIterador(
                            iterador,auxIt,ref,dato,lineas);

                //Guardamos el fichero en la lista
                directorios.push_back(dirAux);
            }
        }
        else
        {
            //Algo ha fallado en los datos del fichero.
            iterador = lineas.end();
            res = false;
        }
    }

    return res;
}

/** desSerializarAuxiliarIterador()      12.05.2025   -   SIN PROBAR
 * Función auxiliar de desSerializar() para
 * avanzar el iterador y leer correctamente el vector
 * que se esta desserializando.
 *
 * Función inspirada en mi otra función:
 *  InfoArchivo::desSerializarDesdeStringAuxiliarIterador()
 *
 * ARG1: vector<string>::iterator &, iterador del vector
 *                      con los datos a desserializar
 * ARG2: string &, contenido del string al que apunta el iterador.
 * ARG3: string &, referencia para saber qué dato contiene ARG2.
 * ARG4: string &, dato extraido de ARG2.
 * ARG5: vector<string> &, vector original sobre el que iteramos.
 */
void Modificaciones::desSerializarAuxiliarIterador(
                        vector<string>::iterator & iterador,
                        string & auxIt,
                        string & ref,
                        string & dato,
                        vector<string> & lineas)
{
    if (iterador != lineas.end())
    {
        //Pasamos al siguiente campo
        iterador++;
        //Obtenemos el string en cuestión
        auxIt = *iterador;
        if (auxIt.length() != 0)
        {
            ref = auxIt.substr(0,2);
            dato = auxIt.substr(2,auxIt.length()-2);
        } else iterador ++;
    } else ref = "//";
    return;
}










