
/*
 * Copyright 2026 Tu Nombre y colaboradores
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

#include "../includes.hpp"
#include "../namespaces.hpp"

#include "../utilidades/directorios.hpp"
#include "../utilidades/accesoArchivos.hpp"

#include "./listadoFicheros.hpp"

//Contructores
/**     CONSTRUCTOR #1                    09.05.2025   -   hecho
 * Crea el objeto pero no inicializa ningún
 * archivo. Solamente se asigna un valor
 * imposible a la ruta raiz para poder
 * confirmar que el objeto no esá cargado.
 */
InfoArchivo::InfoArchivo()
{
    this->rutaRaiz = "//";
}
/**     CONSTRUCTOR #2                   20.04.2025   -   hecho
 * Crea el objeto y le asigna todos los valores
 * que necesita para funcionar.
 *
 * Estos valores son la rutaRaiz donde Discloud
 * sincronizará los datos, la fecha de la última
 * modificación de este directorio y la lista
 * de elementos que ésta contiene.
 *
 * ARG1: string, ruta raiz de Discloud.
 */
InfoArchivo::InfoArchivo(string nuevaRuta)
{
    this->rutaRaiz = nuevaRuta;
    this->fechaModificacion = fechaModificacionDeDirectorio(nuevaRuta);
    rellenarDirectoriosYFicheros();
}


/** inicializarInfoArchivo()                   09.05.2025   -   hecho
 * Función que rellena el objeto en caso de usar el constructor
 * que no inicializa los valores. O en caso de querer resetear
 * por completo los datos del objeto.
 *
 * ARG1: string, ruta a la carpeta raiz de Discloud.
 */
void InfoArchivo::inicializarInfoArchivo(string nuevaRuta)
{
    //Guardamos la ruta raiz de Discloud
    this->rutaRaiz = nuevaRuta;

    //Guardamos la fecha de modificación de la ruta raiz
    this->fechaModificacion = fechaModificacionDeDirectorio(nuevaRuta);

    //Rellenamos la lista de directorios con los datos locales actuales.
    rellenarDirectoriosYFicheros();

    return;
}


/**  rellenarDirectoriosYFicheros()                20.04.2025   -   hecho
 *
 * Función que lee y genera la lista de structs Directorio
 * con los elementos y directorios que contiene cada uno.
 * Incluyendo al final la ruta raiz.
 *
 */
void InfoArchivo::rellenarDirectoriosYFicheros()
{
    //Borramos el contenido(si lo hay) del vector. (útil para actualizar los datos)
    this->directorios.clear();

    //Listar todos los directorios y subdirectorios
    vector<string> listaDirectorios = listarDirectorios(this->rutaRaiz);

    //Tenemos en cuenta los elementos de la carpeta raiz
    listaDirectorios.push_back(this->rutaRaiz);

    //Rellenamos cada directorio que encontramos
    for (string directorio : listaDirectorios)
    {
        //Creamos struct directorio que estamos explorando
        Directorio nuevoDirectorio;

        //Añadimos la ruta del directorio que estamos explorando
        nuevoDirectorio.ruta = directorio;

        //Añadimos la fecha de la última modificación
        nuevoDirectorio.fechaModificacion = fechaModificacionDeDirectorio(directorio);

        //Añadimos lista de todos los ficheros que hay dentro del directorio que estamos explorando
        vector<string> listaficheros = listarFicheros(directorio);
        for(string rutaFich : listaficheros)
        {
            nuevoDirectorio.ficheros.push_back(generarFichero(rutaFich));
        }

        //Añadimos lista de  todos los directorios que hay dentro del directorio que estamos explorando
        nuevoDirectorio.subdirectorios = listarDirectoriosSinRecursion(directorio);

        //Rellenamos cada uno de los elementos del vector de structs Directorio
        this->directorios.push_back(nuevoDirectorio);
    }


    return;
}

/** mostrarDirectoriosYFicheros()                20.04.2025   -   hecho
 *
 * Función que muestra por pantalla la lista de
 * directorios y los ficheros y subdirectorios
 * que estos contienen.
 *
 */
