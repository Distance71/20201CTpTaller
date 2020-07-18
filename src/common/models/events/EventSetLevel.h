#ifndef EVENT_SET_LEVEL
#define EVENT_SET_LEVEL

#include "Event.h"
#include "../messages/MessageSetLevel.h"
#include "../messages/Message.h"
#include "../../providers/GameProvider.h"
#include "../../services/Logger.h"
#include "../../../client/Client.h"

using namespace std;

class EventSetLevel: public Event {

	private:
        level_t level_;

    public:
        EventSetLevel(level_t level) : level_(level){}
        
        Message* serialize();
        level_t getLevel();
        void update();
};

#endif