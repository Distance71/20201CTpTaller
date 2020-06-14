#ifndef MESSAGE_INIT_SCREEN_H_
#define MESSAGE_INIT_SCREEN_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../types.h"

using namespace std;

class MessageInitScreen : public Message {

    private:
        size_t screenWidth_;
        size_t screenHeight_;

    public:

        MessageInitScreen(size_t width, size_t height);
        ~MessageInitScreen();
        string getStringData();

        size_t getWidth();
        size_t getHeight();
};

#endif // MESSAGE_INIT_SCREEN_H_