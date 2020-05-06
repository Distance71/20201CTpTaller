#ifndef _STAGE_H_
#define _STAGE_H_

#include "Map.h"
#include "MapElement.h"
#include "Position.h"
#include "Speed.h"
#include "Orientation.h"
#include "../graphics/Graphics.h"
#include "../graphics/GraphicsSpacecraft.h"
#include "../graphics/GraphicsScenario.h"
#include "MovementHandler.h"
#include "PlayerController.h"
#include <unordered_map>

// Se encarga del manejo interno del state de posicion

class Stage: public Map {
    private:
    unordered_map<IdElement, MapElement*> mapElements_;
    IdElement lastId_ = 0;

    public:
    Stage();
    //~Stage();

    void update();
    void createPlayer();
    void createEnemy();
    void createBackground(level_t level);
    void killMapElement(IdElement id);
};

#endif
