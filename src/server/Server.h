#ifndef _SERVER_H_
#define _SERVER_H_

#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>
#include "usersManager/UsersManager.h"
#include "../common/models/Socket.h"
#include "../common/services/Logger.h"
#include "../common/providers/GameProvider.h"
#include "eventsManager/ServerEventsManager.h"
#include "models/Game.h"

class ServerEventsManager;
class UsersManager;
class Game;

class Server {
    
    private:
        Socket *socket_;
        UsersManager* usersManager_;
        ServerEventsManager* eventsManager_;
        bool connected_;
        Game* game_;
                
        void _initializeServer(size_t port);
        
    public:  
        Server(size_t port);
        ~Server();
        bool isConnected();
        Socket* getSocket();
        void processEvent(Event *event);
        void sendToAllUsers(Event* event);
        void sendToUser(Id id,Event* event);
        void moveUser(Id idUser, orientation_t orientation);
        void runGame();
        responseStatus_t loginRequest(Id id, string username,string password);
        int run();
        
        void informDisconnection(string user);   
        void informConnection(string user);   
};

#endif