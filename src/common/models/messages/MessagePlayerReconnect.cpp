#include "MessagePlayerReconnect.h"

Event* MessagePlayerReconnect::deSerialize(){
    return (Event *) new EventPlayerReconnect(this->id_);
}