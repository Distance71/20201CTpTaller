#include "Sprite.h"

Sprite::Sprite(const string &source){
    ifstream infile(source);
    if(infile.good()) {
        Logger::getInstance()->log(DEBUG, "Se va a crear el sprite: " + source);
        SDL_Surface *sprite = IMG_Load(source.c_str());
        if (!sprite) {
            Logger::getInstance()->log(ERROR, string("Error al cargar sprite ").append(source).append(string("IMG_Error: ")).append(IMG_GetError()));
            GameProvider::setErrorStatus(IMG_GetError());
            return;
        }
        texture_ = SDL_CreateTextureFromSurface(GameProvider::getRenderer(), sprite);
        SDL_FreeSurface(sprite);
    }
    else {
        Logger::getInstance()->log(ERROR, string("Error al abrir el archivo del sprite"));
        GameProvider::setErrorStatus(string("Error al abrir el archivo del sprite"));
    }
}
SDL_Texture *Sprite::getTexture() {
    return this->texture_;
}

Sprite::~Sprite(){
    SDL_DestroyTexture(this->texture_);
    texture_ = NULL;
}