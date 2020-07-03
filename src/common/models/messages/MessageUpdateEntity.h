#ifndef MESSAGE_UPDATE_ENTITY_H_
#define MESSAGE_UPDATE_ENTITY_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../../types.h"

using namespace std;

class MessageUpdateEntity : public Message {

    private:
    
        IdElement idElement_;
        int pos_x_;
        int pos_y_;
    
    public:

        MessageUpdateEntity(IdElement idMapElement, int posX, int posY);
        ~MessageUpdateEntity();        
        string getStringData();

        IdElement getIdElement();
        int getPosX();
        int getPosY();

        //level_t getLevel();
        //stage_t getStage();
        //unsigned int getStep();

};

#endif // MESSAGE_UPDATE_ENTITY_H_