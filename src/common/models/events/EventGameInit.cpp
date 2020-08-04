#include "EventGameInit.h"
#include "../../../client/Client.h"

Message* EventGameInit::serialize() {
    return (Message *) new MessageGameInit(this->screenSizes_);
}

void EventGameInit::update() {
    if (!this->context_){
		  Logger::getInstance()->log(DEBUG, "No hay contexto para el evento EventGameInit");
    }
    else{
        Client* client = (Client*) Event::context_;
        //client->initGame(screenSizes_.width,screenSizes_.height);
        Logger::getInstance()->log(DEBUG, "Se ejecutó el evento EventGameInit");
    }
}