#include "ClientTest.h"

int ClientTest::runTest(){
    this->initializeClient();
    if (!this->isConnected())
        return EXIT_FAILURE;
    
    cout << "Se conecta con el servidor " << endl;
    
    cout << "Envio de Msj al server para logearlo... " << endl;
    MessageLog message_prueba = MessageLog((int)INFO,"TEST- Envio log a server");
    this->sendMessage((Message *) &message_prueba);

    //TODO cargar tests
    
    this->gameScreen_->screenTest();

    return EXIT_SUCCESS;    
}