void InfoArchivo::mostrarDirectoriosYFicheros()
{
    //Una iteración por diectorio
    for (Directorio dir : this->directorios)
    {
        cout << "\nRuta: " << dir.ruta << " -Ult.Mod.: " << mostrarFechaLegible(dir.fechaModificacion) << endl;
        cout << endl;
        cout << "\t\tDIRECTORIOS:" << endl;
        for(string directorio : dir.subdirectorios)
        {
            cout << "\t" << directorio << endl;
            //cout << "\t " << mostrarFechaLegible(this->directorio.fechaModificacion) << endl;
        }
        cout << "\t\tFICHEROS:" << endl;
        for(Fichero fichero : dir.ficheros)
        {
            cout << "\tFecha:" << fichero.fechaModificacion << "-Ruta: "<< fichero.ruta << endl;
            cout << "\t " << mostrarFechaLegible(fichero.fechaModificacion) << endl;
        }
        cout << "### ### ###" << endl;
    }

    cout << "\t Fecha de carpeta raiz: " << mostrarFechaLegible(this->fechaModificacion) << endl;

    return;
}

/**  generarFichero()                            20.04.2025   -   hecho
 * Función que crea un elemento Fichero a partir
 * de la ruta de un fichero y lo devuelve en el
 * return.
 */
Fichero InfoArchivo::generarFichero(string rutaFich)
{
    Fichero fichero;
    fichero.ruta = rutaFich;
    fichero.fechaModificacion = fechaModificacionDeFichero(rutaFich);
    return fichero;
    ///return fichero(rutaFich,fechaCreacionDeFichero(rutaFich));
}



/** leerFechaModificacion()                     23.04.2025    -    hecho
 * Función que devuelve el valor de la fecha de
 * la úlitima modificación de la ruta raiz.
 *
 * RTRN time_t, valor del tiempo en crudo
 */
time_t InfoArchivo::leerFechaModificacion()
{
    return this->fechaModificacion;
}



/**  leerListaDirectorios()                   23.04.2025    -    hecho
 * Función que devuelve la lista de structs Directorio
 *
 * RTRN: vector<Directorio>, lista completa de rirectorios y sus propiedades
 */
vector<Directorio> InfoArchivo::leerListaDirectorios()
{
    return this->directorios;
}


/** leerRutaRaiz()                             01.05.2025   -   hecho
 * Funcion simple que devuelve la ruta de la carpeta
 * raiz de Discloud.
 *
 * RTRN: String, ruta raiz de la carpeta sincronizada.
 */
string InfoArchivo::leerRutaRaiz()
{
    return this->rutaRaiz;
}


/**     12.05.2025   -   SIN PROBAR
 *
 */
void InfoArchivo::modificarFechaFicheroSinDirectorio(string rutaFichero, time_t nuevaFecha)
{
    string rutaDirectorio =
        obtenerRutaDirectorioDesdeRutaFichero(rutaFichero);

    modificarFechaFichero(rutaDirectorio,
                          rutaFichero,
                          nuevaFecha);

    return;
}

/**     12.05.2025   -   SIN PROBAR
 *
 */
void InfoArchivo::modificarFechaFichero(string rutaDirectorio,
                                   string rutaFichero,
                                   time_t nuevaFecha)
{
    Directorio* dirPrt = obtenerPrtDirectorio(rutaDirectorio);

    //int tam = *dirPrt.ficheros.size();    <== Así no se usa el acceso a cosas desde punteros
    int tam = dirPrt->ficheros.size();//    <== Así sí
    int i = 0;

    while(i<=tam)
    {
        if(dirPrt->ficheros[i].ruta == rutaFichero)
        {
            dirPrt->ficheros[i].fechaModificacion = nuevaFecha;
            i = tam;
        }
        i++;
    }

    return;
}

/** obtenerPrtDirectorio()  12.05.2025   -   SIN PROBAR
 */ //### sin escribir
Directorio* InfoArchivo::obtenerPrtDirectorio(string rutaDirectorio)
{
    Directorio* dirPrt;
    //dirPrt = nullptr;

    long unsigned int i = 0;
    while( i <= this->directorios.size())
    {
        if(this->directorios[i].ruta == rutaDirectorio)
        {
            dirPrt = &this->directorios[i];
            i = this->directorios.size();
        } else {
            i++;
        }
    }

    return dirPrt;
}


