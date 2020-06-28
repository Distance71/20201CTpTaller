#ifndef MESSAGE_INIT_LAYER_H_
#define MESSAGE_INIT_LAYER_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../types.h"

using namespace std;

class MessageInitLayer : public Message {

    private:
        size_t id_; 
        string source_;
    
    public:

        MessageInitLayer(size_t idLayer, string oneSource);
        ~MessageInitLayer();
        string getStringData();

        size_t getIdLayer();
        string getSource();

};

#endif // MESSAGE_INIT_LAYER_H_