#include "MessageMapElementUpdate.h"

Event* MessageMapElementUpdate::deSerialize(){
    return (Event *) new EventMapElementUpdate(this->id_, this->position_);
}