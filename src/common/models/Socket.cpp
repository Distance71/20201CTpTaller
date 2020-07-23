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

int Socket::receiveMessage(stringstream &s, size_t sizeData){

    int totalBytesReceive = 0;
    int bytesReceive = 0;
    bool isOpen = true;

    char buffer[sizeData + 1];

    for(size_t i = 0; i < sizeData; i++)
        buffer[i] = 0;
    buffer[sizeData] = '\0';
    
    while ((totalBytesReceive < sizeData) && isOpen){
        bytesReceive = read(this->fileDescriptor_, (void *) buffer + totalBytesReceive, (sizeData - totalBytesReceive));
        if (bytesReceive < 0){
            Logger::getInstance()->log(DEBUG, "Se ha producido un error al recibir el mensaje en socket");
            return -1;
        } else if (bytesReceive == 0){
            isOpen = false;
            Logger::getInstance()->log(DEBUG, "Se ha cerrado el Socket");
            return 0;
        } else {
            totalBytesReceive += bytesReceive;
        }
    }

    s << buffer;

    Logger::getInstance()->log(DEBUG, "Se recibe el mensaje con exito en Socket");

    return totalBytesReceive;
}

int Socket::sendMessage(stringstream &s, size_t sizeData){
    int totalBytesWritten = 0;
    int bytesWritten = 0;;
    bool isOpen = true;

    Logger::getInstance()->log(DEBUG, "Se va a enviar un mensaje");

    string msg = s.str();
    
    char buffer[sizeData + 1];

    for(size_t i = 0; i < sizeData; i++)
        buffer[i] = 0;
    buffer[sizeData] = '\0';

    strcpy(buffer, msg.c_str());

    while ((sizeData > totalBytesWritten) && isOpen){
        bytesWritten = send(this->fileDescriptor_, (void *) (buffer + totalBytesWritten), (sizeData - totalBytesWritten), MSG_NOSIGNAL | MSG_DONTWAIT);
        if (bytesWritten < 0){
            Logger::getInstance()->log(DEBUG, "Se ha producido un error al mandar el mensaje en socket");
            return -1;
        } else if (bytesWritten == 0){
            isOpen = false;
            Logger::getInstance()->log(DEBUG, "Se ha cerrado el socket de destino en Socket");
            return 0;
        } else {
            totalBytesWritten += bytesWritten;
        }
    }

    Logger::getInstance()->log(DEBUG, "Se mando mensaje ok en Socket de tamaño " + std::to_string((int)sizeData));

    return totalBytesWritten;
}

void Socket::cerrar(){
    shutdown(this->fileDescriptor_, 2);
}
