#ifndef MESSAGE_INIT_LAYER_H_
#define MESSAGE_INIT_LAYER_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../types.h"

using namespace std;

class MessageInitLayer : public Message {

    private:
        level_t level_; 
        stage_t stage_;
        size_t id_; 
        string source_;
    
    public:

        MessageInitLayer(level_t oneLevel, stage_t oneStage, size_t idLayer, string oneSource);
        ~MessageInitLayer();
        string getStringData();

};

#endif // MESSAGE_INIT_LAYER_H_