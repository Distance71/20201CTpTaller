#ifndef _SERVER_TRANSMITION_MANAGER_H_
#define _SERVER_TRANSMITION_MANAGER_H_

#include <unordered_map>
#include "../../common/transmitionManager/Socket.h"
#include "../../common/types.h"
#include "../../common/messages/Message.h"
#include "../../common/messages/MessageActionPlayer.h"
#include "../../common/messages/MessageInitEntity.h"
#include "../../common/messages/MessageInitLayer.h"
#include "../../common/messages/MessageInitScreen.h"
#include "../../common/messages/MessageMovementPlayer.h"
#include "../../common/messages/MessageUpdateEntity.h"
#include "../../common/messages/MessageUpdateStage.h"

#include "../Server.h"
#include "../usersManager/UsersManager.h"

class Server;
class UsersManager;

class ServerTransmitionManager {
    private:
        Server *serverOwn_;
        Socket *socket_;
        size_t maxPlayers;
        
        unordered_map<IdPlayer, UsersManager*> users_;
        IdPlayer lastId_ = 0;
        pthread_mutex_t mutex_lastId_;

    public:
        ServerTransmitionManager(Server *server, size_t port);
        ~ServerTransmitionManager();

        bool initialize();
        bool waitPlayers();
};

#endif