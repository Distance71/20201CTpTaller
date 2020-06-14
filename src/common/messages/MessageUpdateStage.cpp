#include "MessageUpdateStage.h"

MessageUpdateStage::MessageUpdateStage(level_t oneLevel, stage_t oneStage, string oneSource) : Message(UPDATE_STAGE){
    this->level_ = oneLevel;
    this->stage_ = oneStage;
    this->source_ = oneSource;
};

MessageUpdateStage::~MessageUpdateStage(){};

string MessageUpdateStage::getStringData(){
    string dataString;

    dataString.push_back(this->type_);
    dataString.push_back(this->level_);
    dataString.push_back(this->stage_);

    int len = this->source_.length();
    char* len_arr = (char*)&len;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        dataString.push_back(len_arr[i]);

    dataString.append(this->source_);
    
    return dataString;
};

level_t MessageUpdateStage::getLevel(){
    return this->level_;
};

stage_t MessageUpdateStage::getStage(){
    return this->stage_;
};

string MessageUpdateStage::getSource(){
    return this->source_;
};
