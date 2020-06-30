#include "ThreadsHandler.h"

ThreadsHandler::ThreadsHandler(){

}

ThreadsHandler::~ThreadsHandler(){

}

void ThreadsHandler::addThread(pthread_t *thread, const string threadName) {
    this->threads_[threadName] = thread;
};