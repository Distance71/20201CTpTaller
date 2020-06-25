#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "GameScreen.h"
#include "transmitionManager/ClientTransmitionManager.h"
#include "../common/models/Socket.h"
#include "../common/providers/GameProvider.h"
#include "../common/services/Logger.h"

using namespace std;

class GameScreen;
class ClientTransmitionManager;

class Client {
    private:
        GameScreen *gameScreen_;
        ClientTransmitionManager *transmitionManager_;

        //Socket *socket_;
        bool connected_;
        
        string name_;
        string ipHost_;
        size_t port_;

        void initializeClient();

    public:
        Client(string ipAddress, size_t port);
        ~Client();
        
        int run();
        bool isConnected();

        void disconnect();
        void setName(string oneName);
        string getName();

        void sendMovement(orientation_t moveOrientation);

        GameScreen *getGameScreen();
        ClientTransmitionManager *getTransmitionManager();
};

#endif