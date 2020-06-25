#include "ThreadsHandler.h"

ThreadsHandler::ThreadsHandler(){

}

ThreadsHandler::~ThreadsHandler(){

}

// void ThreadsHandler::createThread(void (*func) ()), string threadName) {
//     pthread_t thread;

//     int pthreadCreateStatus = pthread_create(&thread, nullptr, [](void *arg) -> func, (void *) this);

//     if(!pthreadCreateStatus) {
//         string errorMessage = "No se pudo crear el hilo para manejar un proceso ".append(threadName);
//         Logger::getInstance()->log(ERROR, errorMessage);
//         setErrorStatus(errorMessage);
//         return;
//     }
//     Locator::logger()->log(DEBUG, "Se creó el hilo de transmision ".append(threadName));

//     //Need to validate this
//     threads_[threadName] = thread;
// }