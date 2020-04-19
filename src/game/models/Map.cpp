#include "Map.h"

Map::Map() {}

Map::~Map() {
    clearMap();
}

MapElement* Map::createMapElement(){
    auto *mapElement = new MapElement();
    IdElement lastId = lastId_;

    mapElements_[++lastId_] = mapElement;
    return mapElement;
}

void Map::clearMap() {
    mapElements_.clear();
    lastId_ = 0;
    GameProvider::getLogger()->log(DEBUG, "Se vaciaron los elementos del mapa");
}

vector<MapElement*> Map::getElements(){
    vector<MapElement *> mapElements(mapElements_.size());
    auto value_selector = [](auto pair) { return pair.second; };
    transform(mapElements_.begin(), mapElements_.end(), mapElements.begin(), value_selector);
    return mapElements;
}