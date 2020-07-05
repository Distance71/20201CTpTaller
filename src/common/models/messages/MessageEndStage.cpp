#include "MessageEndStage.h"

Event* MessageEndStage::deSerialize(){
    return (Event *) new EventEndStage(this->path_);
}