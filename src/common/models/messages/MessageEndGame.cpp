#include "MessageEndGame.h"

Event* MessageEndGame::deSerialize(){
    return (Event *) new EventEndGame();
}

message_t MessageEndGame::getType(){
	return this->type_;
}

responseStatus_t MessageEndGame::serialize(){
    return OK;
}