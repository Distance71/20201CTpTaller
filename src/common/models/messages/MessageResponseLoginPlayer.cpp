#include "MessageResponseLoginPlayer.h"

Event* MessageResponseLoginPlayer::deSerialize(){
    return (Event *) new EventResponseLoginPlayer(this->response_);
}

message_t MessageResponseLoginPlayer::getType(){
	return this->type_;
}

responseStatus_t MessageResponseLoginPlayer::serialize(){
    return OK;
}