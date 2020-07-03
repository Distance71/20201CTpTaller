#ifndef MESSAGE_INIT_ENTITY_H_
#define MESSAGE_INIT_ENTITY_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../../types.h"

using namespace std;

class MessageInitEntity : public Message {

    private:
    
        IdElement idElement_; 
        int size_x_;
        int size_y_;
        string source_;
    
    public:

        MessageInitEntity(IdElement idMapElement, int sizeX, int sizeY, string oneSource);
        ~MessageInitEntity();
        string getStringData();

        IdElement getIdElement();
        int getSizeX();
        int getSizeY();
        string getSource();

        //level_t getLevel();
        //stage_t getStage();
        //unsigned int getStep();
        //int getPosX();
        //int getPosY();
        //bool getIsPlayer();
};

#endif // MESSAGE_INIT_ENTITY_H_