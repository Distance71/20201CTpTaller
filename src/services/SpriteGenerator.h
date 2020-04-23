#ifndef _SPRITEGENERATOR_H_
#define _SPRITEGENERATOR_H_

#include <string>
#include <fstream>
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


class SpriteGenerator {

    SDL_Texture *texture_;

    public:
    SpriteGenerator(const string &source);
    ~SpriteGenerator();
    SDL_Texture* getTexture();
};

#endif