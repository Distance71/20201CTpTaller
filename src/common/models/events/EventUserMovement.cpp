#include "EventUserMovement.h"

Message* EventUserMovement::serialize() {
    return (Message *) new MessageUserMovement(this->orientation_);
}

void EventUserMovement::update() {
    //Do stuff
}