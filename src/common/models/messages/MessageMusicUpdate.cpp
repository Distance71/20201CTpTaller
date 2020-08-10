#include "MessageMusicUpdate.h"

Event* MessageMusicUpdate::deSerialize(){
    return (Event *) new EventMusicUpdate(this->musicType_);
}

message_t MessageMusicUpdate::getType(){
	return this->type_;
}

musicType_t MessageMusicUpdate::getMusicType(){
    return this->musicType_;
}

responseStatus_t MessageMusicUpdate::serialize(){
    return OK;
}