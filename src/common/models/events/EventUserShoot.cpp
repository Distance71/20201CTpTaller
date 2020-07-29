#include "EventUserShoot.h"
#include "../../../server/Server.h"

Message* EventUserShoot::serialize() {
    return (Message *) new MessageUserShoot();
}

void EventUserShoot::update() {
    if (!this->context_)
		Logger::getInstance()->log(DEBUG, "No hay contexto para el evento EventUserShoot");
    else{
        Server* server = (Server*) Event::context_;
        server->shootUser(this->nameOwn_);
        Logger::getInstance()->log(DEBUG, "se ejecutó el evento EventUserShoot");
    }
}