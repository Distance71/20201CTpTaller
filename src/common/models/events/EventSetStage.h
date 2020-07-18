#ifndef EVENT_SET_STAGE
#define EVENT_SET_STAGE

#include "Event.h"
#include "../messages/MessageSetStage.h"
#include "../messages/Message.h"
#include "../../providers/GameProvider.h"
#include "../../services/Logger.h"
#include "../../../client/Client.h"

using namespace std;

class EventSetStage: public Event {

	private:
        stage_t stage_;

    public:
        EventSetStage(stage_t stage) : stage_(stage){}
        
        Message* serialize();
        stage_t getStage();
        void update();
};

#endif
