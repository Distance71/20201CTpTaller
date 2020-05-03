#ifndef _GRAPHICSSCENARIO_H_
#define _GRAPHICSSCENARIO_H_

#include "Graphics.h"
#include "../../providers/GameProvider.h"
#include "SDL2/SDL_image.h"

class GraphicsScenario: public Graphics {
    private:
    int level;

    public:
    GraphicsScenario(int stage);
    //~GraphicsScenario();
};

#endif