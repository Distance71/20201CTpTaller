# tp1taller

##########################################################################################################
#instrucciones para levantar el ambiente
##########################################################################################################

*install sdl: sudo apt-get install libsdl2-dev
*install sdl-image: sudo apt install libsdl2-image-dev
*install cmake 3.17: sudo snap install cmake --classic # version 3.17.1
*install Libreria Json: sudo apt install nlohmann-json-dev
*install sdl_ttf: sudo apt-get install libsdl2-ttf-dev

*verificar carpeta build vacia
*hacer 'cmake ..' en build
*hacer 'make' en build

*ejecutar (para el modo server):
./tp1taller -c../ConfigurationServer.json --p 6000 -m SERVER

ó ejecutar (para el modo cliente): 
./tp1taller -c../ConfigurationClient.json --p 6000 -i 127.0.0.1 -m CLIENT

ó ejecutar (para el modo cliente y TEST): 
./tp1taller -c../ConfigurationClient.json --p 6000 -i 127.0.0.1 -m CLIENT-TEST

##########################################################################################################
problemas conocidos:

**ubuntu 19.10 problemas para instalar Libreria Json. camino alternativo:
de https://ubuntu.pkgs.org/19.10/ubuntu-universe-i386/nlohmann-json3-dev_3.7.0-2_all.deb.html
hacer wget de http://archive.ubuntu.com/ubuntu/pool/universe/n/nlohmann-json3/nlohmann-json3-dev_3.7.0-2_all.deb
y por ultimo sudo apt install ./nlohmann-json3-dev_3.7.0-2_all.deb


**No existe el archivo o el directorio
    7 | #include <boost/algorithm/string.hpp>
solucion-->
sudo apt-get install libboost-dev

##########################################################################################################