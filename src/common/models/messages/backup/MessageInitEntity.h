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
        int pos_x_;
        int pos_y_;
        orientation_t orientation_;
        string source_;
    
    public:

        MessageInitEntity(IdElement idMapElement, int sizeX, int sizeY, int posX, int posY, orientation_t orientation, string oneSource);
        ~MessageInitEntity();
        string getStringData();

        IdElement getIdElement();
        int getSizeX();
        int getSizeY();
        int getPosX();
        int getPosY();
        orientation_t getOrientation();
        string getSource();

        //level_t getLevel();
        //stage_t getStage();
        //unsigned int getStep();
        //bool getIsPlayer();
};

#endif // MESSAGE_INIT_ENTITY_H_