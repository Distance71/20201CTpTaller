#ifndef _GRAPHICS_SCENARIO_H_
#define _GRAPHICS_SCENARIO_H_

class Sprite;

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../../../common/providers/GameProvider.h"
#include "../../../common/models/Sprite.h"
#include "../../../common/models/Position.h"
#include "../../../server/models/Speed.h"
#include <vector>
#include "../../../common/types.h"

class GraphicsScenario {
    private:
    unordered_map<layer_t, Sprite *> sprites_;

    public:
    GraphicsScenario(stageSource_t stageSource);
    ~GraphicsScenario();
    void update(layer_t layer, int step);
    
};

#endif