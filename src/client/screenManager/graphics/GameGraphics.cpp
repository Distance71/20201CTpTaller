#include "GameGraphics.h"
#include <stdio.h>

GameGraphics::GameGraphics(SDL_Renderer* renderer){
    this->image_ = nullptr;
    this->renderer_ = renderer;
    this->createElements();
    this->createScenes();
    this->createScenarios();
    this->scoreBoard_ = new GraphicsScoreBoard();
}


GameGraphics::~GameGraphics(){
    for(auto scenario:this->scenaries_)
        delete scenario.second;
    if(this->image_)
        delete this->image_;
    for(auto element:this->elements_)
        delete element.second;

    delete this->scoreBoard_;

    Logger::getInstance()->log(INFO, "Se liberan los recursos utilizados para los gŕaficos del juego");
}

void GameGraphics::createElements(){
    vector<player_t> players;
    vector<string> sourcePlayersDisconnected;

    for (int i = 0; i < 4; i++){
        player_t onePlayer = GameProvider::getConfig()->getPlayerParam(i);
        players.push_back(onePlayer);
    }

    enemy_t enemy1A = GameProvider::getConfig()->getEnemyData(0, 0);
    enemy_t enemy2A = GameProvider::getConfig()->getEnemyData(0, 1);
    enemy_t enemy1B = GameProvider::getConfig()->getEnemyData(1, 0);
    enemy_t enemy2B = GameProvider::getConfig()->getEnemyData(1, 1);
    enemy_t enemy1C = GameProvider::getConfig()->getEnemyData(2, 0);
    enemy_t enemy2C = GameProvider::getConfig()->getEnemyData(2, 1);
    enemy_t enemy1D = GameProvider::getConfig()->getEnemyData(3, 0);
    enemy_t enemy2D = GameProvider::getConfig()->getEnemyData(3, 1);

    enemy_t finalBoss = GameProvider::getConfig()->getFinalBoss();
    projectile_t projectile = GameProvider::getConfig()->getProjectileData();
    projectile_t projectileBoss = GameProvider::getConfig()->getProjectileBossData();

    string sourceProjectile = "assets/Projectile/projectile.png";
    string sourceProjectileBoss = "assets/Projectile/projectileBoss.png";
    string sourceExplosionAnimation1 = "assets/Explosions/Explosion1/Explosion1.png";
    string sourceExplosionAnimation2 = "assets/Explosions/Explosion1/Explosion2.png";
    string sourceExplosionAnimation3 = "assets/Explosions/Explosion1/Explosion3.png";
    string sourceExplosionAnimation4 = "assets/Explosions/Explosion1/Explosion4.png";
    string sourceExplosionAnimation5 = "assets/Explosions/Explosion1/Explosion5.png";
    string sourceExplosionAnimation6 = "assets/Explosions/Explosion1/Explosion6.png";
    string sourceExplosionAnimation7 = "assets/Explosions/Explosion1/Explosion7.png";
    string sourceExplosionAnimation8 = "assets/Explosions/Explosion1/Explosion8.png";
    string sourceExplosionAnimation9 = "assets/Explosions/Explosion1/Explosion9.png";
    string sourceExplosionAnimation10 = "assets/Explosions/Explosion1/Explosion10.png";
    string sourceExplosionAnimation11 = "assets/Explosions/Explosion1/Explosion11.png";

    this->elements_[PLAYER_1] = new GraphicsMapElement(players[0].sprite, players[0].size_x, players[0].size_y, 0, 0, FRONT);
    this->elements_[PLAYER_2] = new GraphicsMapElement(players[1].sprite, players[1].size_x, players[1].size_y, 0, 0, FRONT);
    this->elements_[PLAYER_3] = new GraphicsMapElement(players[2].sprite, players[2].size_x, players[2].size_y, 0, 0, FRONT);
    this->elements_[PLAYER_4] = new GraphicsMapElement(players[3].sprite, players[3].size_x, players[3].size_y, 0, 0, FRONT);
    this->elements_[PLAYER_1_OUT] = new GraphicsMapElement(players[0].spriteDisconnected, players[0].size_x, players[0].size_y, 0, 0, FRONT);
    this->elements_[PLAYER_2_OUT] = new GraphicsMapElement(players[1].spriteDisconnected, players[1].size_x, players[1].size_y, 0, 0, FRONT);
    this->elements_[PLAYER_3_OUT] = new GraphicsMapElement(players[2].spriteDisconnected, players[2].size_x, players[2].size_y, 0, 0, FRONT);
    this->elements_[PLAYER_4_OUT] = new GraphicsMapElement(players[3].spriteDisconnected, players[3].size_x, players[3].size_y, 0, 0, FRONT);
    
    this->elements_[ENEMY_1_A] = new GraphicsMapElement(enemy1A.sprite, enemy1A.size_x, enemy1A.size_y, 0, 0, FRONT);
    this->elements_[ENEMY_2_A] = new GraphicsMapElement(enemy2A.sprite, enemy2A.size_x, enemy2A.size_y, 0, 0, FRONT);
    this->elements_[ENEMY_1_B] = new GraphicsMapElement(enemy1B.sprite, enemy1B.size_x, enemy1B.size_y, 0, 0, FRONT);
    this->elements_[ENEMY_2_B] = new GraphicsMapElement(enemy2B.sprite, enemy2B.size_x, enemy2B.size_y, 0, 0, FRONT);
    this->elements_[ENEMY_1_C] = new GraphicsMapElement(enemy1C.sprite, enemy1C.size_x, enemy1C.size_y, 0, 0, FRONT);
    this->elements_[ENEMY_2_C] = new GraphicsMapElement(enemy2C.sprite, enemy2C.size_x, enemy2C.size_y, 0, 0, FRONT);
    this->elements_[ENEMY_1_D] = new GraphicsMapElement(enemy1D.sprite, enemy1D.size_x, enemy1D.size_y, 0, 0, FRONT);
    this->elements_[ENEMY_2_D] = new GraphicsMapElement(enemy2D.sprite, enemy2D.size_x, enemy2D.size_y, 0, 0, FRONT);

    this->elements_[BOSS_ENEMY] = new GraphicsMapElement(finalBoss.sprite, finalBoss.size_x, finalBoss.size_y, 0, 0, FRONT);
    this->elements_[PROJECTILE] = new GraphicsMapElement(projectile.sprite, projectile.size_x, projectile.size_y, 0, 0, FRONT);
    this->elements_[PROJECTILE_BOSS] = new GraphicsMapElement(projectileBoss.sprite, projectileBoss.size_x, projectileBoss.size_y, 0, 0, FRONT);

    this->elements_[EXPLOSION_ANIMATION_1] = new GraphicsMapElement(sourceExplosionAnimation1, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_2] = new GraphicsMapElement(sourceExplosionAnimation2, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_3] = new GraphicsMapElement(sourceExplosionAnimation3, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_4] = new GraphicsMapElement(sourceExplosionAnimation4, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_5] = new GraphicsMapElement(sourceExplosionAnimation5, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_6] = new GraphicsMapElement(sourceExplosionAnimation6, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_7] = new GraphicsMapElement(sourceExplosionAnimation7, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_8] = new GraphicsMapElement(sourceExplosionAnimation8, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_9] = new GraphicsMapElement(sourceExplosionAnimation9, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_10] = new GraphicsMapElement(sourceExplosionAnimation10, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_11] = new GraphicsMapElement(sourceExplosionAnimation11, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);

    this->elements_[EXPLOSION_ANIMATION_BOSS_1] = new GraphicsMapElement(sourceExplosionAnimation1, finalBoss.size_x, finalBoss.size_y, 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_BOSS_2] = new GraphicsMapElement(sourceExplosionAnimation2, finalBoss.size_x, finalBoss.size_y, 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_BOSS_3] = new GraphicsMapElement(sourceExplosionAnimation3, finalBoss.size_x, finalBoss.size_y, 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_BOSS_4] = new GraphicsMapElement(sourceExplosionAnimation4, finalBoss.size_x, finalBoss.size_y, 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_BOSS_5] = new GraphicsMapElement(sourceExplosionAnimation5, finalBoss.size_x, finalBoss.size_y, 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_BOSS_6] = new GraphicsMapElement(sourceExplosionAnimation6, finalBoss.size_x, finalBoss.size_y, 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_BOSS_7] = new GraphicsMapElement(sourceExplosionAnimation7, finalBoss.size_x, finalBoss.size_y, 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_BOSS_8] = new GraphicsMapElement(sourceExplosionAnimation8, finalBoss.size_x, finalBoss.size_y, 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_BOSS_9] = new GraphicsMapElement(sourceExplosionAnimation9, finalBoss.size_x, finalBoss.size_y, 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_BOSS_10] = new GraphicsMapElement(sourceExplosionAnimation10, finalBoss.size_x, finalBoss.size_y, 0, 0, FRONT);
    this->elements_[EXPLOSION_ANIMATION_BOSS_11] = new GraphicsMapElement(sourceExplosionAnimation11, finalBoss.size_x, finalBoss.size_y, 0, 0, FRONT);   
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
    this->scenes_[GAME_OVER_ANIMATION] = new GraphicsMapElement(informationScreen.gameOver, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);

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
        this->scoreBoard_->update();
        SDL_RenderPresent(this->renderer_);
        SDL_RenderClear(this->renderer_);
    }
    else{
        try{
            this->elements_[type]->update(position);
        }
        catch (const std::out_of_range& oor){
            std::cerr << "Out of Range error in GameGraphics UpdateEntity " << oor.what() << '\n';
        }     
    }          
}


