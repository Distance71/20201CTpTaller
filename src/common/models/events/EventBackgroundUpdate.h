#ifndef EVENT_BACKGROUND_UPDATE
#define EVENT_BACKGROUND_UPDATE

#include "Event.h"
#include "../messages/MessageBackgroundUpdate.h"
#include "../messages/Message.h"
#include "../../providers/GameProvider.h"
#include "../../services/Logger.h"
#include "../../../client/Client.h"

using namespace std;

class EventBackgroundUpdate: public Event {

	private:
        layer_t layer_;
        stage_t stage_;
        int step_;

    public:
        EventBackgroundUpdate(layer_t layer, stage_t stage, int step) : layer_(layer), step_(step), stage_(stage){}
        
        Message* serialize();
        int getStep();
        layer_t getLayer();
        stage_t getStage();
        void update();
};

#endif
