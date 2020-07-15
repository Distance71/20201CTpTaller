#ifndef _USERS_MANAGER_H_
#define _USERS_MANAGER_H_

#include <unordered_map>
#include "../../common/types.h"
#include "../../common/models/Socket.h"
#include "../../common/models/BlockingMap.h"
#include "../models/User.h"
#include "../../common/providers/GameProvider.h"
#include "../Server.h"

class Server;

class UsersManager {
    private:
        Server *serverOwn_;
        //unordered_map<Id, User *> users_;
        BlockingMap<User> *users_;
        size_t maxUsers_;
        Id lastId_ = 0;
        vector<Id> *idsLoggedUsers_;
        
        pthread_mutex_t mutex_lastId_;
        pthread_mutex_t mutex_loggedUser_;
        

    public:
        UsersManager(Server *serverOwn);
        ~UsersManager();

        unordered_map<Id, User *> getUsers();
        // void setIdUser(Id idUser);
        // Id getIdUser();
        bool isFullGame();
        Id acceptUnloggedUser();      
        bool loginUser(Id userId); 

        void setSocket(Socket *socket);
};

#endif // _USERS_MANAGER_H_