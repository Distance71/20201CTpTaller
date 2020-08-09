#include "EventGameOver.h"

Message* EventGameOver::serialize() {
    return (Message *) new MessageGameOver();
}

void EventGameOver::update() {
    if (!this->context_){
		Logger::getInstance()->log(DEBUG, "No hay contexto para el evento EventGameOver");
    }
    else{
        Client* client =  (Client* ) context_;
        client->gameOver();
        Logger::getInstance()->log(DEBUG, "Se ejecutó el evento EventGameOver");
    }
}