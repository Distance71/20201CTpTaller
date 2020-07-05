#include "EventPlayerDisconnect.h"

Message* EventPlayerDisconnect::serialize() {
    return (Message *) new MessagePlayerDisconnect(this->id_);
}

void EventPlayerDisconnect::update() {
    /*if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

    GameProvider::setWidth(this->width_);
    GameProvider::setHeight(this->height_);*/
}