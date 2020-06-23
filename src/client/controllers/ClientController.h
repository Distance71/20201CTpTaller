#ifndef CLIENTCONTROLLER_H_
#define CLIENTCONTROLLER_H_

#include "../../common/types.h"
#include "SDL2/SDL.h"
#include "../Client.h"

class Client;

class ClientController {
    private:
        Client *clientOwn_;

    public:
        ClientController(Client *client);
        ~ClientController();

        void update();
};

#endif // CLIENTCONTROLLER_H_