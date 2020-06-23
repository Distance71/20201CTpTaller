#include "MessageInitEntity.h"

MessageInitEntity::MessageInitEntity(unsigned int oneStep, IdElement idMapElement, 
                                    int sizeX, int sizeY, int posX, int posY, string oneSource, bool isHuman) : Message(INIT_ENTITY)
{

    this->step_ = oneStep;
    this->idElement_ = idMapElement;
    this->size_x_ = sizeX;
    this->size_y_ = sizeY;
    this->pos_x_ = posX;
    this->pos_y_ = posY;
    this->source_ = oneSource;
    this->isPlayer_ = isHuman;
};

MessageInitEntity::~MessageInitEntity(){};

string MessageInitEntity::getStringData(){
    string dataString;

    dataString.push_back(this->type_);
    
    char* sizeStep_arr = (char*)&this->step_;
    for (unsigned int i = 0; i < sizeof(unsigned int); ++i)
        dataString.push_back(sizeStep_arr[i]);

    char* idElement_arr = (char*)&this->idElement_;
    for (unsigned int i = 0; i < sizeof(IdElement); ++i)
        dataString.push_back(idElement_arr[i]);

    char* sizeX_arr = (char*)&this->size_x_;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        dataString.push_back(sizeX_arr[i]);

    char* sizeY_arr = (char*)&this->size_y_;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        dataString.push_back(sizeY_arr[i]);

    char* posX_arr = (char*)&this->pos_x_;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        dataString.push_back(posX_arr[i]);

    char* posY_arr = (char*)&this->pos_y_;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        dataString.push_back(posY_arr[i]);

    int len = this->source_.length();
    char* len_arr = (char*)&len;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        dataString.push_back(len_arr[i]);

    dataString.append(this->source_);

    if (this->isPlayer_){
        dataString.push_back(IS_TRUE);
    } else {
        dataString.push_back(IS_FALSE);
    }
    
    return dataString;
};

/*
level_t MessageInitEntity::getLevel(){
    return this->level_;
};

stage_t MessageInitEntity::getStage(){
    return this->stage_;
};*/

unsigned int MessageInitEntity::getStep(){
    return this->step_;
}

IdElement MessageInitEntity::getIdElement(){
    return this->idElement_;
};

int MessageInitEntity::getSizeX(){
    return this->size_x_;
};

int MessageInitEntity::getSizeY(){
    return this->size_y_;
};

int MessageInitEntity::getPosX(){
    return this->pos_x_;
};

int MessageInitEntity::getPosY(){
    return this->pos_y_;
};

string MessageInitEntity::getSource(){
    return this->source_;
};

bool MessageInitEntity::getIsPlayer(){
    return this->isPlayer_;
}