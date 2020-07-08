#include "Socket.h"

Socket::Socket(){}

Socket::Socket(int fd){
    this->fileDescriptor_ = fd;
}

Socket::~Socket(){}

void Socket::setPort(unsigned int port){
    this->port_ = port;
}

bool Socket::create(){
    
    this->fileDescriptor_ = socket(AF_INET, SOCK_STREAM, 0);

    if (this->fileDescriptor_ < 0)
        return false;

    return true;
}

bool Socket::setOption(){
    int enable = 1;
    int optsSetted = setsockopt(this->fileDescriptor_, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

    if (optsSetted < 0)
        return false;

    return true;
}

bool Socket::link(){

    struct sockaddr_in socket_addr; 

    socket_addr.sin_family = AF_INET;
    socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_addr.sin_port = htons(this->port_);

    if (bind(this->fileDescriptor_, (struct sockaddr *) &socket_addr, sizeof(socket_addr)) < 0)
        return false; 
    
    return true;
}

bool Socket::listenConnections(int maxConnections){

    if (listen(this->fileDescriptor_, maxConnections) < 0)
        return false;

    return true; 
}

bool Socket::connectWithServer(string ipHost){

    struct sockaddr_in server; 

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ipHost.c_str());
    server.sin_port = htons(this->port_);

    if (connect(this->fileDescriptor_, (struct sockaddr *) &server, sizeof(server)))
        return false;
    
    return true;
}

int Socket::acceptClient(){
    struct sockaddr_in sockaddr_client;
    int clientAddrLen;

    return accept(this->fileDescriptor_, (struct sockaddr *) &sockaddr_client, (socklen_t *) &clientAddrLen);
}

int Socket::receiveMessage(void* &buffer, size_t sizeData){

    cout << "llegue " << sizeof(buffer) << endl;
    int totalBytesReceive = 0;
    int bytesReceive = 0;
    bool isOpen = true;

    while ((totalBytesReceive < sizeData) && isOpen){
        cout << "ok" << endl;
        bytesReceive = read(this->fileDescriptor_, (void *) buffer + totalBytesReceive - 1, (sizeData - totalBytesReceive));
        cout << "Aca" << endl;
        if (bytesReceive < 0){
            return -1;
        } else if (bytesReceive == 0){
            isOpen = false;
            return 0;
        } else {
            totalBytesReceive += bytesReceive;
        }
    }

    cout << "bits "<< totalBytesReceive << endl;

    return totalBytesReceive;
}

int Socket::sendMessage(void* &buffer, size_t sizeData){
    int totalBytesWritten = 0;
    int bytesWritten = 0;;
    bool isOpen = true;

    while ((sizeData > totalBytesWritten) && isOpen){
        bytesWritten = write(this->fileDescriptor_, (void *) (buffer + totalBytesWritten), (sizeData - totalBytesWritten));

        if (bytesWritten < 0){
            return -1;
        } else if (bytesWritten == 0){
            isOpen = false;
            return 0;
        } else {
            totalBytesWritten += bytesWritten;
        }
    }

    cout << "debug2 " << totalBytesWritten << endl;

    return totalBytesWritten;
}

void Socket::cerrar(){
    shutdown(this->fileDescriptor_, 2);
}
