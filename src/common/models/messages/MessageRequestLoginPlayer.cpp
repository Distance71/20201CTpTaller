#include "MessageRequestLoginPlayer.h"

Event* MessageRequestLoginPlayer::deSerialize(){
    return (Event *) new EventRequestLoginPlayer(this->userName_, this->password_);
}

message_t MessageRequestLoginPlayer::getType(){
	return this->type_;
}

responseStatus_t MessageRequestLoginPlayer::serialize(){
    return OK;
}