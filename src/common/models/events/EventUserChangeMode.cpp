#include "EventUserChangeMode.h"
#include "../../../server/Server.h"

Message* EventUserChangeMode::serialize() {
    return (Message *) new MessageUserChangeMode();
}

void EventUserChangeMode::update() {
    if (!this->context_)
		Logger::getInstance()->log(DEBUG, "No hay contexto para el evento EventUserChangeMode");
    else{
        Server* server = (Server*) Event::context_;
        server->changeUserGameMode(this->nameOwn_);
        Logger::getInstance()->log(DEBUG, "se ejecutó el evento EventUserChangeMode");
    }
}