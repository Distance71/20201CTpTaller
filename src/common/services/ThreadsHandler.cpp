#include "ThreadsHandler.h"

ThreadsHandler::ThreadsHandler(){

}

ThreadsHandler::~ThreadsHandler(){

}

void ThreadsHandler::createThread(void (*func) (), string threadName) {
    pthread_t thread;
/*
    int pthreadCreateStatus = pthread_create(&thread, nullptr, [](void *arg) -> func, (void *) this);

    if(!pthreadCreateStatus) {
        string errorMessage = "No se pudo crear el hilo para manejar un proceso ";
        errorMessage.append(threadName);
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    string strLog = "Se creó el hilo de transmision ";
    Logger::getInstance()->log(DEBUG, strLog.append(threadName));
*/
    //Need to validate this
    threads_[threadName] = &thread;
}