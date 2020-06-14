#include "MessageInitLayer.h"

MessageInitLayer::MessageInitLayer(level_t oneLevel, stage_t oneStage, size_t idLayer, string oneSource) : Message(INIT_LAYER){
    this->level_ = oneLevel;
    this->stage_ = oneStage;
    this->id_ = idLayer;
    this->source_ = oneSource;
};

MessageInitLayer::~MessageInitLayer(){};

string MessageInitLayer::getStringData(){
    string dataString;
    
    dataString.push_back(this->type_);
    dataString.push_back(this->level_);
    dataString.push_back(this->stage_);
    dataString.push_back(this->id_);

    int len = this->source_.length();
    char* len_arr = (char*)&len;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        dataString.push_back(len_arr[i]);

    dataString.append(this->source_);
        
    return dataString;
};

level_t MessageInitLayer::getLevel(){
    return this->level_;
};

stage_t MessageInitLayer::getStage(){
    return this->stage_;
};

size_t MessageInitLayer::getIdLayer(){
    return this->id_;
};

string MessageInitLayer::getSource(){
    return this->source_;
};
