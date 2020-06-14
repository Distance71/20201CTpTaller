#ifndef _THREADSHANDLER_H_
#define _THREADSHANDLER_H_

#include "../Logger.h"
#include <unordered_map>
#include <pthread.h>

using namespace std;

class ThreadsHandler {

    private:
    unordered_map<string, pthread_t *> threads_;

    public:
        ThreadsHandler();
        ~ThreadsHandler();
        void ThreadsHandler::createThread(void (*func) ()), string threadName);
};


#endif //_THREADSHANDLER_H_