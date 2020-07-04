#include "MessageInitEntity.h"

MessageInitEntity::MessageInitEntity(IdElement idMapElement, int sizeX, int sizeY, int posX, 
                                    int posY, orientation_t orientation, string oneSource) : Message(INIT_ENTITY)
{

    this->idElement_ = idMapElement;
    this->size_x_ = sizeX;
    this->size_y_ = sizeY;
    this->pos_x_ = posX;
    this->pos_y_ = posY;
    this->orientation_ = orientation;
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

    char* posX_arr = (char*)&this->pos_x_;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        dataString.push_back(posX_arr[i]);

    char* posY_arr = (char*)&this->pos_y_;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        dataString.push_back(posY_arr[i]);
        
    char* orientation_arr = (char*)&this->orientation_;
    for (unsigned int i = 0; i < sizeof(orientation_t); ++i)
        dataString.push_back(orientation_arr[i]);
        
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

int MessageInitEntity::getPosX(){
    return this->pos_x_;
};

int MessageInitEntity::getPosY(){
    return this->pos_y_;
};

orientation_t MessageInitEntity::getOrientation(){
    return this->orientation_;
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

bool MessageInitEntity::getIsPlayer(){
    return this->isPlayer_;
}
*/