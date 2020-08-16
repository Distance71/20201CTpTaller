#include "MessageQuantityPlayers.h"

Event* MessageQuantityPlayers::deSerialize(){
    return (Event *) new EventQuantityPlayers(this->quantityPlayers_);
}

message_t MessageQuantityPlayers::getType(){
	return this->type_;
}

unsigned int MessageQuantityPlayers::getQuantityPlayers(){
	return this->quantityPlayers_;
}

responseStatus_t MessageQuantityPlayers::serialize(){
    return OK;
}