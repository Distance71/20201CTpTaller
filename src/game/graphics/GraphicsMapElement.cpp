#include "GraphicsMapElement.h"

GraphicsMapElement::GraphicsMapElement(Sprite * sprite,  int size_x, int size_y){
    this->sprite_ = sprite;
    this->size_x_ = size_x;
    this->size_y_ = size_y;
}

void GraphicsMapElement::update(unordered_map<string, State *> states_){

    State* position_ = states_.at("Position");
    State* orientation_ = states_.at("Orientation");

    Logger::getInstance()->log(DEBUG, "Entro al update de graphics");

    SDL_Renderer* renderer = GameProvider::getRenderer();   
    
    //rectangulo que se usa para hace el recorte sobre la foto
    SDL_Rect sprite ={0, 0, this->size_x_, this->size_y_}; 
    
    //rectangulo de la pantalla donde quiero dibujar el sprite.
    SDL_Rect aux_graphics_sprite = {position_ -> getX(), position_ -> getY(), this->size_x_, this->size_y_};
    
    //Obtengo la textura
    SDL_Texture* spriteTexture = sprite_-> getTexture();
    
    //el renderer copia la textura del sprite recortando la foto con 
    //sprite y pegandola en el rectangulo de la pantalla
    //donde lo quiero ubicar, es decir en aux_graphics_sprite
    //SDL_RenderCopy(renderer, spriteTexture, &sprite, &aux_graphics_sprite);
    int orientationSprite = orientation_->getX();
    if (orientationSprite == FRONT){
        SDL_RenderCopy(renderer, spriteTexture, &sprite, &aux_graphics_sprite);
    } else if (orientationSprite == BACK){
        SDL_RenderCopyEx(renderer, spriteTexture, &sprite, &aux_graphics_sprite, 180, nullptr, SDL_FLIP_VERTICAL);
    }
}
 