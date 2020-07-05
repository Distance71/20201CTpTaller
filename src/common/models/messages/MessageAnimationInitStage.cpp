#include "MessageAnimationInitStage.h"

Event* MessageAnimationInitStage::deSerialize(){
    return (Event *) new EventAnimationInitStage(this->path_);
}