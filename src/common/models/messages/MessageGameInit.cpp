#include "MessageGameInit.h"

Event* MessageGameInit::deSerialize(){
    return (Event *) new EventGameInit(this->width_, this->height_);
}