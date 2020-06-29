#include "ThreadsHandler.h"

ThreadsHandler::ThreadsHandler(){

}

ThreadsHandler::~ThreadsHandler(){

}

void ThreadsHandler::addThread(pthread_t *thread, string threadName) {
    threads_[threadName] = thread;
};