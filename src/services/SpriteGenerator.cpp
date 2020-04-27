#include "SpriteGenerator.h"

#include <iostream>
using namespace std;

SpriteGenerator::SpriteGenerator(const string &source){
    ifstream infile(source);
    if(infile.good()) {
        Logger::getInstance()->log(DEBUG, "Se va a crear el sprite: " + source);
        SDL_Surface *sprite = IMG_Load(source.c_str());
        texture_ = SDL_CreateTextureFromSurface(GameProvider::getRenderer(), sprite);
        SDL_FreeSurface(sprite);
    }

    else cout << source << endl;
}
SDL_Texture *SpriteGenerator::getTexture() {
    return this->texture_;
}

SpriteGenerator::~SpriteGenerator(){
    SDL_DestroyTexture(this->texture_);
    texture_ = NULL;
}
