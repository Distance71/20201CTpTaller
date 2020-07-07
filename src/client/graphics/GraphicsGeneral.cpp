#include "GraphicsGeneral.h"
#include <stdio.h>
GraphicsGeneral::GraphicsGeneral(Client* _client){
    client = _client;
    image = NULL;
}

Client* GraphicsGeneral::getClient(){
    return client;
}

GraphicsGeneral::~GraphicsGeneral(){
    
    if (this->scenario_)
        delete this->scenario_;
}

void GraphicsGeneral::update(){
    if (scenario_){
        scenario_->update();
    }
     if (image){
        image->update();
    }
    for(auto oneElement : this->elements_)
        oneElement.second->update();
};

void GraphicsGeneral::createEntity(IdElement id, const string &source, int sizeX, int sizeY, int posX, int posY, orientation_t orientation){
    GraphicsMapElement *newElement = new GraphicsMapElement(source, sizeX, sizeY, posX, posY, orientation);

    this->elements_[id] = newElement;    
};

void GraphicsGeneral::updateEntity(IdElement id, int posX, int posY, orientation_t orientation){

    GraphicsMapElement *oneElement = this->elements_.at(id);

    if (oneElement){
        oneElement->setNewPosition(posX, posY, orientation);
    }
};

void GraphicsGeneral::deadEntity(IdElement id){

    GraphicsMapElement *oneElement = this->elements_.at(id);

    if (oneElement){
        this->elements_.erase(id);
        delete oneElement;
    }
};

void GraphicsGeneral::setBackground(stageSource_t background){

    if (this->scenario_)
        delete this->scenario_;

    if (this->image)
        delete this->image;

    this->scenario_ = new GraphicsScenario(background);
};
 

void GraphicsGeneral::run(){
    SDL_Renderer* gRenderer = GameProvider::getRenderer();
    while (client->isConnected()){
        SDL_RenderClear(gRenderer);
        update();
        SDL_RenderPresent(gRenderer);
    }
}

void GraphicsGeneral::setImage(const string &source){
    int sizeX, sizeY, posX, posY;
    orientation_t orientation = FRONT;

    sizeX = GameProvider::getWidth();
    sizeY = GameProvider::getHeight();
    posX = 0;
    posY = 0;

    this->image = new GraphicsMapElement(source, sizeX, sizeY, posX, posY, orientation);

};
