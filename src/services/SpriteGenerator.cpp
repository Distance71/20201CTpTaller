#include "SpriteGenerator.h"

SpriteGenerator::SpriteGenerator(const string &source){
    ifstream infile(source);
    if(infile.good()) {
        GameProvider::getLogger()->log(DEBUG, "Se va a crear el sprite: " + source);
        
        SDL_Surface *sprite = IMG_Load(source.c_str());
        texture_ = SDL_CreateTextureFromSurface(GameProvider::getRenderer(), sprite);
        SDL_FreeSurface(sprite);
    }

    //else aca pueden incluir codigo para el caso de no encontrar imagen
}

SDL_Texture *SpriteGenerator::getTexture() {
    return this->texture_;
}

SpriteGenerator::~SpriteGenerator(){
    SDL_DestroyTexture(this->texture_);
    texture_ = NULL;
}
