# TP1 - Taller de Programación I

--------------------------------------------------------------------------------------------------------
## Instrucciones para levantar el ambiente

#### Instalación de librerías requeridas
- install sdl: sudo apt-get install libsdl2-dev
- install sdl-image: sudo apt install libsdl2-image-dev
- install cmake 3.17: sudo snap install cmake --classic # version 3.17.1
- install Libreria Json: sudo apt install nlohmann-json-dev
- install sdl_ttf: sudo apt-get install libsdl2-ttf-dev
- install sdl_mixer: sudo apt-get install libsdl2-mixer-dev

#### Verificar carpeta build vacia
- hacer 'cmake ..' en build
- hacer 'make' en build


--------------------------------------------------------------------------------------------------------
## Formas de Ejecución

#### Modo Server:
./tp1taller -c../ConfigurationServer.json -p 6000 -m SERVER

#### Modo Cliente:
./tp1taller -c../ConfigurationClient.json -p 6000 -i 127.0.0.1 -m CLIENT

Tanto para el puerto (_-p_) como para la dirección IP a conectarse (_-i_) puede variar según los requerimientos propios.

Por otro lado, para el archivo de configuración correspondiente (_-c_) puede ingresar la ruta a su propio archivo de configuración.

--------------------------------------------------------------------------------------------------------

## Algunos problemas conocidos:

- ubuntu 19.10 problemas para instalar Libreria Json. Camino alternativo: 
    - de https://ubuntu.pkgs.org/19.10/ubuntu-universe-i386/nlohmann-json3-dev_3.7.0-2_all.deb.html
    - hacer wget de http://archive.ubuntu.com/ubuntu/pool/universe/n/nlohmann-json3/nlohmann-json3-dev_3.7.0-2_all.deb
    - y por ultimo sudo apt install ./nlohmann-json3-dev_3.7.0-2_all.deb


- No existe el archivo o el directorio: #include <boost/algorithm/string.hpp>
 solucion --> sudo apt-get install libboost-dev
