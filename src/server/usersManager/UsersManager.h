#ifndef _USERS_MANAGER_H_
#define _USERS_MANAGER_H_

#include "../../common/types.h"
#include "../../common/models/Socket.h"
#include "../models/User.h"
#include "../../common/providers/GameProvider.h"
#include "../Server.h"

class Server;

class UsersManager {
    private:
        Server *serverOwn_;
        unordered_map<IdPlayer, User *> users_;

    public:
        UsersManager(Server *server);
        ~UsersManager();


        void setIdPlayer(IdPlayer idPlayer);
        IdPlayer getIdPlayer();

        void setSocket(Socket *socket);
};

#endif // _USERS_MANAGER_H_