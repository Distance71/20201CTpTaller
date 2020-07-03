#include "MessageInitLayer.h"

MessageInitLayer::MessageInitLayer(size_t idLayer, string oneSource) : Message(INIT_LAYER){
    this->id_ = idLayer;
    this->source_ = oneSource;
};

MessageInitLayer::~MessageInitLayer(){};

string MessageInitLayer::getStringData(){
    string dataString;
    
    dataString.push_back(this->type_);
    
    char* id_arr = (char*)&this->id_;
    for (unsigned int i = 0; i < sizeof(size_t); ++i)
        dataString.push_back(id_arr[i]);

    int len = this->source_.length();
    char* len_arr = (char*)&len;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        dataString.push_back(len_arr[i]);

    dataString.append(this->source_);
        
    return dataString;
};

size_t MessageInitLayer::getIdLayer(){
    return this->id_;
};

string MessageInitLayer::getSource(){
    return this->source_;
};
