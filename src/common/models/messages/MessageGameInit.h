#ifndef MESSAGE_INIT_SCREEN_H_
#define MESSAGE_INIT_SCREEN_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../../types.h"

using namespace std;

class MessageGameInit : public Message {

    private:
        unsigned int screenWidth_;
        unsigned int screenHeight_;

    public:

        MessageGameInit(unsigned int width, unsigned int height);
        ~MessageGameInit();
        string getStringData();

        unsigned int getWidth();
        unsigned int getHeight();
};

#endif // MESSAGE_INIT_SCREEN_H_