#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "GameScreen.h"
#include "loginMenu/Menu.h"
#include "transmitionManager/ClientTransmitionManager.h"
#include "eventsManager/ClientEventsManager.h"
#include "../common/models/Socket.h"
#include "../common/providers/GameProvider.h"
#include "../common/services/Logger.h"
#include "../common/models/messages/Message.h"
#include "../common/models/messages/MessageLog.h"


class GameScreen;
class ClientEventsManager;
class ClientTransmitionManager;

class Client {
    protected:
        
        GameScreen *gameScreen_;
        ClientTransmitionManager *transmitionManager_;
        ClientEventsManager* eventsManager_;

        string name_;
        string ipHost_;
        size_t port_;
        bool connected_;

        void initializeClient();

    public:
        Client(string ipAddress, size_t port);
        ~Client();
        
        int run();
        bool isConnected();
        void disconnect();
        void setName(string oneName);
        string getName();
        void initGraphics(screen_t screenSizes);

        void sendMessage(Message* message);

        GameScreen *getGameScreen();
        ClientTransmitionManager *getTransmitionManager();
        ClientEventsManager* getEventsManager();
};

#endif