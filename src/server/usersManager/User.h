 
#ifndef USER_H
#define USER_H

#include <string>
#include "../../common/types.h"
#include "../../common/models/messages/Message.h"
#include "../../common/models/events/Event.h"
#include "../../common/services/serializer/MessageDeserializer.h"
#include "../../common/services/serializer/MessageSerializer.h"
#include "../../common/models/Socket.h"
#include "../../common/models/BlockingQueue.h"
#include "UsersManager.h"
#include "UsersManager.h"
#include <thread>

using namespace std;

class UsersManager;
class Message;

class User {

private:

    Id id_;
    string username_;

    UsersManager* usersManager_;
    Socket* socket_;
    
    bool connected_;
    BlockingQueue <Message*> * sendingQueue_;

    bool logged_;
    bool previouslyLogged_;
      
public:

    User(UsersManager* usersManager,Socket* socket);
    ~User();
    
    void setId(Id id);
    Id getId();
    void setUserName(string username);
    string getUserName();

    void setConnection();
    void setDisconnection();
    bool isConnected();

    Socket* getSocket();
    UsersManager* getUsersManager();

    
    void sendEvent(Event* event);
    void sendMessage(Message* message);
    
    void runSendingMessagesThread();
    void runReceivingMessagesThread();
 
};

#endif 