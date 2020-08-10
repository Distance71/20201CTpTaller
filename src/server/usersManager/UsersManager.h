 
#ifndef _USERS_MANAGER_H_
#define _USERS_MANAGER_H_

#include <unordered_map>
#include "../../common/types.h"
#include "User.h"
#include "../../common/providers/GameProvider.h"
#include "../Server.h"
#include "../../common/models/BlockingQueue.h"

class Server;
class User;

class UsersManager {
    
    private:
        Server *serverOwn_;
        Id lastId_ ;
        unordered_map< Id, User *> notLoggedInUsers_;
        unordered_map< string, User *> loggedInUsers_;
        BlockingQueue <Message*> * sendingQueue_;
   
    public:
        UsersManager(Server *serverOwn);
        ~UsersManager();
        Server* getServer();
        bool isFullGame();
        void processEvent(Event* event);
        void sendEventToNotLoggedUser(Id id, Event* event);
        void sendEventToAllLogged(Event* event);
        void sendEventToOneUserLogged(string username, Event* event);
        responseStatus_t loginRequest(Id id,string username,string password);
        void runAcceptUsersThread();  
        void acceptUser();
        void runSendingThread();
        void informDisconnection(string user);
        void informConnection(string user);
        BlockingQueue <Message*> * getQueue();
        void sendToAll(Message* message);
        
};

#endif 