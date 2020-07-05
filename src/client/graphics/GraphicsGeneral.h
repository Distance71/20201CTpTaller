#ifndef _GRAPHICS_GENERAL_H_
#define _GRAPHICS_GENERAL_H_


#include <netinet/in.h>
#include <arpa/inet.h>
#include <unordered_map>
#include "GraphicsMapElement.h"
#include "GraphicsScenario.h"
#include "../../common/types.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../Client.h"
#include "../../common/providers/GameProvider.h"
class Client;
class GraphicsGeneral {
    private:
        unordered_map<IdElement, GraphicsMapElement*> elements_;
        GraphicsScenario *scenario_ = nullptr;
        Client* client;

    public:
        GraphicsGeneral(Client* _client);
        ~GraphicsGeneral();

        void update();
        
        void createEntity(IdElement id, const string &source, int sizeX, int sizeY, int posX, int posY, orientation_t orientation);
        void updateEntity(IdElement id, int posX, int posY, orientation_t orientation);
        void deadEntity(IdElement id);
        void setBackground(stageSource_t background);
        void run();
        Client* getClient();

};

#endif // _GRAPHICS_GENERAL_H_