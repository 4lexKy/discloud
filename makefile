
/*
 * Copyright 2026 Alex (alex.correu@pm.me)
 * SPDX-License-Identifier: GPL-2.0-only
 * Este programa es software libre: puedes redistribuirlo y/o modificarlo bajo los términos
 * de la Licencia Pública General GNU como publicada por la Free Software Foundation,
 * ya sea la versión 2 de la Licencia, o (a tu elección) cualquier versión posterior.
 */

	#Variables
#Opciones de compilacion
options = -Wall -g -O2
version = -std=c++17
libLink = -lstdc++fs -pthread
miCompilacion = $(options) $(version) $(libLink)
#Lista de mis librerías
lib01 = ./ejecutables/directorios.o
lib02 = ./ejecutables/accesoArchivos.o
lib03 = ./ejecutables/comunicacionCliente.o
lib04 = ./ejecutables/comunicacionServidor.o
lib05 = ./ejecutables/envioArchivos.o
lib06 = ./ejecutables/envrec.o
lib07 = ./ejecutables/vigilaFicheros.o
lib08 = ./ejecutables/discloudLib.o
lib09 = ./ejecutables/listadoFicheros.o
lib10 = ./ejecutables/nodo.o
lib11 = ./ejecutables/cliente.o
lib12 = ./ejecutables/hilos.o
lib13 = ./ejecutables/modificaciones.o
numLib = 13
miLibreria = $(lib01) $(lib02) $(lib03) $(lib04) $(lib05) $(lib06) $(lib07) $(lib08) $(lib09) $(lib10) $(lib11) $(lib12) $(lib13)

make: clear
	#################################################################
	#								#
	#	Para compilar DISCLOUD:					#
	#	"make all"		-> Compila Servidor i Client	#
	#	"make allinc"		-> Compila incl, serv i cli	#
	#	"make discloud"		-> Compila sols el Servidor	#
	#	"make clienteDiscloud"	-> Compila soles el Client	#
	#	"make includes"		-> Compila soles llibreries	#
	#	"make pr"		-> Compila ficher de proves	#
	#	"make princ"		-> Compila includes y prova	#
	#	"make prexe"		-> Compila i executa prova1	#
	#	"make princexe"		-> Compila exec prova i lib	#
	#	"make prclang"		-> Compila proves amb clang	#
	#	"make pr2"		-> Compila fichers de prova	#
	#	"make pr2only"		-> Compila ficher de prova2	#
	#	"make pr2onlyexe"	-> Compila i executa prova2	#
	#	"make debugpr2"		-> Executa  valgrind prova2	#
	#								#
	#################################################################

all: discloud clienteDiscloud
	@echo "\nCompilat amb Èxit\n"

allinc: includes discloud clienteDiscloud
	@echo "\nCompilat amb Èxit\n"

discloud: clear clean discloud.cpp
	g++ ./discloud.cpp $(miLibreria) -o discloud.o $(miCompilacion)
	@echo "\nCompilat el servidor Discloud amb Èxit\n"

clienteDiscloud: clean clienteDiscloud.cpp
	g++ ./clienteDiscloud.cpp $(miLibreria) -o clienteDiscloud.o $(miCompilacion)
	@echo "\nCompilat el client Discloud amb Èxit\n"

