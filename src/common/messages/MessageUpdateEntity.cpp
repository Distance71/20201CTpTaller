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