#ifndef _USERS_MANAGER_H_
#define _USERS_MANAGER_H_

#include <unordered_map>
#include "../../common/types.h"
#include "User.h"
#include "../../common/providers/GameProvider.h"
#include "../Server.h"

class Server;
class User;

class UsersManager {
    
    private:
        Server *serverOwn_;
        Id lastId_ ;
        unordered_map< Id, User *> notLoggedInUsers_;
        unordered_map< string, User *> loggedInUsers_;
   
    public:
        UsersManager(Server *serverOwn);
        ~UsersManager();
        Server* getServer();
        bool isFullGame();
        void processEvent(Event* event);
        void sendEventToNotLoggedUser(Id id, Event* event);
        void sendEventToAllLogged(Event* event);
        responseStatus_t loginRequest(Id id,string username,string password);
        void runAcceptUsersThread();  
        void acceptUser();
};

#endif 