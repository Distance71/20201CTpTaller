#include "MessageEndStage.h"

Event* MessageEndStage::deSerialize(){
    return (Event *) new EventEndStage(this->path_);
}

message_t MessageEndStage::getType(){
	return this->type_;
}