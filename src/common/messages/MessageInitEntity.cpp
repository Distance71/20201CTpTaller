#include "MessageInitEntity.h"

MessageInitEntity::MessageInitEntity(level_t oneLevel, stage_t oneStage, IdElement idMapElement, 
                                    int sizeX, int sizeY, int posX, int posY, string oneSource) : Message(INIT_ENTITY)
{
    this->level_ = oneLevel;
    this->stage_ = oneStage;
    this->idElement_ = idMapElement;
    this->size_x_ = sizeX;
    this->size_y_ = sizeY;
    this->pos_x_ = posX;
    this->pos_y_ = posY;
    this->source_ = oneSource;
};

string MessageInitEntity::getStringData(){
    string dataString;
        
    return dataString;
};