void GameGraphics::updateBackgroundLayer(layer_t layer, stage_t stage, int step){
    try{
        this->scenaries_[stage]->update(layer,step);
    }
    catch (const std::out_of_range& oor){
        std::cerr << "Out of Range error in GameGraphics updateBackgroundLayer: " << oor.what() << '\n';
    }               
}

void GameGraphics::setImage(sceneScreen_t scene){
    usleep(100000);
    SDL_RenderClear(this->renderer_);
    position_t position;
    position.axis_x= 0;
    position.axis_y= 0;
    position.orientation= FRONT;
    
    if (scene == SCORE_TABLE){
        this->scoreBoard_->showScores();
    }   
    
    else{
        try{
            this->scenes_[scene]->update(position);
        }
        catch (const std::out_of_range& oor){
            std::cerr << "Out of Range in GameGraphics setImage " << oor.what() << '\n';
        }
    } 
    SDL_RenderPresent(this->renderer_);
}

void GameGraphics::setAudio(musicType_t scene){

    switch (scene)
    {
    case MUSIC_STAGE_ONE:
        Audio::getInstance()->setSong("assets/Music/stage_1.mp3");   
        Audio::getInstance()->playMusic(); 
        break;
    case MUSIC_STAGE_TWO:
        Audio::getInstance()->setSong("assets/Music/stage_2.mp3");   
        Audio::getInstance()->playMusic(); 
        break;
    case MUSIC_STAGE_THREE:
        Audio::getInstance()->setSong("assets/Music/stage_3.mp3");   
        Audio::getInstance()->playMusic(); 
        break;
    case MUSIC_STAGE_FOUR:
        Audio::getInstance()->setSong("assets/Music/stage_boss.mp3");   
        Audio::getInstance()->playMusic(); 
        break;
    default:
        break;
    }
}

void GameGraphics::updateScore(elementType_t playerImage,unsigned int lives,int health,int levelScore,int totalScore){
    this->scoreBoard_->updateScore(playerImage,lives,health,levelScore,totalScore);
}