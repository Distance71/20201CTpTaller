#include "MessageMapElementDelete.h"

Event* MessageMapElementDelete::deSerialize(){
    return (Event *) new EventMapElementDelete(this->id_);
}