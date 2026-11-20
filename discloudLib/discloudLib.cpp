
/*
 * Copyright 2026 Alex (alex.correu@pm.me)
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

#include "../includes.hpp"
#include "../namespaces.hpp"

#include "../utilidades/directorios.hpp"
#include "../utilidades/comunicacionServidor.hpp"
#include "../utilidades/comunicacionCliente.hpp"
#include "../utilidades/envioArchivos.hpp"
#include "../utilidades/vigilaFicheros.hpp"
#include "../utilidades/accesoArchivos.hpp"
#include "../estructuras/modificaciones.hpp"


#include "./discloudLib.hpp"
;   //El compilador detecta algo antes, necesita poner el punto y coma
//Pre-Declaración funciones
int almacenamientoLocal(string);


/**     almacenamientoLocal()           15.04.25 - hecho
 *
 * Cuando Discloud se inicia comprueba la carpeta
 * donde tiene almacenados los archivos de la nube.
 * Concretamente que exista y que estén sincronizados
 * con la BD.
 *
 * Uso:
 *      almacenamientoLocal("./pruebaBorrar")
 *      almacenamientoLocal()                   //Para crear la ruta predeterminada
 *
 * Return:
 * 0 Todo ha salido bien, éxito de sincronización
 * 1 Error desconocido
 * 2 Carpeta creada, no existía
 * 3 datos de archivos recogidos correctamente, no comparado con la BD
 * 4 fallo, dessincronización entre archivos con BD
 * 5 fallo, no conexión con BD
 * 6 error desconocido en la BD
 * 7 fallo en en inventario de los archivos
 * 8 Error desconocido al crear carpeta
 *
 *
 * debe hacer lo siguiente:
 *  - Predeterminado, return 1, error desconocido.
 *  - Comprobar si existe la carpeta
 *      - Si no existe la crea (devuelve 2)
 *      - Si existe cuenta cuantos archivos hay y los lista
 *          - Si concuerda todo ha ido bien. return 0
 *          - Si no concuerda, reurn 3
 *  - **Comprueba que los archivos coincidan con la BD.
 *  - Guarda los archivos en un struct.
 */
int almacenamientoLocal(string ruta = " sinruta")
{
    int res = 1; // por defecto manda un error desconocido.

    //Comprobar si existe la carpeta
        //Crearla
            //return 2
        //Existe
            //Numero de archivos
            //Datos
            //*Comparar con BD
                //todo bien return 0
                //discrepancia con la BD return 3

    /**
     * Return
     * 0 Todo ha salido bien, éxito de sincronización
     * 1 Error desconocido
     * 2 Carpeta creada, no existía
     * 3 datos de archivos recogidos correctamente
     * 4 fallo, dessincronización entre archivos con BD
     * 5 fallo, no conexión con BD
     * 6 error desconocido en la BD
     * 7 fallo en en inventario de los archivos
     * 8 Error desconocido al crear carpeta
     */

    //Obtenemos ruta a crear/acceder
    if (ruta == " sinruta")
        ruta =  "./datosNube";
    else
        cout << "\nRuta introducida" << endl;

//     ruta == " sinruta"
//         ? ruta = "./datosNube"
//         : cout << "\nRuta introducida" << endl;

    //Creamos/accedemos al directorio
    switch (crearDirectorio(ruta))//carpeta NO existe)
    {
        case 0:     //La carpeta NO ha sido creada, ya existía.
            //Hacemos inventario de archivos
            if(/*rellenarListaArchivos()*/  0 == 0)
            {
                //Inventario realizado correctamente
                res = 3;

                //Se comprueba los archivos con la BD
                switch (/*compararArchivosConBD()*/ 0)
                {
                    case 0:
                        //Concronización con la BD correcta
                        res = 0;
                        break;
                    case 1:
                        //Archivos dessincronizados
                        res = 4;
                        break;
                    case 2:
                        //Fallo de conexión con la BD
                        res = 5;
                        break;
                    default:
                        //error desconocido
                        res = 6;
                        break;
                }
            } else {
                cout << "Error al crear la lista de archivo existentes" << endl;
                res = 7;
            }
            break;
        case 1:     //La carpeta(y su ruta) ha sido creada
            //Rellenamos lista de archivos SIN elementos
            //////rellenarListaArchivos(1);
            //Return de caso carpeta creada
            res = 2;
            break;
        default:
            //Caso desconocido
            res = 8;
            break;

        /*
        fs::create_directory(nombre)
            ? cout << "Almacenamiento creado correctamente" << endl
            : cout << "Fallo al crear almacenamiento" << endl;
        */
    }

    return res;
}













/** escuchandoAClientes()   ### falta pulir       10.05.2025   -   hecha
 * Función que escucha los cambios de archivos del cliente,
 * posteriormente recibe el archivo y lo guarda en la ruta
 * correcta.
 *
 * ARG1: InfoArchivo &, información de los archivos locales.
 */
