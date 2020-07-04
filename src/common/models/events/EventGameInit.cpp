#include "EventGameInit.h"

Message* EventGameInit::serialize() {
    return (Message *) new MessageGameInit(this->width_, this->height_);
}

void EventGameInit::update() {
    /*if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

    GameProvider::setWidth(this->width_);
    GameProvider::setHeight(this->height_);*/
}