#ifndef _CLIENT_TEST_H_
#define _CLIENT_TEST_H_

#include "Client.h"

class ClientTest : public Client {
    private:

    public:
        ClientTest(string ipAddress, size_t port): Client (ipAddress, port) {};
        
        int runTest();
    
};

#endif