#include "GraphicsGeneral.h"

GraphicsGeneral::GraphicsGeneral(){}

GraphicsGeneral::~GraphicsGeneral(){
    
    if (this->scenario_)
        delete this->scenario_;
}

void GraphicsGeneral::update(){

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

    this->scenario_ = new GraphicsScenario(background);
};

