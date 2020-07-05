#include "EventPlayerReconnect.h"

Message* EventPlayerReconnect::serialize() {
    return (Message *) new MessagePlayerReconnect(this->id_);
}

void EventPlayerReconnect::update() {
    /*if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

    GameProvider::setWidth(this->width_);
    GameProvider::setHeight(this->height_);*/
}