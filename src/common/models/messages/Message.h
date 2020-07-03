#ifndef MESSAGE_H_
#define MESSAGE_H_

using namespace std;

class Message {

    public:
        Message() = default;

        virtual Event* deSerialize();
};

#endif