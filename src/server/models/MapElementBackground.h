#ifndef _MAP_ELEMENT_BACKGROUND_H_
#define _MAP_ELEMENT_BACKGROUND_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "../../common/models/State.h"
#include "../../common/models/Action.h"
#include "../../common/models/Orientation.h"
#include "../../common/models/Position.h"
#include "Speed.h"
#include "../../common/types.h"
#include "PlayerController.h"

using namespace std;

class MapElementBackground {

    private:
        layer_t layer_;
        stage_t stage_;
        Position* position_;
        Speed* speed_;

    public:
        MapElementBackground(layer_t layer, stage_t stage, Speed* speed, Position* position);
       
        void update();

        int getStep();
        stage_t getStage();
        layer_t getLayer();

};

#endif