/** InfoArchivo:actualizarDatos()               5.5.25   -   hecha
 * Función que al llamarla actualiza todos los datos
 * escepturando la rutaRaiz que no cambia. Para actualizar
 * las fechas de los archivos que han sido modificados y
 * ya estan actualizados.
 *
 */
void InfoArchivo::actualizarDatos()
{
    //Actualizamos la fecha de la ruta raiz
    this->fechaModificacion = fechaModificacionDeDirectorio(this->rutaRaiz);
    //Eliminamos la lista de directorios(y ficheros) actual
    this->directorios.clear();
    //Rellenamos la lista de directorios y ficheros de nuevo.
    this->rellenarDirectoriosYFicheros();

    return;
}


/** serializarEnRuta()                      11.05.2025   -   hecha
 * Función que (serializa) convierte el objeto InfoArchivo
 * en un string y posteriormente lo guarda el fichero
 * pasado como argumento.
 *
 * Esta funcion solo se limita a llamar a funciones
 * que ya estan hechas para facilitar el uso de estas y
 * el código final.
 *
 * ARG1: string, ruta al archivo destino de la serializacion.
 */
void InfoArchivo::serializarEnRuta(string rutaFichero)
{
    //Serializa este objeto entero
    string serializacion = this->serializarEnString();

    //Abre, guarda la serializacion y cierra el archivo
    escribirArchivoDesdeRuta(rutaFichero,serializacion);

    return;
}

/** serializarEnString()                     10.05.2025   -   hecha
 * Función que serializa todos los datos de este
 * objeto InfoArchivo. Es decir, que transforma
 * todos los datos en texto, en concreto, en una
 * variable string.
 *
 * Esta función es útil para almacenar en memoria
 * no volatil el estado de la nube o para enviar
 * el estado de la nube al servidor.
 *
 * El algoritmo de serializacion es de invención proia y se
 * basa en almacenar cada dato en una línea (separados por '\n')
 * precedidos de dos caracteres que indicarán qué contiene la
 * línea en cuestión. Ej.:  "DR./carpeta\n"
 *                              "DR" -> El dato es la Ruta a un Directorio
 *                              "./carpeta\n" -> Dato
 *
 * RTRN: string, devuelve el objeto serializado en formato string.
 */
string InfoArchivo::serializarEnString()
{
    string resultado =  "";

    /**
     * RR - Ruta Raiz del objeto
     * RF - Fecha Modificacion de RR
     * DR - Ruta de Directorio
     * DF - Fecha de modificacion de Directorio
     * SD - Subdirectorio
     * FR - Ruta de Fichero
     * FF - fecha de modificacion de fichero
     */

    resultado += "RR" + this->rutaRaiz + "\n";
    resultado += "RF" + to_string(this->fechaModificacion) + "\n";

    for(Directorio d : this->directorios)
    {
        resultado += "DR" + d.ruta + "\n";
        resultado += "DF" + to_string(d.fechaModificacion) + "\n";
        for(string s: d.subdirectorios)
        {
            resultado += "SD" + s + "\n";
        }
        for(Fichero f: d.ficheros)
        {
            resultado += "FR" + f.ruta + "\n";
            resultado += "FF" + to_string(f.fechaModificacion) + "\n";
        }
    }

    return resultado;
}


/** desSerializarDesdeRuta()                 10.05.2025   -   hecha
 * Función que pasada la ruta a un fichero cuyo contenido
 * es la serialización de un objeto InfoArchivo, lo lee
 * y carga los datos en el objeto InfoArchivo desde el
 * que se le ha llamado.
 *
 * Esta función lee el fichero y llama a la función que
 * serializa -> desSerializarDesdeString().
 *
 * ARG1: string, ruta al fichero que queremos desserializar.
 * RTRN: bool, true  -> InfoArchivo cargado correctamente.
 *             false -> Datos en fichero de origen erroneos.
 */
bool InfoArchivo::desSerializarDesdeRuta(string rutaFichero)
{
    bool todoBien = true;
    string datos;

    datos = leerArchivoDesdeRuta(rutaFichero);

    todoBien =this->desSerializarDesdeString(datos);

    return todoBien;
}

/** desSerializarDesdeString()                      10.05.2025   -   hecha
 *
 *
 */  //### Falta la info