includes: clear includes.hpp ./utilidades/accesoArchivos.cpp ./utilidades/comunicacionCliente.cpp ./utilidades/comunicacionServidor.cpp ./utilidades/directorios.cpp ./utilidades/envioArchivos.cpp ./utilidades/envrec.cpp ./utilidades/vigilaFicheros.cpp ./estructuras/listadoFicheros.cpp ./estructuras/nodo.cpp ./estructuras/cliente.cpp
	rm -rf ./ejecutables/*.o
	@echo "Borrats '-o' antics.\n"
	@#LIBRERÍAS DE DISCLOUD
	g++ -c ./discloudLib/discloudLib.cpp -o ./ejecutables/discloudLib.o $(miCompilacion)
	@echo "    Llibreríes compilades =>1/$(numLib)"
	@#LIBRERÍAS DE UTILIDADES
	g++ -c ./utilidades/accesoArchivos.cpp -o ./ejecutables/accesoArchivos.o $(miCompilacion)
	@echo "    Llibreríes compilades =>2/$(numLib)"
	g++ -c ./utilidades/comunicacionCliente.cpp -o ./ejecutables/comunicacionCliente.o $(miCompilacion)
	@echo "    Llibreríes compilades =>3/$(numLib)"
	g++ -c ./utilidades/comunicacionServidor.cpp -o ./ejecutables/comunicacionServidor.o $(miCompilacion)
	@echo "    Llibreríes compilades =>4/$(numLib)"
	g++ -c ./utilidades/directorios.cpp -o ./ejecutables/directorios.o $(miCompilacion)
	@echo "    Llibreríes compilades =>5/$(numLib)"
	g++ -c ./utilidades/envioArchivos.cpp -o ./ejecutables/envioArchivos.o $(miCompilacion)
	@echo "    Llibreríes compilades =>6/$(numLib)"
	g++ -c ./utilidades/envrec.cpp -o ./ejecutables/envrec.o $(miCompilacion)
	@echo "    Llibreríes compilades =>7/$(numLib)"
	g++ -c ./utilidades/vigilaFicheros.cpp -o ./ejecutables/vigilaFicheros.o $(miCompilacion)
	@echo "    Llibreríes compilades =>8/$(numLib)"
	g++ -c ./estructuras/listadoFicheros.cpp -o ./ejecutables/listadoFicheros.o $(miCompilacion)
	@echo "    Llibreríes compilades =>9/$(numLib)"
	g++ -c ./estructuras/nodo.cpp -o ./ejecutables/nodo.o $(miCompilacion)
	@echo "    Llibreríes compilades =>10/$(numLib)"
	g++ -c ./estructuras/cliente.cpp -o ./ejecutables/cliente.o $(miCompilacion)
	@echo "    Llibreríes compilades =>11/$(numLib)"
	g++ -c ./utilidades/hilos.cpp -o ./ejecutables/hilos.o $(miCompilacion)
	@echo "    Llibreríes compilades =>12/$(numLib)"
	g++ -c ./estructuras/modificaciones.cpp -o ./ejecutables/modificaciones.o $(miCompilacion)
	@echo "    Llibreríes compilades =>13/$(numLib)"
	@echo "Totes les dependències están controlades\n"



pr: clear clean zpruebas.cpp
	g++ ./zpruebas.cpp $(miLibreria) -o pr.o $(miCompilacion)
	@echo "Creat    ./pr.o    per a executar proves \n"
princ: includes pr
prexe: pr
	sleep 1
	./pr.o
princexe:  princ
	sleep 1
	./pr.o
prclang: zpruebas.cpp
	clang++-16 -x c++ -Wall -std=c++11 zpruebas.cpp -o pr.o
pr2: clear clean zpruebas.cpp zpruebas2.cpp
	g++ zpruebas.cpp -o pr.o $(miCompilacion)
	g++ zpruebas2.cpp -o pr2.o $(miCompilacion)
	@echo "Creat    ./pr.o y ./pr2.o    per a executar proves \n"
pr2only: clear clean zpruebas2.cpp
	g++ ./zpruebas2.cpp $(miLibreria) -o pr2.o $(miCompilacion)
	@echo "Creat    ./pr2.o    per a executar proves \n"
pr2onlyexe: pr2only
	@echo "Executant PR2 proves \n"
	./pr2.o

debugpr2: clear
	#https://stackoverflow.com/questions/5134891/how-do-i-use-valgrind-to-find-memory-leaks
	#sudo apt install valgrind
	valgrind --verbose ./pr2.o


clean:
	rm -rf *.o
	@echo "Borrats '-o' antics.\n"

clear:
	clear



	@#-o: nombre de archivo ejecutable
	@#-c option says not to run the linker, compilar archivo sin main()
	@#-O2: opción de optimización
	@#-g: "genera información adicional de depuración simbólica para usar con el gdb depurador"
	@#-Wall: muestra todos los avisos
	@#-std=c++17: usar la versión 17 del compilador de c++
	@#-lstdc++fs: hace que se enlace la librería de filesystem
