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