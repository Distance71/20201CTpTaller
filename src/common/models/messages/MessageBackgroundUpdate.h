#ifndef MESSAGE_BACKGROUND_UPDATE
#define MESSAGE_BACKGROUND_UPDATE

#include "Message.h"
#include "../events/EventBackgroundUpdate.h"
#include "../events/Event.h"

class MessageBackgroundUpdate: public Message {

	private:
        layer_t layer_;
        stage_t stage_;
        int step_;
        const message_t type_ = BACKGROUND_UPDATE;

    public:
    	explicit MessageBackgroundUpdate(layer_t layer, stage_t stage, int step) :step_(step), layer_(layer), stage_(stage) {}
        message_t getType();
        Event* deSerialize();
        int getStep();
        layer_t getLayer();
        stage_t getStage();
        responseStatus_t serialize();
};

#endif
