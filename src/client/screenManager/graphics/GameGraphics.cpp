#include "GameGraphics.h"
#include <stdio.h>

GameGraphics::GameGraphics(SDL_Renderer* renderer){
    this->scenario_ = nullptr;
    this->image_ = nullptr;
    this->renderer_ = renderer;
    this->createElements();
    this->createScenes();
    this->createScenarios();
    this->graphicsQueue_ = new BlockingQueue<elementToGraphic_t>();
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
    string sourcePlayer1Disconnected = "assets/Players/player1Reducido_Out.png";
    string sourcePlayer2Disconnected = "assets/Players/player2Reducido_Out.png";
    string sourcePlayer3Disconnected = "assets/Players/player3Reducido_Out.png";
    string sourcePlayer4Disconnected = "assets/Players/player4Reducido_Out.png";
    this->elements_[PLAYER_1] = new GraphicsMapElement(sourcePlayer1, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[PLAYER_2] = new GraphicsMapElement(sourcePlayer2, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[PLAYER_3] = new GraphicsMapElement(sourcePlayer3, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[PLAYER_4] = new GraphicsMapElement(sourcePlayer4, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[PLAYER_1_OUT] = new GraphicsMapElement(sourcePlayer1Disconnected, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[PLAYER_2_OUT] = new GraphicsMapElement(sourcePlayer2Disconnected, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[PLAYER_3_OUT] = new GraphicsMapElement(sourcePlayer3Disconnected, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
    this->elements_[PLAYER_4_OUT] = new GraphicsMapElement(sourcePlayer4Disconnected, GameProvider::getElementsSize(), GameProvider::getElementsSize(), 0, 0, FRONT);
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
    string sourceInitStage4 = "assets/TransitionScreens/Stage4.JPG";
    string sourceEndStage4 = "assets/TransitionScreens/Stage4Cleared.JPG";    
    string sourceEndGame = "assets/TransitionScreens/gameOver.png";
    string sourceWaitingPlayers = "assets/TransitionScreens/waitingForPlayers.png";
    this->scenes_[INIT_STAGE_1] = new GraphicsMapElement(sourceInitStage1, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[END_STAGE_1] = new GraphicsMapElement(sourceEndStage1, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[INIT_STAGE_2] = new GraphicsMapElement(sourceInitStage2, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[END_STAGE_2] = new GraphicsMapElement(sourceEndStage2, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[INIT_STAGE_3] = new GraphicsMapElement(sourceInitStage3, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[END_STAGE_3] = new GraphicsMapElement(sourceEndStage3, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[INIT_STAGE_4] = new GraphicsMapElement(sourceInitStage4, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[END_STAGE_4] = new GraphicsMapElement(sourceEndStage4, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[END_GAME_ANIMATION] = new GraphicsMapElement(sourceEndGame, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);
    this->scenes_[WAITING_PLAYERS] = new GraphicsMapElement(sourceWaitingPlayers, GameProvider::getWidth(), GameProvider::getHeight(), 0, 0, FRONT);

}

void GameGraphics::createScenarios(){
    stageSource_t stage1;
    stage1.layer1 = "assets/Stage/Level1/layer_1.png";
    stage1.layer2 = "assets/Stage/Level1/layer_2.png";
    stage1.layer3 = "assets/Stage/Level1/layer_3.png";
    stage1.layer4 = "assets/Stage/Level1/layer_4.png";
    stage1.layer5 = "assets/Stage/Level1/layer_5.png";
    stage1.layer6 = "";
    stage1.layer7 = "";

    stageSource_t stage2;
    stage2.layer1 = "assets/Stage/Level2/layer_1.png";
    stage2.layer2 = "assets/Stage/Level2/layer_2.png";
    stage2.layer3 = "assets/Stage/Level2/layer_3.png";
    stage2.layer4 = "assets/Stage/Level2/layer_4.png";
    stage2.layer5 = "assets/Stage/Level2/layer_5.png";
    stage2.layer6 = "assets/Stage/Level2/layer_6.png";
    stage2.layer7 = "assets/Stage/Level2/layer_7.png";

    stageSource_t stage3;
    stage3.layer1 = "assets/Stage/Level3/layer_1.png";
    stage3.layer2 = "assets/Stage/Level3/layer_2.png";
    stage3.layer3 = "assets/Stage/Level3/layer_3.png";
    stage3.layer4 = "assets/Stage/Level3/layer_4.png";
    stage3.layer5 = "assets/Stage/Level3/layer_5.png";
    stage3.layer6 = "assets/Stage/Level3/layer_6.png";
    stage3.layer7 = "assets/Stage/Level3/layer_7.png";

    stageSource_t stage4;
    stage4.layer1 = "assets/Stage/Level4/layer_1.png";
    stage4.layer2 = "assets/Stage/Level4/layer_2.png";
    stage4.layer3 = "assets/Stage/Level4/layer_3.png";
    stage4.layer4 = "assets/Stage/Level4/layer_4.png";
    stage4.layer5 = "";
    stage4.layer6 = "";
    stage4.layer7 = "";

    this->scenaries_[STAGE_ONE] = new GraphicsScenario(stage1);
    this->scenaries_[STAGE_TWO] = new GraphicsScenario(stage2);
    this->scenaries_[STAGE_THREE] = new GraphicsScenario(stage3);
    this->scenaries_[STAGE_FOUR] = new GraphicsScenario(stage4);
}

void GameGraphics::update(){
    SDL_RenderClear(this->renderer_);
    position_t positionImage;
    positionImage.axis_x = 0;
    positionImage.axis_y = 0;
    positionImage.orientation = FRONT;
    vector <elementToGraphic_t> renderElementsBackground;

    if (this->image_){
        this->graphicsQueue_->clear();
        this->image_->update(positionImage);
    }

    if (this->scenario_) {
        this->scenario_->update();
    }
        

    double elaptedTimeMS = GameProvider::getElaptedTimeFPS();
    auto begin = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();   
    auto dur = end - begin;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

    while(0 >= (ms - elaptedTimeMS)) { 
        end = chrono::high_resolution_clock::now();
        dur = end - begin;
        ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        if (!graphicsQueue_->empty()){
            elementToGraphic_t elementToGraphic = graphicsQueue_->pop();
            this->elements_[elementToGraphic.type]->update(elementToGraphic.position);
        }
    }

    SDL_RenderPresent(this->renderer_);
}

void GameGraphics::updateEntity(elementType_t type, position_t position){
    Logger::getInstance()->log(DEBUG, "Se va a actualizar un MapElement en GameGraphics");
    
    elementToGraphic_t elementToGraphic;
    elementToGraphic.position = position;
    elementToGraphic.type = type;
    cout << type << endl;
    this->graphicsQueue_->push(elementToGraphic);
}

void GameGraphics::setBackground(stage_t stage){

    if (this->scenario_){
        this->scenario_=nullptr;
    }

    if (this->image_){
        this->image_=nullptr;
    }
    this->scenario_ = this->scenaries_[stage];

    Logger::getInstance()->log(DEBUG, "Se actualiza el background");
}

void GameGraphics::setImage(sceneScreen_t scene){
    Logger::getInstance()->log(DEBUG, "Se va a cargar imagen de fondo en GameGraphics");
    if (this->scenario_){
        this->scenario_= nullptr;
    }
    if (this->image_){
        this->image_=nullptr;
    }
    this->image_ = this->scenes_[scene];
}