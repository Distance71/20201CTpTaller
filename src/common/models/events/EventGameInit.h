#ifndef EVENT_GAME_INIT_H
#define EVENT_GAME_INIT_H

#include "Event.h"
#include "../messages/MessageGameInit.h"
#include "../messages/Message.h"
#include "../../providers/GameProvider.h"
#include "../../services/Logger.h"
#include "../../types.h"
#include "../../../client/Client.h"

using namespace std;

class EventGameInit: public Event {

	private:
        screen_t screenSizes_;

    public:
        EventGameInit(screen_t screenSizes): screenSizes_(screenSizes) {}
        
        Message* serialize();
        void update();
};

#endif