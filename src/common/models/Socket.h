#ifndef SOCKET_H_
#define SOCKET_H_

#include <iostream>
#include <sstream>
#include <iomanip>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "../services/Logger.h"

using namespace std;

class Socket {
    private:
        unsigned int port_;
        int fileDescriptor_;

    public:
        Socket();
        Socket(int fd);
        ~Socket();

        // For Server
        bool create();
        bool link();
        bool listenConnections(int maxConnections);
        bool setOption();
        int acceptClient();

        // For Client
        bool connectWithServer(string ipHost);

        // Common
        void setPort(unsigned int port);
        int receiveMessage(void* buffer, size_t sizeData);
        int sendMessage(void* buffer, size_t sizeData);

        void cerrar();    
};

#endif //SOCKET_H_