#include "EventMapElementUpdate.h"

Message* EventMapElementUpdate::serialize() {
    return (Message *) new MessageMapElementUpdate(this->id_, this->position_);
}

void EventMapElementUpdate::update() {
    /*if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

    GameProvider::setWidth(this->width_);
    GameProvider::setHeight(this->height_);*/
}