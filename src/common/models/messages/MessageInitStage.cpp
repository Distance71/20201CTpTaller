#include "MessageInitStage.h"

Event* MessageInitStage::deSerialize(){
    return (Event *) new EventInitStage(this->layerPaths_);
}