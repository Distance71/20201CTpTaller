#include "MessageUpdateStage.h"

MessageUpdateStage::MessageUpdateStage(level_t oneLevel, bool isStartStage, bool isEndStage) : Message(UPDATE_STAGE){
    this->level_ = oneLevel;
    this->isStartStage_ = isStartStage;
    this->isEndStage_ = isEndStage;
};

MessageUpdateStage::~MessageUpdateStage(){};

string MessageUpdateStage::getStringData(){
    string dataString;

    dataString.push_back(this->type_);
    dataString.push_back(this->level_);
    
    if (this->isStartStage_){
        dataString.push_back(IS_TRUE);
    } else {
        dataString.push_back(IS_FALSE);
    }

    if (this->isEndStage_){
        dataString.push_back(IS_TRUE);
    } else {
        dataString.push_back(IS_FALSE);
    }
    
    return dataString;
};

level_t MessageUpdateStage::getLevel(){
    return this->level_;
};

bool MessageUpdateStage::getIsStartStage(){
    return this->isStartStage_;
};

bool MessageUpdateStage::getIsEndStage(){
    return this->isEndStage_;
};
