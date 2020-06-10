#ifndef CLIENTCONTROLLER_H_
#define CLIENTCONTROLLER_H_

#include "../../common/types.h"
#include "SDL2/SDL.h"

class ClientController {
    private:

    public:
        ClientController();
        ~ClientController();

        void update();
};

#endif // CLIENTCONTROLLER_H_