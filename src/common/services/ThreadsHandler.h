#ifndef THREADSHANDLER_H_
#define THREADSHANDLER_H_

#include "Logger.h"
#include <unordered_map>
#include <pthread.h>
#include <string>

#include "../providers/GameProvider.h"

using namespace std;

class ThreadsHandler {

    private:
        static unordered_map<string, pthread_t *> threads_;

    public:
        ThreadsHandler();
        ~ThreadsHandler();
        void addThread(pthread_t thread, string threadName);
};


#endif