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
}

GraphicsMapElement::~GraphicsMapElement(){
    delete this->sprite_;
}

void GraphicsMapElement::set(){
    this->setted_ = true;
}

bool GraphicsMapElement::isSet(){
    return this->setted_;
}

void GraphicsMapElement::update(position_t position){
    SDL_Rect auxGraphicsSprite = {position.axis_x, position.axis_y, this->size_x_, this->size_y_};

    SDL_Renderer *renderer = GameProvider::getRenderer();
    
    if(position.orientation == FRONT)
        SDL_RenderCopy(renderer, this->sprite_->getTexture(), NULL, &auxGraphicsSprite);
    else if(position.orientation == BACK)
        SDL_RenderCopyEx(renderer, this->sprite_->getTexture(), NULL, &auxGraphicsSprite, 180, nullptr, SDL_FLIP_VERTICAL);
}