#ifndef _USERS_MANAGER_H_
#define _USERS_MANAGER_H_

#include <unordered_map>
#include "../../common/types.h"
#include "../../common/models/Socket.h"
#include "../models/User.h"
#include "../../common/providers/GameProvider.h"
#include "../Server.h"

class Server;

class UsersManager {
    private:
        Server *serverOwn_;
        unordered_map<IdUser, User *> users_;
        size_t maxUsers_;
        size_t loggedUsers_ = 0;
        IdUser lastId_ = 0;
        
        pthread_mutex_t mutex_lastId_;
        

    public:
        UsersManager(Server *serverOwn);
        ~UsersManager();

        unordered_map<IdUser, User *> getUsers();
        // void setIdUser(IdUser idUser);
        // IdUser getIdUser();
        bool isFullGame();
        IdUser acceptUnloggedUser();
        

        void setSocket(Socket *socket);
};

#endif // _USERS_MANAGER_H_