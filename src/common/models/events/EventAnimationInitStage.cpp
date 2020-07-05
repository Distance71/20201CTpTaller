#include "EventAnimationInitStage.h"

Message* EventAnimationInitStage::serialize() {
    return (Message *) new MessageAnimationInitStage(this->path_);
}

void EventAnimationInitStage::update() {
    /*if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

    GameProvider::setWidth(this->width_);
    GameProvider::setHeight(this->height_);*/
}