#include "MessageGameInit.h"

Event* MessageGameInit::deSerialize(){
    return (Event *) new EventGameInit(this->screenSizes_);
}

message_t MessageGameInit::getType(){
	return this->type_;
}