#include "EventUserMovement.h"
#include "../../../server/Server.h"

Message* EventUserMovement::serialize() {
    return (Message *) new MessageUserMovement(this->orientation_);
}

void EventUserMovement::update() {
    if (!this->context_)
		Logger::getInstance()->log(DEBUG, "No hay contexto para el evento EventUserMovement");
    else{
        Server* server = (Server*) Event::context_;
        server->moveUser(this->own_, this->orientation_);
        Logger::getInstance()->log(DEBUG, "se ejecutó el evento EventUserMovement");
    }
}