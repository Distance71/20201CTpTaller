#include "MessageMusicUpdate.h"

Event* MessageMusicUpdate::deSerialize(){
    return (Event *) new EventMusicUpdate(this->elementType_);
}

message_t MessageMusicUpdate::getType(){
	return this->type_;
}

soundType_t MessageMusicUpdate::getMusicType(){
    return this->elementType_;
}

responseStatus_t MessageMusicUpdate::serialize(){
    return OK;
}