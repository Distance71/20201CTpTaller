#include "ServerTransmitionManager.h"

ServerTransmitionManager::ServerTransmitionManager(Server *server, size_t port){
    this->serverOwn_ = server;
    this->socket_ = new Socket();
    this->socket_->setPort(port);
    pthread_mutex_init(&this->mutex_lastId_,NULL);
}

ServerTransmitionManager::~ServerTransmitionManager(){
    pthread_mutex_destroy(&this->mutex_lastId_);
}

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

    // Se compara con el Server porque ServerTransmitionManager puede tener mas usuarios de la cantidad del juego
    // porque el Socket hace el accept antes de que del logeo y demas
    while (!this->serverOwn_->isFull()){
    
        int newFDClient = this->socket_->acceptClient();

        if (newFDClient < 0){
            Logger::getInstance()->log(ERROR, "Error al aceptar al cliente.");
        } else {
            pthread_mutex_lock(&this->mutex_lastId_);
            Socket *newSocketClient = new Socket(newFDClient);
            UsersManager *newUser = new UsersManager(this->lastId_, newSocketClient, this->serverOwn_);          
            this->users_[this->lastId_] = newUser;
            
            this->serverOwn_->addPlayer(this->lastId_, newUser);
            this->lastId_++; 
            cout << "Se agrega el cliente " + to_string(this->lastId_) << endl;     
            pthread_mutex_unlock(&this->mutex_lastId_);       

            unsigned int width = GameProvider::getWidth();
            unsigned int height = GameProvider::getHeight();
            MessageInitScreen initScreen = MessageInitScreen(width, height);
            string dataString;
            dataString = initScreen.getStringData();
        
            newSocketClient->enviarMensaje(dataString.c_str(), sizeof(char) *dataString.size());
            
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