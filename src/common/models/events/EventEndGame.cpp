#include "EventEndGame.h"

Message* EventEndGame::serialize() {
    return (Message *) new MessageEndGame();
}

void EventEndGame::update() {
    /*if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

    GameProvider::setWidth(this->width_);
    GameProvider::setHeight(this->height_);*/
}