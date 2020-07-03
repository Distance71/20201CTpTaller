#include "EventGameInit.h"

Message* EventGameInit::serialize() {
    return (Message *) new MessageGameInit();
}

void EventGameInit::update() {
    //Do stuff
}