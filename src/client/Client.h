#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <iostream>
#include <strings.h>
#include <stdbool.h>
#include <sys/types.h>
#include "../common/services/Logger.h"
#include "transmitionManager/ClientTransmitionManager.h"
#include "eventsManager/ClientEventsManager.h"
#include "screenManager/ScreenManager.h"
#include "../common/models/messages/Message.h"

class ClientTransmitionManager;
class ClientEventsManager;
class ScreenManager;

class Client {
    
    private:

        bool connected_;
        string ipHost_;
        size_t port_;

        ScreenManager *screenManager_;
        ClientTransmitionManager *transmitionManager_;
        ClientEventsManager* eventsManager_;

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
        void initGame();
        void createEntity(IdElement id, const string &source, int sizeX, int sizeY, int posX, int posY, orientation_t orientation);
        void updateEntity(IdElement id, int posX, int posY, orientation_t orientation);
        void deadEntity(IdElement id);
        void setBackground(stageSource_t background);
        void setImage(const string &source);
        void setScreenSizes(int Xsize, int Ysize);
        void endGame();
        
        //menu methods
        void setLoginResponse(responseStatus_t response);
        
        //transmition methods
        void sendMessage(Message* message);
};

#endif