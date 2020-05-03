#include "Map.h"
#include <string>

Map::Map() {
}

/*MapElement* Map::createMapElement(){
    auto *mapElement = new MapElement();
    IdElement lastId = lastId_;

    mapElements_[++lastId_] = mapElement;
    return mapElement;
}*/

void Map::addMapElement(MapElement *newMapElement){
    IdElement lastId = this->lastId_;
    this->lastId_++;
    
    newMapElement->setIdElement(lastId);
    this->mapElements_[lastId] = newMapElement;
}

void Map::clearMap() {
    mapElements_.clear();
    lastId_ = 0;
    Logger::getInstance()->log(DEBUG, "Se vaciaron los elementos del mapa");
}

vector<MapElement*> Map::getElements(){
    vector<MapElement *> mapElements(mapElements_.size());
    auto value_selector = [](auto pair) { return pair.second; };
    transform(mapElements_.begin(), mapElements_.end(), mapElements.begin(), value_selector);
    return mapElements;
}

int Map:: move_in_direction( string movement_instruction,int id){
    // si devuelve 0 todo ok, ante cualquier problema que devuelva 1 
    //para poder registrarlo en el logger
    return 0;
    
}