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
#include "../../../common/models/BlockingMapGraphicsMapElement.h"

class GameGraphics {
    
    private:
        SDL_Renderer* renderer_;
        unordered_map<Id, GraphicsMapElement*> elements_;
        GraphicsScenario * scenario_;
        GraphicsMapElement* image_;
        std::mutex mutex_update;
        
        
    public:
        
        GameGraphics(SDL_Renderer* renderer);
        ~GameGraphics();
        void update();
        void createEntity(Id id, const string &source, int sizeX, int sizeY, int posX, int posY, orientation_t orientation);
        void updateEntity(Id id, int posX, int posY, orientation_t orientation);
        void deadEntity(Id id);
        void setBackground(stageSource_t background);
        void setImage(const string &source);
};

#endif