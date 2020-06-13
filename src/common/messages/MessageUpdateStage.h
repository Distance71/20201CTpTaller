#ifndef MESSAGE_UPDATE_STAGE_H_
#define MESSAGE_UPDATE_STAGE_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../types.h"

using namespace std;

class MessageUpdateStage : public Message {

    private:
        level_t level_; 
        stage_t stage_;
        bool isStart_;
    
    public:

        MessageUpdateStage(level_t oneLevel, stage_t oneStage, bool started);
        string getStringData();

};

#endif // MESSAGE_UPDATE_STAGE_H_