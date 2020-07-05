#include "EventResponseLoginPlayer.h"

Message* EventResponseLoginPlayer::serialize() {
    return (Message *) new MessageResponseLoginPlayer(this->response_);
}

void EventResponseLoginPlayer::update() {
    /*if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

    GameProvider::setWidth(this->width_);
    GameProvider::setHeight(this->height_);*/
}