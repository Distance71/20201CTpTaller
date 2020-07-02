#ifndef MESSAGE_SERIALIZER_H_
#define MESSAGE_SERIALIZER_H_


#include "../../models/Socket.h"
#include "../../../server/models/User.h"
#include "../../models/events/Event.h"
#include "../../services/Logger.h"

using namespace std;

class MessageSerializer {

    public:
        MessageSerializer() = default;
        ~MessageSerializer() = default;
        
        void sendSerializedEvent(User *user, Event *event);
};

#endif