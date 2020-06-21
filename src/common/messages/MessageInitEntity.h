#ifndef MESSAGE_INIT_ENTITY_H_
#define MESSAGE_INIT_ENTITY_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../types.h"

using namespace std;

class MessageInitEntity : public Message {

    private:
        level_t level_; 
        stage_t stage_;
        unsigned int step_;
        IdElement idElement_; 
        int size_x_;
        int size_y_;
        int pos_x_;
        int pos_y_;
        string source_;
        bool isPlayer_;
    
    public:

        MessageInitEntity(level_t oneLevel, stage_t oneStage, unsigned int oneStep, IdElement idMapElement, int sizeX, int sizeY, int posX, int posY, string oneSource, bool isHuman);
        ~MessageInitEntity();
        string getStringData();

        level_t getLevel();
        stage_t getStage();
        unsigned int getStep();
        IdElement getIdElement();
        int getSizeX();
        int getSizeY();
        int getPosX();
        int getPosY();
        string getSource();
        bool getIsPlayer();
};

#endif // MESSAGE_INIT_ENTITY_H_