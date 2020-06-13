#include "MessageUpdateStage.h"

MessageUpdateStage::MessageUpdateStage(level_t oneLevel, stage_t oneStage, bool started) : Message(UPDATE_STAGE){
    this->level_ = oneLevel;
    this->stage_ = oneStage;
    this->isStart_ = started;
};

string MessageUpdateStage::getStringData(){
    string dataString;

    return dataString;
};

