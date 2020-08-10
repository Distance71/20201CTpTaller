#include "MessageScoreUpdate.h"

Event* MessageScoreUpdate::deSerialize(){
    return (Event *) new EventScoreUpdate(this->typePlayer_, this->lives_, this->health_, this->score_);
}

message_t MessageScoreUpdate::getType(){
	return this->type_;
}

elementType_t MessageScoreUpdate::getTypePlayer(){
    return this->typePlayer_;
}

unsigned int MessageScoreUpdate::getLives(){
    return this->lives_;
}

int MessageScoreUpdate::getHealth(){
    return this->health_;
}

int MessageScoreUpdate::getScore(){
    return this->score_;
}

responseStatus_t MessageScoreUpdate::serialize(){
    return OK;
}
