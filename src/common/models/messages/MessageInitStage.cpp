#include "MessageInitStage.h"

Event* MessageInitStage::deSerialize(){
    return (Event *) new EventInitStage(this->layerPaths_);
}

message_t MessageInitStage::getType(){
	return this->type_;
}