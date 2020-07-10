#include "EventResponseLoginPlayer.h"

Message* EventResponseLoginPlayer::serialize() {
    return (Message *) new MessageResponseLoginPlayer(this->response_);
}

void EventResponseLoginPlayer::update() {
    if (!this->context_){
		Logger::getInstance()->log(DEBUG, "No hay contexto para el evento EventResponseLoginPlayer");
    }
    else{
        Client* client = (Client *) context_;
        client ->setLoginResponse(this->response_);
        Logger::getInstance()->log(DEBUG, "Se ejecutó el evento EventResponseLoginPlayer");
    }

}