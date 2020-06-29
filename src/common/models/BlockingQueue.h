#ifndef QUEUE_H
#define QUEUE_H

#include <vector>
#include <mutex>
#include "Semaphore.h"

using namespace std;

#define QUANTITY_EVENTS 100

template<typename T>
class BlockingQueue {

    private:
    size_t size_;
    size_t count_;
    vector <T *> data_;

    Semaphore* openSlots;
    Semaphore* fullSlots;
    std::mutex mutex;

    public:
    
    BlockingQueue(size_t size = QUANTITY_EVENTS) {
        data_.reserve(size);
        openSlots = new Semaphore(size);
        fullSlots = new Semaphore((size_t) 0);
    }

    ~BlockingQueue() {
        int i = this->count_ - 1;
        while (i >= 0)
            delete data_[i--];
        
        //delete(data_); no porque no es puntero
    }

    void push(const T &item) {
        openSlots->wait();
        {
            lock_guard<std::mutex> lock(mutex);
            data_.insert(data_.begin(), item);
        }
        fullSlots->post();
    }

    T* pop() {
        fullSlots->wait();
        T* item;
        {
            lock_guard<std::mutex> lock(mutex);
            auto lastIndex = data_.size() - 1;
            item = data_[lastIndex];
            data_.pop_back();
        }
        openSlots->post();
        return item;
    }

    bool empty() {
        lock_guard<std::mutex> lock(mutex);
        return count_ == 0;
    }

};

#endif