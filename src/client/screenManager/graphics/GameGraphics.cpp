#include "GameGraphics.h"
#include <stdio.h>

GameGraphics::GameGraphics(SDL_Renderer* renderer){
    this->scenario_ = nullptr;
    this->image_ = nullptr;
    this->renderer_ = renderer;
    this->createElements();
    this->createScenes();
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

void GameGraphics::createElements(){
    string sourcePlayer1 = "assets/Players/player1.png";
    string sourcePlayer2 = "assets/Players/player2.png";
    string sourcePlayer3 = "assets/Players/player3.png";
    string sourcePlayer4 = "assets/Players/player4.png";
    string sourceEnemy1 = "assets/Enemies/enemigo1.png";
    string sourceEnemy2 = "assets/Enemies/enemigo2.png";
    this->elements_[PLAYER_1] = new GraphicsMapElement(sourcePlayer1, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[PLAYER_2] = new GraphicsMapElement(sourcePlayer2, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[PLAYER_3] = new GraphicsMapElement(sourcePlayer3, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[PLAYER_4] = new GraphicsMapElement(sourcePlayer4, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[ENEMY_1] = new GraphicsMapElement(sourceEnemy1, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[ENEMY_2] = new GraphicsMapElement(sourceEnemy2, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
}

void GameGraphics::createScenes(){
    string sourceInitStage1 = "assets/TransitionScreens/Stage1.JPG";
    string sourceEndStage1 = "assets/TransitionScreens/Stage1Cleared.JPG";
    string sourceInitStage2 = "assets/TransitionScreens/Stage2.JPG";
    string sourceEndStage2 = "assets/TransitionScreens/Stage2Cleared.JPG";
    string sourceInitStage3 = "assets/TransitionScreens/Stage3.JPG";
    string sourceEndStage3 = "assets/TransitionScreens/Stage3Cleared.JPG";
    string sourceEndGame = "assets/TransitionScreens/gameOver.png";
    string sourceWaitingPlayers = "assets/TransitionScreens/waitingForPlayers.png";
    this->scenes_[INIT_STAGE_1] = new GraphicsMapElement(sourceInitStage1, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[END_STAGE_1] = new GraphicsMapElement(sourceEndStage1, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[INIT_STAGE_2] = new GraphicsMapElement(sourceInitStage2, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[END_STAGE_2] = new GraphicsMapElement(sourceEndStage2, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[INIT_STAGE_3] = new GraphicsMapElement(sourceInitStage3, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[END_STAGE_3] = new GraphicsMapElement(sourceEndStage3, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[END_GAME_ANIMATION] = new GraphicsMapElement(sourceEndGame, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[WAITING_PLAYERS] = new GraphicsMapElement(sourceWaitingPlayers, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
}

void GameGraphics::update(){

    SDL_RenderClear(this->renderer_);
    position_t position;
    position.axis_x = 0;
    position.axis_y = 0;
    position.orientation = FRONT;

    if (this->scenario_)
        scenario_->update();

    if (this->image_){
        image_->update(position);
    }

    SDL_RenderPresent(this->renderer_);

}

void GameGraphics::updateEntity(elementType_t type, position_t position){
    this->elements_[type]->update(position);
}

void GameGraphics::setBackground(stageSource_t background){

    // if (this->scenario_){
    //     delete this->scenario_;
    //     this->scenario_=nullptr;
    // }

    // if (this->image_){
    //     delete this->image_;
    //     this->image_=nullptr;
    // }
    // std::mutex mtx;
    
    // mtx.lock();
    // this->scenario_ = new GraphicsScenario(background);
    // mtx.unlock();

    Logger::getInstance()->log(DEBUG, "Se actualiza el background");

}


void GameGraphics::setImage(sceneScreen_t scene){
    if (this->scenario_){
        delete this->scenario_;
        this->scenario_= nullptr;
    }
    this->image_ = this->scenes_[scene];
}