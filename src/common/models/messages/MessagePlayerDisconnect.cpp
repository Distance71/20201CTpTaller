#include "MessagePlayerDisconnect.h"

Event* MessagePlayerDisconnect::deSerialize(){
    return (Event *) new EventPlayerDisconnect(this->id_);
}