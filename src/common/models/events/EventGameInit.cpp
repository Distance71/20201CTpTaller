#include "EventGameInit.h"
#include "../../../client/Client.h"

Message* EventGameInit::serialize() {
    return (Message *) new MessageGameInit(this->screenSizes_);
}

void EventGameInit::update() {
    if (!this->context_)
		  Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");
    
    ((Client *)context_)->setScreenSizes(this->screenSizes_.width, this->screenSizes_.height);
}