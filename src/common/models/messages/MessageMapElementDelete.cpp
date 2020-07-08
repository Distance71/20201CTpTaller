#include "MessageMapElementDelete.h"

Event* MessageMapElementDelete::deSerialize(){
    return (Event *) new EventMapElementDelete(this->id_);
}

message_t MessageMapElementDelete::getType(){
	return this->type_;
}