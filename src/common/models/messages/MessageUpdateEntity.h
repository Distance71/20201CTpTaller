#ifndef MESSAGE_UPDATE_ENTITY_H_
#define MESSAGE_UPDATE_ENTITY_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../types.h"

using namespace std;

class MessageUpdateEntity : public Message {

    private:
    
        //level_t level_; 
        //stage_t stage_;
        unsigned int step_;
        IdElement idElement_;
        int pos_x_;
        int pos_y_;
    
    public:

        MessageUpdateEntity(unsigned int oneStep, IdElement idMapElement, int posX, int posY);
        ~MessageUpdateEntity();
        
        string getStringData();

        //level_t getLevel();
        //stage_t getStage();
        unsigned int getStep();
        IdElement getIdElement();
        int getPosX();
        int getPosY();

};

#endif // MESSAGE_UPDATE_ENTITY_H_