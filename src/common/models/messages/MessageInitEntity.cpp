#include "MessageInitEntity.h"

MessageInitEntity::MessageInitEntity(IdElement idMapElement, int sizeX, int sizeY, string oneSource) : Message(INIT_ENTITY)
{

    this->idElement_ = idMapElement;
    this->size_x_ = sizeX;
    this->size_y_ = sizeY;
    this->source_ = oneSource;
};

MessageInitEntity::~MessageInitEntity(){};

string MessageInitEntity::getStringData(){
    string dataString;

    dataString.push_back(this->type_);

    char* idElement_arr = (char*)&this->idElement_;
    for (unsigned int i = 0; i < sizeof(IdElement); ++i)
        dataString.push_back(idElement_arr[i]);

    char* sizeX_arr = (char*)&this->size_x_;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        dataString.push_back(sizeX_arr[i]);

    char* sizeY_arr = (char*)&this->size_y_;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        dataString.push_back(sizeY_arr[i]);

    int len = this->source_.length();
    char* len_arr = (char*)&len;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        dataString.push_back(len_arr[i]);

    dataString.append(this->source_);
    
    return dataString;
};

IdElement MessageInitEntity::getIdElement(){
    return this->idElement_;
};

int MessageInitEntity::getSizeX(){
    return this->size_x_;
};

int MessageInitEntity::getSizeY(){
    return this->size_y_;
};

string MessageInitEntity::getSource(){
    return this->source_;
};

/*
level_t MessageInitEntity::getLevel(){
    return this->level_;
};

stage_t MessageInitEntity::getStage(){
    return this->stage_;
};

unsigned int MessageInitEntity::getStep(){
    return this->step_;
}

int MessageInitEntity::getPosX(){
    return this->pos_x_;
};

int MessageInitEntity::getPosY(){
    return this->pos_y_;
};

bool MessageInitEntity::getIsPlayer(){
    return this->isPlayer_;
}
*/