void escuchandoAClientes(InfoArchivo & ia)
{
//     int clienteSocket = crearSocket(20);
    string palabra = "asadsaasd";
    int socketCliente = crearSocket(20);
    bool bucle = true;
    int numConexion = 0;
    string rutaGuardado = "./CarpetaServidor/CarpetaOrigen/archivoSenyuelo2.txt";


    while (bucle)
    {
        cout << "[SRV]-> Escuchando a clientes...(conexión: " << numConexion << ")" << endl;
        palabra = "//";

        //Esperamos conexión del cliente
        escuchaAlSocketCliente(palabra,socketCliente);
        cout << "[SRV]-> Palabra recibida..." << palabra << endl;

        //Generamos ruta de guardado
        rutaGuardado = ia.leerRutaRaiz() + palabra.erase(0, 1);

        //Recibimos y guardamos el archivo
        cout << "[SRV]-> Recibiendo archivo..." << rutaGuardado << endl;
//        recibirArchivoSV(rutaGuardado);
        recibirArchivoSVSocketPropio(rutaGuardado,socketCliente);

        numConexion++;
    }

    cerrarSocket(socketCliente);
    return;
}

/** bucleDeDeteccionYenvioDeficheros()  ### falta pulir       10.05.2025   -   hecha
 * Función que está atenta al cambio de ficheros
 * y en el caso de modificación informa al servidor
 * y lo envía.
 */
void bucleDeDeteccionYenvioDeficheros(InfoArchivo & ia)
{
    //Declaraciones
    string palabra = "//";
    vector<DirectorioModificado> directoriosModificados;    //vector<string> directoriosModificados;
    vector<FicheroModificado> ficherosModificados;          //vector<string> ficherosModificados;
    Modificaciones mods;

    //Operaciones
    while(true)
    {
        //Controlar cambios en ficheros
        monitorizarFicheros(ia,
                    directoriosModificados,
                    ficherosModificados,
                    false,  //No queremos que compruebe con la BD
                    2);     //Comprobar cada 2 segundos

        ///###
        if(ficherosModificados.size() != 0)
        {
            //Genero el objeto Modificaciones
            mods = Modificaciones(ficherosModificados,directoriosModificados);

            //Enviar informacion de modificaciones a servidor
            string serializado = "CMS\n"+mods.serializarEnString();
                                //^La cabecera CMS indica que es la modificación de un fichero
                                /**Siempre iniciamos con "CMS" porque el
                                * único caso en el que se envía este
                                * archivo serializado es cuando el cliente
                                * tiene una modificación y desea serializarla
                                * para enviarla, es decir, el caso "CMS"
                                */
            cout << "Serializado salido del horno:" << serializado << endl;
            informarAlServidor(serializado);

            //Enviar archivos modificados    (¿ ### esperar confirmacion para enviar?)
            vector<FicheroModificado> vfm = mods.leerListaFicheros();
            for(FicheroModificado fm : vfm)
            {
                sleep_for(seconds(1));
                enviarArchivoCL(fm.ruta);
            }
            //Los directorios no hay que enviarlos.

            cout << "Enviado tam: " << vfm.size() << endl;

            //Reseteamos variables
            ficherosModificados.clear();
            palabra = "//";
        }
    }

    return;
}




/** existeIAguardado()  11.05.2025   -   hecha
 * Función que comprueba si el fichero pasado como
 * parámetro contiene un objeto InfoArchivo serializado.
 *
 * Las condiciones que se han usado para comprobarlo son:
 *      - Que el archivo exista.
 *      - Que el archivo pueda abrirse.
 *      - Que el archivo se desserialize en un InfoArchivo
 *          y que este objeto no esté vacío (rutaRaiz == "//")
 *
 * ARG1: string, ruta al fichero que comprobar.
 * RTRN: bool, true  -> Si el fichero contiene un objeto InfoArchivo.
 *             false -> Si el archivo no contiene un objeto InfoArchivo.
 */
bool existeIAguardado(string rutaIAGuardada)
{
    bool hayUnIA = false;       //Infica que hay un InfoArchivo almacenado.
    bool existe = false;        //Indica si el fichero existe
    bool seAbre = false;        //Indica si el fichero puede abrirse.
    bool contIA = false;        //Indica si el fichero contiene un objeto InfoArchivo.
    InfoArchivo iaPrueba;
    int descriptor = -1;
    string aux;

        //Si:
    //El archivo existe
    existe = existeFichero(rutaIAGuardada);
    if (existe)
    {
        cout << "existe fichero" << endl;
        //se puede abrir
        descriptor = abrirCrearArchivo(rutaIAGuardada);
        if(descriptor!=-1)
        {
            cout << "Se abre" << endl;
            //se puede abrir
            cerrarArchivo(descriptor);
            seAbre = true;

            //Leo el objeto guardado
            iaPrueba.desSerializarDesdeRuta(rutaIAGuardada);
            //Contiene un objeto InfoArchivo
//             if (iaPrueba.leerRutaRaiz() != "//" && iaPrueba.leerRutaRaiz() != "")
            aux = iaPrueba.leerRutaRaiz();
            if (aux[0] == '.' && aux[1] == '/')
            {
                cout << "tiene ia" << endl;
                contIA = true;
            }
        }
    }


    if (existe && seAbre && contIA)
        hayUnIA = true;
    else
        hayUnIA = false;

    return hayUnIA;
}
