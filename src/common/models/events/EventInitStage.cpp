#include "EventInitStage.h"

Message* EventInitStage::serialize() {
    return (Message *) new MessageInitStage(this->layerPaths_);
}

void EventInitStage::update() {
    /*if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

    GameProvider::setWidth(this->width_);
    GameProvider::setHeight(this->height_);*/
}