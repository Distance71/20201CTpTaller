#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>

using namespace std;

class Semaphore
{
    private:
        std::mutex mutex_;
        condition_variable conditionReacher_;
        int count_;

    public:
        Semaphore(size_t count);
        ~Semaphore() = default;

        void post();
        void wait();
};

#endif