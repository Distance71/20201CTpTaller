#include "MessageGameInit.h"

Event* MessageGameInit::deSerialize(){
    return (Event *) new EventGameInit(this->screenSizes_);
}