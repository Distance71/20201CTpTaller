#ifndef USER_H
#define USER_H

#include <string>
#include "../../common/models/Socket.h"
#include "../../common/types.h"
#include "../../common/models/messages/Message.h"
#include "../../common/models/events/Event.h"
#include "../../common/services/serializer/MessageDeserializer.h"
#include "../../common/services/serializer/MessageSerializer.h"
#include "../../common/models/BlockingQueue.h"
#include "../usersManager/UsersManager.h"
#include <errno.h>
#include <thread>

using namespace std;
class UsersManager;
class Message;

class User {

private:
    string userName_ = "";
    string password_ = "";
    bool connected_ = false;
    bool logged_ = false;
    Socket *socket_;
    BlockingQueue <Message*> * sendingQueue_;
    UsersManager* usersManager_;
    
public:

    //Constructor
    User(Socket *socket,UsersManager* usersManager);
    ~User();
    
    //general
    UsersManager* getUsersManager();

    //logueo
    string getUserName();
    string getPassword();
    void setCredentials(string userName, string password);
    void setLoggedIn();

    // connection
    bool isConnected();
    void setDisconnection();
    void setConnection();

    //tranismition
    void sendEvent(Event* event);
    Message* getMessage();
    void runSendingMessagesThread();
    void runReceivingMessagesThread();
    Socket* getSocket();

    
};

#endif 
