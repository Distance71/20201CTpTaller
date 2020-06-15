#include "ServerTransmitionManager.h"

ServerTransmitionManager::ServerTransmitionManager(Server *server, size_t port){
    this->serverOwn_ = server;
    this->socket_ = new Socket();
    this->socket_->setPort(port);
}

ServerTransmitionManager::~ServerTransmitionManager(){}

bool ServerTransmitionManager::initialize(){

    if(!this->socket_->create()){
        string errorMessage = "No se pudo crear el socket para recibir clientes en el server";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return false;
    }

    if(!this->socket_->setOption()){
        string errorMessage = "No se pudieron setear las opciones del socket en el server";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return false;
    }

    if (!this->socket_->enlazar()) {
        string errorMessage = "No se pudo asignar una direccion al socket del server";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return false;
    }

    this->maxPlayers = GameProvider::getQuantityPlayers();

    if(!this->socket_->escuchar(this->maxPlayers)) {
        string errorMessage = "No se pudo configurar el socket para aceptar configuraciones entrantes";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return false;
    }

    return true;
};

bool ServerTransmitionManager::waitPlayers(){
    cout << "Esperando jugadores..." << endl;

    while (this->maxPlayers > this->players_.size()){
    
        int newFDClient = this->socket_->acceptClient();

        if (newFDClient < 0){
            Logger::getInstance()->log(ERROR, "Error al aceptar al cliente.");
        } else {
            Socket *newClient = new Socket(newFDClient);
            this->players_[this->lastId_] = newClient;

            cout << "Se agrega el cliente " + to_string(this->lastId_) << endl;

            this->lastId_++; 

            unsigned int width = GameProvider::getWidth();
            unsigned int height = GameProvider::getHeight();
            MessageInitScreen initScreen = MessageInitScreen(width, height);
            string dataString;
            dataString = initScreen.getStringData();
        
            newClient->enviarMensaje(dataString.c_str(), sizeof(char) *dataString.size());
            
            /*
            pthread_t newHilo;

            argpthread argumentos;
            argumentos.server = this;
            argumentos.nroClient = this->clients.size();
            argumentos.des = this->deserializer;

            pthread_create(&newHilo, NULL, recibirInformacion, &argumentos);*/

        }
    }
    return true;
};