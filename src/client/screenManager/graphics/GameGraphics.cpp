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
    
    // for(auto element: this->elements_)
    //     delete element.second;
    
    Logger::getInstance()->log(INFO, "Se liberan los recursos utilizados para los gŕaficos del juego");
}


void GameGraphics::update(){

    // for(size_t i = 20; i <1000; i++) {
    //     auto *falopa = new GraphicsMapElement("assets/Enemies/enemigo1.png", 100, 100, rand() % 1200, rand() % 800, FRONT);
    //     this->elements_.emplace(i, falopa);
    // }
    
    SDL_Renderer* renderer = this->renderer_;
    
    SDL_RenderClear(renderer);

    double elaptedTimeMS = GameProvider::getElaptedTimeFPS();

    auto begin = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();   
    auto dur = end - begin;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();


    while(0 >= (ms - elaptedTimeMS)) { 
        end = chrono::high_resolution_clock::now();
        dur = end - begin;
        ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    }

    if (this->scenario_)
        scenario_->update();
    
    if (this->image_){
        image_->update();
    }

    vector<Id> keys = this->elements_->getAllKeys();

    for(auto key : keys){
        GraphicsMapElement *element = this->elements_->get(key);
        element->update();
    }

    renderer = this->renderer_;
    
    SDL_RenderPresent(renderer);

    // for(size_t i = 20; i <10000; i++)
    //     this->deadEntity(i);

}


void GameGraphics::createEntity(Id id, string source, int sizeX, int sizeY, int posX, int posY, orientation_t orientation){
    GraphicsMapElement *newElement = new GraphicsMapElement(source, sizeX, sizeY, posX, posY, orientation);
    this->elements_->put(id, newElement);
    newElement->set();
}


void GameGraphics::updateEntity(Id id, int posX, int posY, orientation_t orientation){
    // auto iter = this->elements_->find(id);
    // if(iter == this->elements_->end())
    //     return;
    
    // GraphicsMapElement *oneElement = this->elements_.at(id); 
    // if (!oneElement){
    //     Logger::getInstance()->log(ERROR, "No se pudo acutualizar el estado del elemento debido a que el id es inexistente");
    // }
    // else{
    //     //this->elements_[id]->setNewPosition(posX, posY, orientation);
    // }
}


void GameGraphics::deadEntity(Id id){
    // auto iter = this->elements_.find(id);
    // if(iter == this->elements_.end())
    //     return;

    // GraphicsMapElement *oneElement = this->elements_.at(id);
    // if (!oneElement){
    //     Logger::getInstance()->log(ERROR, "No se pudo eliminar el elemento debido a que el id es inexistente");
    // }
    // else {
    //     this->elements_.erase(id);
    //     delete oneElement;
    // }
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