#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <string>
#include <fstream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../providers/GameProvider.h"

using namespace std;

//Debe generar un texture a partir de una imagen, puede ser una ruta
// o pasarle una imagen cargada de la ruta.
// Aca estaria bueno centralizar el manejo de la imagen por defecto

//Pueden hacer varias cosas, mirar estas funciones
//IMG_load -> Cargar imagen si no le pasan un SDL_Surface
//SDL_SetColorKey -> Transparentar color background sprite
//SDL_CreateTextureFromSurface -> Crear textura


class Sprite {

    SDL_Texture *texture_;
    string imageSource_;

    public:
    Sprite(const string &source);
    ~Sprite();
    string getImageSource();
    SDL_Texture* getTexture();
    int getTextureWidth();
    int getTextureHeight();
};

#endif