#include "MessageUserMovement.h"

Event* MessageUserMovement::deSerialize(){
    return (Event *) new EventUserMovement(this->orientation_);
}