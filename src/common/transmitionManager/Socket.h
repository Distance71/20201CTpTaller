#ifndef SOCKET_H_
#define SOCKET_H_

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

using namespace std;

class Socket {
    private:
        unsigned int port_;
        int fileDescriptor;

    public:
        Socket();
        Socket(int fd);
        ~Socket();

        // For Server
        bool create();
        bool enlazar();
        bool escuchar(int maxConection);
        bool setOption();
        int acceptClient();

        // For Client
        bool connectWithServer(string ipHost);

        // Common
        void setPort(unsigned int port);
        int recibirMensaje(int *socketRecv, char* buffer, size_t sizeData);
        int enviarMensaje(const char* buffer, size_t sizeData);

        void cerrar();    
};

#endif //SOCKET_H_