#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <iostream>
#include <strings.h>
#include <stdbool.h>
#include <sys/types.h>
#include <atomic>
#include "../common/services/Logger.h"
#include "transmitionManager/ClientTransmitionManager.h"
#include "eventsManager/ClientEventsManager.h"
#include "screenManager/ScreenManager.h"
#include "../common/models/messages/Message.h"
#include "../common/models/events/Event.h"

class ClientTransmitionManager;
class ClientEventsManager;
class ScreenManager;

class Client {
    
    private:

        std::atomic<bool> connected_;
        string ipHost_;
        size_t port_;
        bool loggedIn_;

        ScreenManager *screenManager_;
        ClientTransmitionManager *transmitionManager_;
        ClientEventsManager* eventsManager_;
        bool serverDisconection_;
        bool endGame_;

    public:

        //general methods
        Client(string ipHost,size_t port);
        ~Client();
        int run();
        bool connectWithServer();
        bool isConnected();
        void disconnect();
        void reconnect();
        size_t getPort();
        string getIpHost();

        //Screen methods
        int waitForPlayers();
        void initGame(int Xsize, int Ysize);
        void endGame();
        void gameOver();
        void ServerDisconnection();
        
        //GraphicsGraphicsMe
        void setLoginResponse(responseStatus_t response);
        void setLoggedInStatus();
        bool isLoggedIn();
        
        //transmition methods
        void sendMessage(Message* message);

        //EventsMethods
        void processEvent(Event* event);
        void updateEntity(elementType_t type, position_t position);
        void updateBackgroundLayer(layer_t layer, stage_t stage, int step);
        void setImage(sceneScreen_t scene);
        void setScreenSizes(int Xsize, int Ysize);
        void runDetectEventThread();
        void updateMusic(musicType_t type);
    };

#endif