#include "EventRequestLoginPlayer.h"

Message* EventRequestLoginPlayer::serialize() {
    return (Message *) new MessageRequestLoginPlayer(this->userName_, this->password_);
}

void EventRequestLoginPlayer::update() {
    /*if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

    GameProvider::setWidth(this->width_);
    GameProvider::setHeight(this->height_);*/
}