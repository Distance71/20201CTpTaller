#include "MapElementBackground.h"

MapElementBackground::MapElementBackground(layer_t layer, stage_t stage, Speed* speed, Position* position){
    this->position_ = new Position(position->getX(), position->getY());
    this->speed_ = new Speed(speed->getX(), speed->getY());
    this->layer_ = layer;
    this->stage_ = stage;
}

void MapElementBackground::update(){
    size_t screenWidht = GameProvider::getWidth();
    size_t screenHeight = GameProvider::getHeight();

    Logger::getInstance()->log(DEBUG, "Entro al update de background");

    int xp = this->position_->getX();
    int xs = this->speed_->getX();
    
    int new_xp;

    new_xp = xp + xs;

    if (new_xp >= screenWidht)
        this->position_->setX(0);
    else
        this->position_->setX(new_xp);
}

int MapElementBackground::getStep(){
    return this->position_->getX();
}

stage_t MapElementBackground::getStage(){
    return this->stage_;
}

layer_t MapElementBackground::getLayer(){
    return this->layer_;
}