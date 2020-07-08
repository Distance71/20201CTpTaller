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
        unordered_map <IdElement, GraphicsMapElement*> elements_;
        GraphicsScenario * scenario_;
        GraphicsMapElement* image_;
        
    public:
        
        GameGraphics(SDL_Renderer* renderer);
        ~GameGraphics();
        void update();
        void createEntity(IdElement id, const string &source, int sizeX, int sizeY, int posX, int posY, orientation_t orientation);
        void updateEntity(IdElement id, int posX, int posY, orientation_t orientation);
        void deadEntity(IdElement id);
        void setBackground(stageSource_t background);
        void setImage(const string &source);
};

#endif