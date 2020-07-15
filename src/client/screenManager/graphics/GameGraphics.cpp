#include "GameGraphics.h"
#include <stdio.h>

GameGraphics::GameGraphics(SDL_Renderer* renderer){
    this->scenario_ = nullptr;
    this->image_ = nullptr;
    this->renderer_ = renderer;
}


GameGraphics::~GameGraphics(){
    if (this->scenario_)
        delete this->scenario_;
    if(this->image_)
        delete this->image_;
    for(auto element:this->elements_)
        delete element.second;

    Logger::getInstance()->log(INFO, "Se liberan los recursos utilizados para los gŕaficos del juego");
}


void GameGraphics::update(){

    SDL_RenderClear(this->renderer_);

    if (this->scenario_)
        scenario_->update();

    if (this->image_){
        image_->update();
    }

    for(auto element : this->elements_){
        element.second->update();
    }
        

    SDL_RenderPresent(this->renderer_);

}


void GameGraphics::createEntity(Id id, const string &source, int sizeX, int sizeY, int posX, int posY, orientation_t orientation){
    GraphicsMapElement *newElement = new GraphicsMapElement(source, sizeX, sizeY, posX, posY, orientation);
    auto it = this->elements_.find(id);
        if (it != this->elements_.end())
            delete it->second;
        this->elements_.emplace(id, newElement); 
}


void GameGraphics::updateEntity(Id id, int posX, int posY, orientation_t orientation){
    auto it = this->elements_.find(id);
    if (it != this->elements_.end())
        it->second->setNewPosition(posX, posY, orientation);
}


void GameGraphics::deadEntity(Id id){
    
    /*GraphicsMapElement *oneElement = this->elements_.at(id);
    if (!oneElement){
        Logger::getInstance()->log(ERROR, "No se pudo eliminar el elemento debido a que el id es inexistente");
    }
    else {
        this->elements_.erase(id);
        delete oneElement;
    }*/
}


void GameGraphics::setBackground(stageSource_t background){

    if (this->scenario_){
        delete this->scenario_;
        this->scenario_=nullptr;
    }

    if (this->image_){
        delete this->image_;
        this->image_=nullptr;
    }
    std::mutex mtx;
    
    mtx.lock();
    this->scenario_ = new GraphicsScenario(background);
    mtx.unlock();

    Logger::getInstance()->log(DEBUG, "Se actualiza el background");

}


void GameGraphics::setImage(const string &source){
    /*if (this->scenario_){
        delete this->scenario_;
        this->scenario_= nullptr;

    }*/
    std::unique_lock<std::mutex> lock(mutex);
    this->image_ = new GraphicsMapElement(source, GameProvider::getWidth(),GameProvider::getHeight(),0,0,FRONT);
}