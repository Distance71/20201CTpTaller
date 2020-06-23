#include "ClientMap.h"

ClientMap::ClientMap(){
    this->clearBackground();
}

ClientMap::~ClientMap(){}

void ClientMap::addLayerBackground(size_t idLayer, string oneSource){

    switch (idLayer){
        case 1:
            this->background_.layer1 = oneSource;
            break;
        case 2:
            this->background_.layer2 = oneSource;
            break;
        case 3:
            this->background_.layer3 = oneSource;
            break;
        case 4:
            this->background_.layer4 = oneSource;
            break;
        case 5:
            this->background_.layer5 = oneSource;
            break;
        case 6:
            this->background_.layer6 = oneSource;
            break;
        case 7:
            this->background_.layer7 = oneSource;
            break;
        default:
            break;
    }
}

void ClientMap::setStageSource(){
    this->escenario_= new GraphicsScenario(this->background_);
}

GraphicsScenario *ClientMap::getCurrentScenario(){
    return this->escenario_;
}

void ClientMap::addNewPlayer(){

}

void ClientMap::addNewEnemy(unsigned int step, IdElement idEnemy, elementType_t type, position_t position, const string &sourceSprite, int size_x, int size_y){


    if (step > this->steps_.size())
        return;

    if (step == this->steps_.size()){
        ClientStep *newStep = new ClientStep();
        this->steps_.push_back(newStep);
    }

    this->steps_.at(step)->addNewEnemy(idEnemy, type, position, sourceSprite, size_x, size_y);
}

void ClientMap::deadEnemy(unsigned int step, IdElement idEnemy){

    if (step >= this->steps_.size())
        return;

    this->steps_.at(step)->deadEnemy(idEnemy);    
}

void ClientMap::endLevel(){

    if (this->escenario_ != nullptr){
        delete this->escenario_;
    }

    this->clearBackground();
}

void ClientMap::clearBackground(){

    this->background_.layer1 = "";
    this->background_.layer2 = "";
    this->background_.layer3 = "";
    this->background_.layer4 = "";
    this->background_.layer5 = "";
    this->background_.layer6 = "";
    this->background_.layer7 = "";
}

ClientStep::ClientStep(){

}

ClientStep::~ClientStep(){
    
}

void ClientStep::addNewEnemy(IdElement idEnemy, elementType_t type, position_t position, const string &sourceSprite, int size_x, int size_y){
    ClientMapElement *newEnemy = new ClientMapElement(type, position, sourceSprite, size_x, size_y);
    this->mapElements_[idEnemy] = newEnemy;
}

void ClientStep::deadEnemy(IdElement idEnemy){

    ClientMapElement *deadMapElement = this->mapElements_.at(idEnemy);
    this->mapElements_.erase(idEnemy);
    delete deadMapElement;    
}

void ClientStep::endStep(){

    for (auto oneEnemy : this->mapElements_){
        delete oneEnemy.second;
    }
}