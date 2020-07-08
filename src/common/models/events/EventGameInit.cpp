#include "EventGameInit.h"
#include "../../../client/Client.h"

Message* EventGameInit::serialize() {
    return (Message *) new MessageGameInit(this->screenSizes_);
}

void EventGameInit::update() {
    if (!this->context_)
		  Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");
    

    int Xsize = this->screenSizes_.width;
    int Ysize = this->screenSizes_.height;
    
    ((Client *)context_)->setScreenSizes(Xsize,Ysize);
}