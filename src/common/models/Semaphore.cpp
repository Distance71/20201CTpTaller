#include "Semaphore.h"

Semaphore::Semaphore(size_t count){
    this->count_ = count;
}

void Semaphore::post()
{
    unique_lock<mutex> lock(mutex);
    this->count_++;
    this->conditionReacher_.notify_one();
};

void Semaphore::wait()
{
    unique_lock<mutex> lock(mutex);
    this->conditionReacher_.wait(lock, [&]{ return this->count_ > 0; });
    this->count_--;
};
