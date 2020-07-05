#include "MessageMapElementCreate.h"

Event* MessageMapElementCreate::deSerialize(){
    return (Event *) new EventMapElementCreate(this->id_, this->imagePath_, this->position_, this->spriteSize_);
}