#include "GameGraphics.h"
#include <stdio.h>

GameGraphics::GameGraphics(SDL_Renderer* renderer){
    this->image_ = nullptr;
    this->renderer_ = renderer;
    this->createElements();
    this->createScenes();
    this->createScenarios();
    this->graphicsQueue_ = new BlockingQueue<elementToGraphic_t>();
}


GameGraphics::~GameGraphics(){
    for(auto scenario:this->scenaries_)
        delete scenario.second;
    if(this->image_)
        delete this->image_;
    for(auto element:this->elements_)
        delete element.second;

    Logger::getInstance()->log(INFO, "Se liberan los recursos utilizados para los gŕaficos del juego");
}

void GameGraphics::createElements(){
    vector<string> sourcePlayers;
    vector<string> sourcePlayersDisconnected;

    for (int i = 0; i < 4; i++){
        player_t onePlayer = GameProvider::getConfig()->getPlayerParam(i);
        sourcePlayers.push_back(onePlayer.sprite);
        sourcePlayersDisconnected.push_back(onePlayer.spriteDisconnected);
    }

    string sourceEnemy1 = GameProvider::getConfig()->getPathEnemy(0);
    string sourceEnemy2 = GameProvider::getConfig()->getPathEnemy(1);

    string sourceBoss = GameProvider::getConfig()->getPathFinalBoss();
    string sourceProjectile = "assets/Projectile/projectile.png";
    
    this->elements_[PLAYER_1] = new GraphicsMapElement(sourcePlayers[0], GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[PLAYER_2] = new GraphicsMapElement(sourcePlayers[1], GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[PLAYER_3] = new GraphicsMapElement(sourcePlayers[2], GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[PLAYER_4] = new GraphicsMapElement(sourcePlayers[3], GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[PLAYER_1_OUT] = new GraphicsMapElement(sourcePlayersDisconnected[0], GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[PLAYER_2_OUT] = new GraphicsMapElement(sourcePlayersDisconnected[1], GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[PLAYER_3_OUT] = new GraphicsMapElement(sourcePlayersDisconnected[2], GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[PLAYER_4_OUT] = new GraphicsMapElement(sourcePlayersDisconnected[3], GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[ENEMY_1] = new GraphicsMapElement(sourceEnemy1, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[ENEMY_2] = new GraphicsMapElement(sourceEnemy2, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[BOSS_ENEMY] = new GraphicsMapElement(sourceBoss, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[PROJECTILE] = new GraphicsMapElement(sourceProjectile, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
}

void GameGraphics::createScenes(){

    transitionScreen_t transitionScreenStage1 = GameProvider::getConfig()->getTransitionScreenForStage(STAGE_ONE);
    transitionScreen_t transitionScreenStage2 = GameProvider::getConfig()->getTransitionScreenForStage(STAGE_TWO);
    transitionScreen_t transitionScreenStage3 = GameProvider::getConfig()->getTransitionScreenForStage(STAGE_THREE);
    transitionScreen_t transitionScreenStage4 = GameProvider::getConfig()->getTransitionScreenForStage(STAGE_FOUR);
    
    informationScreen_t informationScreen = GameProvider::getConfig()->getinformationScreen();
    
    this->scenes_[INIT_STAGE_1] = new GraphicsMapElement(transitionScreenStage1.initPath, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[END_STAGE_1] = new GraphicsMapElement(transitionScreenStage1.endPath, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[INIT_STAGE_2] = new GraphicsMapElement(transitionScreenStage2.initPath, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[END_STAGE_2] = new GraphicsMapElement(transitionScreenStage2.endPath, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[INIT_STAGE_3] = new GraphicsMapElement(transitionScreenStage3.initPath, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[END_STAGE_3] = new GraphicsMapElement(transitionScreenStage3.endPath, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[INIT_STAGE_4] = new GraphicsMapElement(transitionScreenStage4.initPath, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[END_STAGE_4] = new GraphicsMapElement(transitionScreenStage4.endPath, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[END_GAME_ANIMATION] = new GraphicsMapElement(informationScreen.endGame, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[WAITING_PLAYERS] = new GraphicsMapElement(informationScreen.waitingPlayers, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[SERVER_DISCONNECTION] = new GraphicsMapElement(informationScreen.disconnection, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);

}

void GameGraphics::createScenarios(){
    
    stageSource_t stage1 = GameProvider::getConfig()->getSourcesForStage(STAGE_ONE);

    stageSource_t stage2 = GameProvider::getConfig()->getSourcesForStage(STAGE_TWO);

    stageSource_t stage3 = GameProvider::getConfig()->getSourcesForStage(STAGE_THREE);

    stageSource_t stage4 = GameProvider::getConfig()->getSourcesForStage(STAGE_FOUR);

    this->scenaries_[STAGE_ONE] = new GraphicsScenario(stage1);
    this->scenaries_[STAGE_TWO] = new GraphicsScenario(stage2);
    this->scenaries_[STAGE_THREE] = new GraphicsScenario(stage3);
    this->scenaries_[STAGE_FOUR] = new GraphicsScenario(stage4);

}

void GameGraphics::updateEntity(elementType_t type, position_t position){
   if (type == END_GRAPHIC){
        SDL_RenderPresent(this->renderer_);
        SDL_RenderClear(this->renderer_);
    }
    else{
        auto iter = this->elements_.find(type);
        if (iter != this->elements_.end()){
            this->elements_[type]->update(position);
        }
    }          
}


void GameGraphics::updateBackgroundLayer(layer_t layer, stage_t stage, int step){
    auto iter = this->scenaries_.find(stage); 
    if (iter != this->scenaries_.end()){
        this->scenaries_[stage]->update(layer,step);
    }          
}


void GameGraphics::setImage(sceneScreen_t scene){
    usleep(100000);
    SDL_RenderClear(this->renderer_);
    position_t position;
    position.axis_x= 0;
    position.axis_y= 0;
    position.orientation= FRONT;
 
    auto iter = this->scenes_.find(scene);
    if ( iter != this->scenes_.end()){
        this->scenes_[scene]->update(position);
        SDL_RenderPresent(this->renderer_);
    }
    
}