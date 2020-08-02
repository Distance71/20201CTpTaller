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
    vector<player_t> players;
    vector<string> sourcePlayersDisconnected;

    for (int i = 0; i < 4; i++){
        player_t onePlayer = GameProvider::getConfig()->getPlayerParam(i);
        players.push_back(onePlayer);
    }

    enemy_t enemy1 = GameProvider::getConfig()->getEnemyData(0);
    enemy_t enemy2 = GameProvider::getConfig()->getEnemyData(1);

    string sourceBoss = GameProvider::getConfig()->getPathFinalBoss();
    projectile_t projectile = GameProvider::getConfig()->getProjectileData();

    string sourceProjectile = "assets/Projectile/projectile.png";
    string sourceExplosionAnimation1 = "assets/Explosions/Explosion1_1.png";
    string sourceExplosionAnimation2 = "assets/Explosions/Explosion1_2.png";
    string sourceExplosionAnimation3 = "assets/Explosions/Explosion1_3.png";
    string sourceExplosionAnimation4 = "assets/Explosions/Explosion1_4.png";
    string sourceExplosionAnimation5 = "assets/Explosions/Explosion1_5.png";
    string sourceExplosionAnimation6 = "assets/Explosions/Explosion1_6.png";
    string sourceExplosionAnimation7 = "assets/Explosions/Explosion1_7.png";
    string sourceExplosionAnimation8 = "assets/Explosions/Explosion1_8.png";
    string sourceExplosionAnimation9 = "assets/Explosions/Explosion1_9.png";
    string sourceExplosionAnimation10 = "assets/Explosions/Explosion1_10.png";
    string sourceExplosionAnimation11 = "assets/Explosions/Explosion1_11.png";

    this->elements_[PLAYER_1] = new GraphicsMapElement(players[0].sprite, players[0].size_x, players[0].size_y, 0, 0, FRONT);
    this->elements_[PLAYER_2] = new GraphicsMapElement(players[1].sprite, players[1].size_x, players[1].size_y, 0, 0, FRONT);
    this->elements_[PLAYER_3] = new GraphicsMapElement(players[2].sprite, players[2].size_x, players[2].size_y, 0, 0, FRONT);
    this->elements_[PLAYER_4] = new GraphicsMapElement(players[3].sprite, players[3].size_x, players[3].size_y, 0, 0, FRONT);
    this->elements_[PLAYER_1_OUT] = new GraphicsMapElement(players[0].spriteDisconnected, players[0].size_x, players[0].size_y, 0, 0, FRONT);
    this->elements_[PLAYER_2_OUT] = new GraphicsMapElement(players[1].spriteDisconnected, players[1].size_x, players[1].size_y, 0, 0, FRONT);
    this->elements_[PLAYER_3_OUT] = new GraphicsMapElement(players[2].spriteDisconnected, players[2].size_x, players[2].size_y, 0, 0, FRONT);
    this->elements_[PLAYER_4_OUT] = new GraphicsMapElement(players[3].spriteDisconnected, players[3].size_x, players[3].size_y, 0, 0, FRONT);
    this->elements_[ENEMY_1] = new GraphicsMapElement(enemy1.sprite, enemy1.size_x, enemy1.size_y, 0, 0, FRONT);
    this->elements_[ENEMY_2] = new GraphicsMapElement(enemy2.sprite, enemy2.size_x, enemy2.size_y, 0, 0, FRONT);
    this->elements_[BOSS_ENEMY] = new GraphicsMapElement(sourceBoss, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[PROJECTILE] = new GraphicsMapElement(projectile.sprite, projectile.size_x, projectile.size_y, 0, 0, FRONT);

    // this->elements_[EXPLOSION_ANIMATION_1] = new GraphicsMapElement(sourceExplosionAnimation1, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    // this->elements_[EXPLOSION_ANIMATION_2] = new GraphicsMapElement(sourceExplosionAnimation2, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    // this->elements_[EXPLOSION_ANIMATION_3] = new GraphicsMapElement(sourceExplosionAnimation3, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    // this->elements_[EXPLOSION_ANIMATION_4] = new GraphicsMapElement(sourceExplosionAnimation4, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    // this->elements_[EXPLOSION_ANIMATION_5] = new GraphicsMapElement(sourceExplosionAnimation5, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    // this->elements_[EXPLOSION_ANIMATION_6] = new GraphicsMapElement(sourceExplosionAnimation6, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    // this->elements_[EXPLOSION_ANIMATION_7] = new GraphicsMapElement(sourceExplosionAnimation7, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    // this->elements_[EXPLOSION_ANIMATION_8] = new GraphicsMapElement(sourceExplosionAnimation8, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    // this->elements_[EXPLOSION_ANIMATION_9] = new GraphicsMapElement(sourceExplosionAnimation9, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    // this->elements_[EXPLOSION_ANIMATION_10] = new GraphicsMapElement(sourceExplosionAnimation10, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    // this->elements_[EXPLOSION_ANIMATION_11] = new GraphicsMapElement(sourceExplosionAnimation11, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);

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