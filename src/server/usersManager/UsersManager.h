#ifndef _USERS_MANAGER_H_
#define _USERS_MANAGER_H_

#include "../../common/types.h"
#include "../../common/transmitionManager/Socket.h"

#include "../Server.h"

class Server;

class UsersManager {
    private:
        IdPlayer id_;
        Socket *socket_;
        Server *serverOwn_;

    public:
        UsersManager(IdPlayer idPlayer, Socket *socket, Server *server);
        ~UsersManager();

        void setIdPlayer(IdPlayer idPlayer);
        IdPlayer getIdPlayer();

        void setSocket(Socket *socket);
};

#endif // _USERS_MANAGER_H_