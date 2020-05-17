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
        Logger::getInstance()->log(ERROR, string("Error al abrir el archivo del sprite").append(source));
        TTF_Font *Sans = TTF_OpenFont("assets/Fonts/open-sans/OpenSans-Regular.ttf", 24);
        if (Sans == nullptr) {
            SDL_Surface *surfaceColor = SDL_CreateRGBSurface(0, 300, 300, 32, 0, 0, 0, 0);
            SDL_FillRect(surfaceColor, nullptr, SDL_MapRGB(surfaceColor->format, 47, 106, 144));
            texture_ = SDL_CreateTextureFromSurface(GameProvider::getRenderer(), surfaceColor); 
        } else {
            SDL_Color black = {0, 0, 0};
            SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Sans, "?", black);
            SDL_Surface *surfaceColor = SDL_CreateRGBSurface(0, 300, 300, 32, 0, 0, 0, 0);
            SDL_FillRect(surfaceColor, nullptr, SDL_MapRGB(surfaceColor->format, 47, 106, 144));
            SDL_BlitSurface(surfaceMessage, nullptr, surfaceColor, nullptr);
            texture_ = SDL_CreateTextureFromSurface(GameProvider::getRenderer(), surfaceColor);
        }
    }
}
SDL_Texture *Sprite::getTexture() {
    return this->texture_;
}

int Sprite::getTextureWidth(){
    int width;
    SDL_QueryTexture(texture_, nullptr, nullptr, &width,NULL);
    return width;
}

int Sprite::getTextureHeight(){
    int height;
    SDL_QueryTexture(texture_, nullptr, nullptr,NULL,&height);
    return height;
}

Sprite::~Sprite(){
    SDL_DestroyTexture(this->texture_);
    texture_ = NULL;
}