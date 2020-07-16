#ifndef _USERS_MANAGER_H_
#define _USERS_MANAGER_H_

#include <unordered_map>
#include "../../common/types.h"
#include "../../common/models/Socket.h"
//#include "../../common/models/BlockingMap.h"
#include "../models/User.h"
#include "../../common/providers/GameProvider.h"
#include "../Server.h"

class Server;
class User;

class UsersManager {
    private:
        Server *serverOwn_;
        Socket* socket_;
        size_t maxUsers_;
        Id lastId_ ;
        unordered_map<Id, User *> users_;
        int loggedUsers_;
        

    public:
        UsersManager(Server *serverOwn);
        ~UsersManager();
        Server* getServer();
        bool isFullGame();
        void sendEventToUser(Id id, Event* event);
        void sendToAll(Event* event);
        void runAcceptUsersThread();
        void acceptUser();
        void loginUser(Id userId);
        void disconnectUser(Id id);
        bool isConnectedUser(Id id);
        void setConnection(Id id);
        void processEvent(Event* event);
        
};


#endif 