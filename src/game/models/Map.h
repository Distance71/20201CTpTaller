#ifndef _MAP_H_
#define _MAP_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "MapElement.h"
#include "../../providers/GameProvider.h"
#include "Position.h"
#include "Speed.h"
#include "Orientation.h"
#include "../graphics/GraphicsSpacecraft.h"
#include "../graphics/GraphicsScenario.h"
#include "MovementHandler.h"
#include "PlayerController.h"

// Es el contenedor principal del juego. Se va mostrando una parte de este en la pantalla

class Stage;

class Map {
    private:
    vector<Stage *> stages_;
    //IdElement lastId_ = 0;
    void clearMap();

    public:
        Map();
        int move_in_direction(string movement_instruction,int id);
        //vector<MapElement* > getElements();
        // MapElement* createMapElement();
        void addStage(Stage* Stage);
        void update();
};

class Stage: public Map {
    private:
    unordered_map<IdElement, MapElement*> mapElements_;
    IdElement lastId_ = 0;

    public:
    // Stage();
    //~Stage();

    void update();
    void createPlayer();
    void createEnemy();
    void createBackground(level_t level);
    void killMapElement(IdElement id);
};

#endif