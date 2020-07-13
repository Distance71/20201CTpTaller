#include "GameGraphics.h"

GameGraphics::GameGraphics(SDL_Renderer* renderer){
    this->scenario_ = nullptr;
    this->image_ = nullptr;
    this->renderer_ = renderer;
    this->elements_ = new BlockingMapGraphicsMapElement();
}


GameGraphics::~GameGraphics(){
    if (this->scenario_)
        delete this->scenario_;
    
    if(this->image_)
        delete this->image_;
    
    vector<Id> keys = this->elements_->getAllKeys();
    
    for(auto key : keys)
        this->elements_->deleteElement(key);
    
    Logger::getInstance()->log(INFO, "Se liberan los recursos utilizados para los gŕaficos del juego");

}


void GameGraphics::update(){

    SDL_RenderClear(this->renderer_);

    if (this->scenario_)
        scenario_->update();
    
    if (this->image_){
        image_->update();
    }

    vector<Id> keys = this->elements_->getAllKeys();
    
    for(auto key : keys) {
        GraphicsMapElement *element = this->elements_->get(key);
        element->update();
        //delete element;
    }
    
    SDL_RenderPresent(this->renderer_);

}


void GameGraphics::createEntity(Id id, const string &source, int sizeX, int sizeY, int posX, int posY, orientation_t orientation){
    GraphicsMapElement *newElement = new GraphicsMapElement(source, sizeX, sizeY, posX, posY, orientation);
    this->elements_->put(id, newElement);
}


void GameGraphics::updateEntity(Id id, int posX, int posY, orientation_t orientation){
    GraphicsMapElement *oneElement = this->elements_->get(id);
    if (!oneElement){
        Logger::getInstance()->log(ERROR, "No se pudo acutualizar el estado del elemento debido a que el id es inexistente");
    }
    else{
        oneElement->setNewPosition(posX, posY, orientation);
        this->elements_->put(id, oneElement);
    }
}


void GameGraphics::deadEntity(Id id){
        this->elements_->deleteElement(id);
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

    this->scenario_ = new GraphicsScenario(background);

    Logger::getInstance()->log(DEBUG, "Se actualiza el background");

}
 

void GameGraphics::setImage(const string &source){
    if (this->scenario_){
        delete this->scenario_;
        this->scenario_= nullptr;
    }
    this->image_ = new GraphicsMapElement(source, GameProvider::getWidth(),GameProvider::getHeight(),0,0,FRONT);
}