#include "MessageInitStage.h"

Event* MessageInitStage::deSerialize(){
    return (Event *) new EventInitStage(this->layerPaths_);
}

message_t MessageInitStage::getType(){
	return this->type_;
}

responseStatus_t MessageInitStage::serialize(){
    return OK;
}

void* MessageInitStage::getLayers(){
    return &this->layerPaths_;
}