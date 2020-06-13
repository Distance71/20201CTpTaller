#include "Socket.h"

Socket::Socket(unsigned int port){
    this->port_ = port;
}

Socket::~Socket(){}

bool Socket::create(){
    
    this->fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (this->fileDescriptor < 0)
        return false;

    return true;
}

bool Socket::setOption(){
    int enable = 1;
    int optsSetted = setsockopt(this->fileDescriptor, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

    if (optsSetted < 0)
        return false;

    return true;
}

bool Socket::enlazar(){

    struct sockaddr_in socket_addr; 

    socket_addr.sin_family = AF_INET;
    socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_addr.sin_port = htons(this->port_);

    if (bind(this->fileDescriptor, (struct sockaddr *) &socket_addr, sizeof(socket_addr)) < 0)
        return false; 
    
    return true;
}

bool Socket::escuchar(int maxConection){

    if (listen(this->fileDescriptor, maxConection) < 0)
        return false;

    return true; 
}

bool Socket::connectWithServer(string ipHost){

    struct sockaddr_in server; 

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ipHost.c_str());
    server.sin_port = htons(this->port_);

    if (connect(this->fileDescriptor, (struct sockaddr *) &server, sizeof(server)))
        return false;
    
    return true;
}

int Socket::acceptClient(){
    struct sockaddr_in sockaddr_client;
    int clientAddrLen;

    return accept(this->fileDescriptor, (struct sockaddr *) &sockaddr_client, (socklen_t *) &clientAddrLen);
}

int Socket::recibirMensaje(int *socketRecv, char* buffer, size_t sizeData){

    int totalBytesReceive = 0;
    int bytesReceive = 0;
    bool isOpen = true;

    while ((sizeData > totalBytesReceive) && isOpen){
        bytesReceive = read(*socketRecv, &buffer[totalBytesReceive], (sizeData - totalBytesReceive));
        
        if (bytesReceive < 0){
            return -1;
        } else if (bytesReceive == 0){
            isOpen = false;
            return 0;
        } else {
            totalBytesReceive += bytesReceive;
        }
    }

    return totalBytesReceive;
}

int Socket::enviarMensaje(const char* buffer, size_t sizeData){
       
    int totalBytesWritten = 0;
    int bytesWritten = 0;;
    bool isOpen = true;

    while ((sizeData > totalBytesWritten) && isOpen){
        bytesWritten = write(this->fileDescriptor, &buffer[totalBytesWritten], (sizeData - totalBytesWritten));

        if (bytesWritten < 0){
            return -1;
        } else if (bytesWritten == 0){
            isOpen = false;
            return 0;
        } else {
            totalBytesWritten += bytesWritten;
        }
    }

    return totalBytesWritten;
}

void Socket::cerrar(){
    shutdown(this->fileDescriptor, 2);
}
