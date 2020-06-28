#ifndef MESSAGE_UPDATE_STAGE_H_
#define MESSAGE_UPDATE_STAGE_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../../types.h"

using namespace std;

class MessageUpdateStage : public Message {

    private:
        level_t level_; 
        bool isStartStage_;
        bool isEndStage_;
    
    public:

        MessageUpdateStage(level_t oneLevel, bool isStartStage, bool isEndStage);
        ~MessageUpdateStage();
        string getStringData();

        level_t getLevel();
        bool getIsStartStage();
        bool getIsEndStage();
};

#endif // MESSAGE_UPDATE_STAGE_H_