#ifndef _CLIENTEVENTSMANAGER_H_
#define _CLIENTEVENTSMANAGER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../Client.h"
#include "../../common/types.h"
#include "../../common/models/events/Event.h"
#include "../../common/models/messages/MessageUserMovement.h"
#include <vector>

using namespace std;

class ClientEventsManager {
    private:
        vector <Event*> events_queue;
        Client *client;

    public:
    ClientEventsManager(Client* client);
    ~ClientEventsManager();
    void processEventsRun();
    void RunDetectPlayerEvents();
    void pushBackEvent(Event* event);
    Event* getEvent();
    Client* getClient();

};

#endif