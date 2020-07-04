#include "GraphicsMapElement.h"

GraphicsMapElement::GraphicsMapElement(const string &source,  int size_x, int size_y, int pos_x, int pos_y, orientation_t orientation){
    this->sprite_ = new Sprite(source);
    this->size_x_ = size_x;
    this->size_y_ = size_y;
    this->pos_x_ = pos_x;
    this->pos_y_ = pos_y;
    this->orientation_ = orientation;
}

GraphicsMapElement::~GraphicsMapElement(){
    delete this->sprite_;
}

void GraphicsMapElement::update(){

    Logger::getInstance()->log(DEBUG, "Entro al update de graphics");

    SDL_Renderer* renderer = GameProvider::getRenderer();   
    
    //rectangulo que se usa para hace el recorte sobre la foto
    SDL_Rect sprite ={0, 0, this->size_x_, this->size_y_}; 
    
    //rectangulo de la pantalla donde quiero dibujar el sprite.
    SDL_Rect aux_graphics_sprite = {this->pos_x_, this->pos_y_, this->size_x_, this->size_y_};
    
    //Obtengo la textura
    SDL_Texture* spriteTexture = sprite_-> getTexture();
    
    //el renderer copia la textura del sprite recortando la foto con 
    //sprite y pegandola en el rectangulo de la pantalla
    //donde lo quiero ubicar, es decir en aux_graphics_sprite
    //SDL_RenderCopy(renderer, spriteTexture, &sprite, &aux_graphics_sprite);
    
    if (this->orientation_ == FRONT){
        SDL_RenderCopy(renderer, spriteTexture, &sprite, &aux_graphics_sprite);
    } else if (this->orientation_ == BACK){
        SDL_RenderCopyEx(renderer, spriteTexture, &sprite, &aux_graphics_sprite, 180, nullptr, SDL_FLIP_VERTICAL);
    }
}
 
void GraphicsMapElement::setNewPosition(int pos_x, int pos_y, orientation_t orientation){
    this->pos_x_ = pos_x;
    this->pos_y_ = pos_y;
    this->orientation_ = orientation;
};

