#ifndef _GAME_GRAPHICS_
#define _GAME_GRAPHICS_


#include <unordered_map>
#include <chrono>
#include <thread>
#include <unistd.h>
#include "GraphicsMapElement.h"
#include "GraphicsScenario.h"
#include "../../../common/types.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../../../common/providers/GameProvider.h"
#include "../../../common/services/Logger.h"
#include "../../../common/models/BlockingQueue.h"
#include "../../audio/Audio.h"
#include "GraphicsScoreBoard.h"

class GameGraphics {

    private:
        SDL_Renderer* renderer_;
        unordered_map <elementType_t, GraphicsMapElement*> elements_;
        unordered_map <sceneScreen_t, GraphicsMapElement*> scenes_;
        unordered_map <stage_t, GraphicsScenario*> scenaries_;
        GraphicsMapElement* image_;
        std::mutex mutex;
        BlockingQueue<elementToGraphic_t>* graphicsQueue_;
        GraphicsScoreBoard* scoreBoard_;
        

        void createScenes();
        void createElements();
        void createScenarios();
    public:

        GameGraphics(SDL_Renderer* renderer);
        ~GameGraphics();
        void updateEntity(elementType_t type, position_t position);
        void updateBackgroundLayer(layer_t layer, stage_t stage, int step);
        
        void setBackground(stage_t level);
        void setImage(sceneScreen_t scene);
        void setAudio(sceneScreen_t scene);

        void updateScore(elementType_t player,unsigned int lives,int health,int score);
};

#endif