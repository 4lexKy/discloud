[Versión 0.7.2]: #
# discloud - Nube distribuida privada de código abierto

Discloud ([discloud.es](https://discloud.es)) es una nube distribuida, autohosteada, independiente y de código abierto. Estas características la hacen única:
- Distribuida -> Los datos estan en distintos lugares, resiliente ante fallos
- Privada (autohosteada) -> Posees tus propios datos, tienes pleno control
- Independiente -> No necesita servicios de terceros para poder funcionar
- Código abierto -> Puedes revisar el código que ejecutarás

---
## Estado del proyecto
Estamos en los inicios del desarrollo del proyecto. Se ha dedicado mucho tiempo y esfuerzo para que todo funcione lo mejor posible. Actualmente se dispone de una muy buena base sobre la que seguir construyendo esta nube única

### Ficheros
- discloud.cpp: Fichero principal del proyecto (servidor)
- clienteDiscloud.cpp: Fichero principal del proyecto (cliente)
- namespaces.hpp: Fichero que incluye cabecesas comunes a ficheros
- includes.hpp: Fichero que contiene includes comunes a ficheros
- makefile: Fichero Make para compilar de diferentes modos.
- discloudLib/ : Directorio que contiene las librerías de Discloud
- estructuras/ : Directorio que contiene las estructuras de Discloud
- utilidades/ : Directorio que contiene librerías con utilidades para Discloud
- LICENSE: contenido de la licencia
- README.md: información del proyecto
- .gitignore: define elementos a ignorar

---
## Instalación
En el estado actual del proyecto no necesita instalación

### Lenguaje
- `C/C++`
- `Make`

### Dependencias
Sí, tiene dependencias de las siguientes librerías:

- fstream
- iostream
- string
- cstring
- cstdio
- vector
- experimental/filesystem
- chrono
- thread
- fcntl.h
- unistd.h
- sys/types.h
- sys/stat.h
- dirent.h
- ctime

### Sistemas operativos compatibles
Probado en:
- Debian

---
## Uso
[próximamente]

---
## Licencia
Este proyecto está licenciado bajo GPLv2 - consulta el archivo LICENSE para más detalles.

---
## Autor
>**Alex**
- Github: [https://github.com/4lexKy](https://github.com/4lexKy)
- Email: [alex.correu@pm.me](mailto:alex.correu@pm.me)

---
