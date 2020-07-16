#ifndef _GAME_GRAPHICS_
#define _GAME_GRAPHICS_


#include <unordered_map>
#include "GraphicsMapElement.h"
#include "GraphicsScenario.h"
#include "../../../common/types.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../../../common/providers/GameProvider.h"
#include "../../../common/services/Logger.h"


class GameGraphics {

    private:
        SDL_Renderer* renderer_;
        unordered_map <elementType_t, GraphicsMapElement*> elements_;
        unordered_map <sceneScreen_t, GraphicsMapElement*> scenes_;
        GraphicsScenario * scenario_;
        GraphicsMapElement* image_;
        std::mutex              mutex;

        void createScenes();
        void createElements();
    public:

        GameGraphics(SDL_Renderer* renderer);
        ~GameGraphics();
        void update();
        void updateEntity(elementType_t type, position_t position);
        
        void setBackground(stageSource_t background);
        void setImage(sceneScreen_t scene);
};

#endif