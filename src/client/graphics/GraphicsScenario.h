#ifndef _GRAPHICS_SCENARIO_H_
#define _GRAPHICS_SCENARIO_H_

class Sprite;

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../../common/providers/GameProvider.h"
#include "../../common/models/Sprite.h"
#include "../../common/models/Position.h"
#include "../../server/models/Speed.h"
#include <vector>
#include "../../common/types.h"

class GraphicsScenario {
    private:
    //size_t level_;
    //Asumo que respetan el orden
    vector<Sprite *> sprites_; //refactor if add more levels
    vector<Speed *> layersSpeeds_;
    vector<Position *> layersPositions_;

    public:
    GraphicsScenario(stageSource_t stageSource);
    ~GraphicsScenario();
    void update(); //Add override later
    
};

#endif