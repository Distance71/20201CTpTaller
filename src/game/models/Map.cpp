#include "Map.h"

Map::Map() {
}

/*MapElement* Map::crateMapElement(){
    auto *mapElement = new MapElement();
    IdElement lastId = lastId_;

    mapElements_[++lastId_] = mapElement;
    return mapElement;
}*/

void Map::addStage(Stage *stage){
    if(!stage) {
        Logger::getInstance()->log(ERROR, "Se intentó agregar un stage invalido");
        return;
    }
    this->stages_.push_back(stage);
}

void Map::clearMap() {
    //mapElements_.clear();
    Logger::getInstance()->log(DEBUG, "Se vaciaron los elementos del mapa");
}

// vector<MapElement*> Map::getElements(){
//     vector<MapElement *> mapElements(mapElements_.size());
//     auto value_selector = [](auto pair) { return pair.second; };
//     transform(mapElements_.begin(), mapElements_.end(), mapElements.begin(), value_selector);
//     return mapElements;
// }

int Map::move_in_direction( string movement_instruction, int id){
    // si devuelve 0 todo ok, ante cualquier problema que devuelva 1 
    //para poder registrarlo en el logger
    return 0;
}

void Map::update(){
    for(size_t i = 0; i < stages_.size(); i++) {
        stages_[i]->update();
    }
}

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
    auto *graphics = new GraphicsSpacecraft();
    auto *movementHandler = new PlayerController(lastId_);

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
    auto *graphics = new GraphicsSpacecraft();
    auto *movementHandler = new PlayerController(lastId_);

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

    auto *graphics = new GraphicsScenario(LEVEL_ONE);

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