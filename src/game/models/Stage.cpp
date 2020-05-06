#include "Stage.h"

//Stage::Stage();
//Stage::~Stage();

void Stage::update(){
    for(auto mapElement : mapElements_) {
        mapElement.second->update();
    }
}

void Stage::createPlayer(){
    MapElement* player = new MapElement(PLAYER);
    lastId_++;

    Position *initialPosition = new Position(); //Should have a initial player positionHandler
    Speed *speed = new Speed(); //This should be taken from config
    Orientation *initialOrientation = new Orientation(); //Should be Front
    Graphics *graphics = new GraphicsSpacecraft();
    MovementHandler *movementHandler = new PlayerController(lastId_);

    player->addState("Position", initialPosition);
    player->addState("Speed", speed);
    player->addState("Orientation", initialOrientation);
    player->addAction("Graphics", graphics);
    player->addAction("MovementHandler", movementHandler);

    mapElements_[lastId_] = player;
}

void Stage::createEnemy(){
    MapElement* enemy = new MapElement(ENEMY);
    lastId_++;

    Position *initialPosition = new Position(); //Should have a initial player positionHandler() or class if grows
    Speed *speed = new Speed(); //This should be taken from config
    Orientation *initialOrientation = new Orientation(); //Should be Front
    Graphics *graphics = new GraphicsSpacecraft();
    MovementHandler *movementHandler = new PlayerController(lastId_);

    enemy->addState("Position", initialPosition);
    enemy->addState("Speed", speed);
    enemy->addState("Orientation", initialOrientation);
    enemy->addAction("Graphics", graphics);
    enemy->addAction("MovementHandler", movementHandler);

    mapElements_[lastId_] = enemy;
}

void Stage::createBackground(level_t level){
    MapElement* background = new MapElement(BACKGROUND);
    lastId_++;

    Graphics *graphics = new GraphicsScenario(LEVEL_ONE);

    background->addAction("Graphics", graphics);

    mapElements_[lastId_] = background;
}

void Stage::killMapElement(IdElement id){
    if(!mapElements_[id] || id > lastId_){
        Logger::getInstance()->log(ERROR, "Se intentó eliminar un elemento del mapa invalido");
        return;
    }
    delete mapElements_[id];
    mapElements_[id] = NULL;
}