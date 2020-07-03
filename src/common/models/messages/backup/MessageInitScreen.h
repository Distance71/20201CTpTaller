#ifndef MESSAGE_INIT_SCREEN_H_
#define MESSAGE_INIT_SCREEN_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../../types.h"

using namespace std;

class MessageInitScreen : public Message {

    private:
        unsigned int screenWidth_;
        unsigned int screenHeight_;

    public:

        MessageInitScreen(unsigned int width, unsigned int height);
        ~MessageInitScreen();
        string getStringData();

        unsigned int getWidth();
        unsigned int getHeight();
};

#endif // MESSAGE_INIT_SCREEN_H_