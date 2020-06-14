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