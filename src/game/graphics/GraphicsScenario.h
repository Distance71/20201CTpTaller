#ifndef _GRAPHICSSCENARIO_H_
#define _GRAPHICSSCENARIO_H_

#include "Graphics.h"
#include "../../providers/GameProvider.h"
#include "SDL2/SDL_image.h"
#include "../../game/models/Speed.h"
#include "../../game/models/Position.h"
#include <vector>

using namespace std;

class GraphicsScenario: public Graphics {
    private:
    //size_t level_;
    //Asumo que respetan el orden
    vector<Sprite *> sprites_; //refactor if add more levels
    vector<Speed *> layersSpeeds_;
    vector<Position *> layersPositions_;

    public:
    GraphicsScenario(LEVEL_NUMBER level);
    //~GraphicsScenario();
    void update(); //Add override later
};

#endif