#include "GraphicsMapElement.h"

GraphicsMapElement::GraphicsMapElement(const GraphicsMapElement &cpy){
    this->sprite_ = cpy.sprite_;
    this->size_x_ = cpy.size_x_;
    this->size_y_ = cpy.size_y_;
    this->pos_x_ = cpy.pos_x_;
    this->pos_y_ = cpy.pos_y_;
    this->orientation_ = cpy.orientation_;
}

GraphicsMapElement::GraphicsMapElement(const string &source,  int size_x, int size_y, int pos_x, int pos_y, orientation_t orientation){
    this->sprite_ = new Sprite(source);
    this->size_x_ = size_x;
    this->size_y_ = size_y;
    this->pos_x_ = pos_x;
    this->pos_y_ = pos_y;
    this->orientation_ = orientation;

    cout << "la source " << source << endl;
    cout << "el size x " << size_x << endl;
    cout << "el size y " << size_y << endl;
    cout << "el pos x " << pos_x << endl;
    cout << "el pos y " << pos_y << endl;
    cout << "la orientation " << orientation << endl;
}

GraphicsMapElement::~GraphicsMapElement(){
    delete this->sprite_;
}

void GraphicsMapElement::update(){
    SDL_Renderer* renderer = GameProvider::getRenderer();   
    
    //rectangulo de la pantalla donde quiero dibujar el sprite.
    SDL_Rect aux_graphics_sprite = {this->pos_x_, this->pos_y_, this->size_x_, this->size_y_};

    //Obtengo la textura
    SDL_Texture* spriteTexture = sprite_-> getTexture();
    
    //el renderer copia la textura del sprite recortando la foto con 
    //sprite y pegandola en el rectangulo de la pantalla
    //donde lo quiero ubicar, es decir en aux_graphics_sprite
    //SDL_RenderCopy(renderer, spriteTexture, &sprite, &aux_graphics_sprite);
    
    if (this->orientation_ == FRONT){
        SDL_RenderCopy(renderer, spriteTexture, NULL, &aux_graphics_sprite);
    } else if (this->orientation_ == BACK){
        SDL_RenderCopyEx(renderer, spriteTexture, NULL, &aux_graphics_sprite, 180, nullptr, SDL_FLIP_VERTICAL);
    }
}
 
void GraphicsMapElement::setNewPosition(int pos_x, int pos_y, orientation_t orientation){
    std::unique_lock<std::mutex> lock(this->mutex_setNewPos);
    this->pos_x_ = pos_x;
    this->pos_y_ = pos_y;
    this->orientation_ = orientation;
};

