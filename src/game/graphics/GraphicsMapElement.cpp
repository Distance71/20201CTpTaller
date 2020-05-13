#include "GraphicsMapElement.h"

GraphicsMapElement::GraphicsMapElement(Sprite * sprite){
    sprite_ = sprite;
}

void GraphicsMapElement::update(unordered_map<string, State *> states_){

    State* position_ = states_.at("Position");

    Logger::getInstance()->log(DEBUG, "Entro al update de graphics");

    SDL_Renderer* renderer = GameProvider::getRenderer();   
    
    //rectangulo que se usa para hace el recorte sobre la foto
    SDL_Rect sprite ={0,0,107,83}; 
    
    //rectangulo de la pantalla donde quiero dibujar el sprite.
    SDL_Rect aux_graphics_sprite = {position_ -> getX(), position_ -> getY(),107, 83};
    
    //Obtengo la textura
    SDL_Texture* spriteTexture = sprite_-> getTexture();
    
    //el renderer copia la textura del sprite recortando la foto con 
    //sprite y pegandola en el rectangulo de la pantalla
    //donde lo quiero ubicar, es decir en aux_graphics_sprite
    SDL_RenderCopy(renderer, spriteTexture, &sprite, &aux_graphics_sprite);
}
 