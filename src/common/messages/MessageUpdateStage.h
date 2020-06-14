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
        string source_;
    
    public:

        MessageUpdateStage(level_t oneLevel, stage_t oneStage, string oneSource);
        ~MessageUpdateStage();
        string getStringData();

        level_t getLevel();
        stage_t getStage();
        string getSource();
};

#endif // MESSAGE_UPDATE_STAGE_H_