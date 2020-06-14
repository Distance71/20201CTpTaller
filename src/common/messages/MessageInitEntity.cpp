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

MessageInitEntity::~MessageInitEntity(){};

string MessageInitEntity::getStringData(){
    string dataString;
        
    return dataString;
};

level_t MessageInitEntity::getLevel(){
    return this->level_;
};

stage_t MessageInitEntity::getStage(){
    return this->stage_;
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

string MessageInitEntity::getSource(){
    return this->source_;
};