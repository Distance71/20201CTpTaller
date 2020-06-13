#ifndef MESSAGE_UPDATE_ENTITY_H_
#define MESSAGE_UPDATE_ENTITY_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../types.h"

using namespace std;

class MessageInitEntity : public Message {

    private:
        level_t level_; 
        stage_t stage_;
        IdElement idElement_; 
        int size_x_;
        int size_y_;
        int pos_x_;
        int pos_y_;
        string source_;
    
    public:

        MessageInitEntity(level_t oneLevel, stage_t oneStage, IdElement idMapElement, int sizeX, int sizeY, int posX, int posY, string oneSource);
        string getStringData();

};

#endif // MESSAGE_UPDATE_ENTITY_H_