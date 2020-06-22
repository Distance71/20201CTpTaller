#include "ClientMap.h"

ClientMap::ClientMap(){}

ClientMap::~ClientMap(){}

void ClientMap::setStageSource(stageSource_t background){
    this->escenario_= new GraphicsScenario(background);
}

GraphicsScenario *ClientMap::getCurrentScenario(){
    return this->escenario_;
}

void ClientMap::addNewPlayer(){

}

void  ClientMap::addNewEnemy(unsigned int step, IdElement idEnemy, elementType_t type, position_t position, const string &sourceSprite, int size_x, int size_y){

    if (step >= this->steps_.size())
        return;

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