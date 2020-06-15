#include "MessageUpdateEntity.h"

MessageUpdateEntity::MessageUpdateEntity(level_t oneLevel, stage_t oneStage, IdElement idMapElement, int posX, int posY) : Message(UPDATE_ENTITY)
{
    this->level_ = oneLevel;
    this->stage_ = oneStage;
    this->idElement_ = idMapElement;
    this->pos_x_ = posX;
    this->pos_y_ = posY;
    
};

MessageUpdateEntity::~MessageUpdateEntity(){

};

string MessageUpdateEntity::getStringData(){
    string dataString;

    dataString.push_back(this->type_);
    dataString.push_back(this->level_);
    dataString.push_back(this->stage_);

    char* idElement_arr = (char*)&this->idElement_;
    for (unsigned int i = 0; i < sizeof(IdElement); ++i)
        dataString.push_back(idElement_arr[i]);

    char* posX_arr = (char*)&this->pos_x_;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        dataString.push_back(posX_arr[i]);

    char* posY_arr = (char*)&this->pos_y_;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        dataString.push_back(posY_arr[i]);
        
    return dataString;
};

level_t MessageUpdateEntity::getLevel(){
    return this->level_;
};

stage_t MessageUpdateEntity::getStage(){
    return this->stage_;
};

IdElement MessageUpdateEntity::getIdElement(){
    return this->idElement_;
};

int MessageUpdateEntity::getPosX(){
    return this->pos_x_;
};

int MessageUpdateEntity::getPosY(){
    return this->pos_y_;
};