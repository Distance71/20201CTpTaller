#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include <unordered_map>
#include <algorithm>
#include "MapElement.h"
#include "../../providers/GameProvider.h"

using IdElement = size_t;

// Es el contenedor principal del juego. Se va mostrando una parte de este en la pantalla

class Map {

    unordered_map<IdElement, MapElement*> mapElements_;
    IdElement lastId_ = 0;
    void clearMap();

    public:
    Map();
    ~Map();

    vector<MapElement* > getElements();
    MapElement* createMapElement();
};

#endif