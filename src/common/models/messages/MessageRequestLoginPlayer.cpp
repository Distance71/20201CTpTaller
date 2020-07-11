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

char* MessageRequestLoginPlayer::getUserName(){
    return this->userName_;
}

char* MessageRequestLoginPlayer::getPassword(){
    return this->password_;
}