#ifndef MESSAGE_SERIALIZER_H_
#define MESSAGE_SERIALIZER_H_


#include "../../models/Socket.h"
#include "../../../server/models/User.h"
#include "../../models/events/Event.h"
#include "../../services/Logger.h"

using namespace std;

class MessageSerializer {
    private:
        response_t _handleErrorStatus();
        response_t _handleSuccess();

    public:
        MessageSerializer() = default;
        
        response_t sendSerializedEvent(User *user, Event *event);
};

#endif