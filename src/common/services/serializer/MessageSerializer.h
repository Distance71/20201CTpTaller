#ifndef MESSAGE_SERIALIZER_H_
#define MESSAGE_SERIALIZER_H_


#include "../../models/Socket.h"
#include "../../models/events/Event.h"
#include "../../services/Logger.h"

using namespace std;

class MessageSerializer {
    private:
        response_t _handleErrorStatus();
        response_t _handleSuccess();

    public:
        response_t sendSerializedEvent(Socket *socket, Event *event);
};

#endif