#include "EventEndGame.h"

Message* EventEndGame::serialize() {
    return (Message *) new MessageEndGame();
}

void EventEndGame::update() {
    if (!this->context_){
		Logger::getInstance()->log(DEBUG, "No hay contexto para el evento EventEndGame");
    }
    else{
        Client* client =  (Client* ) context_;
        client->endGame();
        Logger::getInstance()->log(DEBUG, "Se ejecutó el evento EventEndGame");
    }
}