bool InfoArchivo::desSerializarDesdeString(string datos)
{
    bool res = true;
    int posicionInicial = 0;
    int posicionDeSalto = 0;
    vector<string> lineas;
    vector<string>::iterator iterador;
    string ref, dato, auxIt;
    Directorio dirAux;
    Fichero fichAux;

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

    //Reseteamos variable
    this->directorios.clear();
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
        //Si se trata de la ruta raiz del objeto
        if (ref == "RR")
        {
            this->rutaRaiz = dato;

            //Pasamos al siguiente campo
            desSerializarDesdeStringAuxiliarIterador(
                        iterador,auxIt,ref,dato,lineas);
//         }
        //Si se trata de la fecha del directorio raiz del objeto
//         if (ref == "RF")
//         {
            this->fechaModificacion = stoi(dato);

            //Pasamos al siguiente campo
            desSerializarDesdeStringAuxiliarIterador(
                        iterador,auxIt,ref,dato,lineas);
        }

        //Si se trata de un tipo directorio
//         while (ref == "DR")
        else if (ref == "DR")
        {
            /**Directorio contiene
             * DR - Ruta
             * DF - Fecha de modificación
             * SD - Subdirectorios (vector de strings)
             * FR - Vector de Ficheros
             */
            //Reseteamos variables
            dirAux.ruta = "";
            dirAux.fechaModificacion = 0;
            dirAux.subdirectorios.clear();
            dirAux.ficheros.clear();

            //Guardamos la ruta
            dirAux.ruta = dato;

            //Pasamos al siguiente campo
            desSerializarDesdeStringAuxiliarIterador(
                        iterador,auxIt,ref,dato,lineas);

            //Obtenemos la fecha
//             if (ref == "DF")
            dirAux.fechaModificacion = stoi(dato);

            //Pasamos al siguiente campo
            desSerializarDesdeStringAuxiliarIterador(
                        iterador,auxIt,ref,dato,lineas);

            //Si obtenemos subdirectorios
            while(ref == "SD")
            {
                //Guardamos el subdirectorio
                dirAux.subdirectorios.push_back(dato);

                //Pasamos al siguiente campo
                desSerializarDesdeStringAuxiliarIterador(
                        iterador,auxIt,ref,dato,lineas);
            }

            //Si obtenemos ficheros
            while(ref == "FR")
            {
                /** Ficheros
                 * FR - Ruta del fichero
                 * FF - Fecha del fichero
                 */

                //Reseteamos variables
                fichAux.ruta = "";
                fichAux.fechaModificacion = 0;

                //Guardamos la ruta al dato.
                fichAux.ruta = dato;

                //Pasamos al siguiente campo
                desSerializarDesdeStringAuxiliarIterador(
                        iterador,auxIt,ref,dato,lineas);

                //Guardamos la fecha de modificación
                //if (ref == "FF")
                fichAux.fechaModificacion = stoi(dato);

                //Añadimos fichero a la lista
                dirAux.ficheros.push_back(fichAux);

                //Pasamos al siguiente campo
                desSerializarDesdeStringAuxiliarIterador(
                        iterador,auxIt,ref,dato,lineas);
            }

            //Añadimos el directorio
            this->directorios.push_back(dirAux);
        }
        else
        {
            //Algo ha fallado en los datos del fichero.
            iterador = lineas.end();
            this->rutaRaiz = "//";
            this->fechaModificacion = -1;
            this->directorios.clear();
            res = false;
        }
    }

    return res;
}
/** desSerializarDesdeStringAuxiliarIterador()      10.05.2025   -   hecha
 * Función auxiliar de desSerializarDesdeString() para
 * avanzar el iterador y leer correctamente el vector
 * que se esta desserializando.
 *
 * ARG1: vector<string>::iterator &, iterador del vector
 *                      con los datos a desserializar
 * ARG2: string &, contenido del string al que apunta el iterador.
 * ARG3: string &, referencia para saber qué dato contiene ARG2.
 * ARG4: string &, dato extraido de ARG2.
 * ARG5: vector<string> &, vector original sobre el que iteramos.
 */
void InfoArchivo::desSerializarDesdeStringAuxiliarIterador(
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











