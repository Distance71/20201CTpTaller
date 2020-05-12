#ifndef _GRAPHICS_SCENARIO_H_
#define _GRAPHICS_SCENARIO_H_

class Sprite;

#include "../../providers/GameProvider.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../../game/models/Speed.h"
#include "../../game/models/Position.h"
#include "../../game/models/Sprite.h"
#include <vector>
#include "../types.h"
#include "Graphics.h"

class GraphicsScenario {
    private:
    //size_t level_;
    //Asumo que respetan el orden
    vector<Sprite *> sprites_; //refactor if add more levels
    vector<Speed *> layersSpeeds_;
    vector<Position *> layersPositions_;

    public:
    GraphicsScenario(stageSource_t stageSource);
    //~GraphicsScenario();
    void update(); //Add override later
    
};

#endif