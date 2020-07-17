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
        int loggedUsersCount_;
        unordered_map<Id, User *> users_;
        unordered_map<Id, User *> loggedUsers_;
    
    public:
        UsersManager(Server *serverOwn);
        ~UsersManager();
        Server* getServer();
        bool isFullGame();
        bool isLoggedIn(string username);
        bool wasPreviouslyLogged(string username);
        void processEvent(Event* event);
        void sendEventToNotLoggedUser(Id id, Event* event);
        void sendEventToAllLogged(Event* event);
        void setLoginResponse(Id id,bool response,string username);
        void acceptUser();
        void runAcceptUsersThread();  
};

#endif 