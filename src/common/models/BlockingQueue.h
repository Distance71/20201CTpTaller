#ifndef QUEUE_H
#define QUEUE_H

#include <mutex>
#include "Semaphore.h"

using namespace std;

#define QUANTITY_EVENTS 100

template<typename T>
class BlockingQueue {
    public:
    
    BlockingQueue(size_t size = QUANTITY_EVENTS) {
        data_.reserve(size);
        openSlots(size);
        fullSlots(0);
    }

    ~BlockingQueue() {
        int i = this->count - 1;
        while (i >= 0)
            data[i--].~T();
        
        delete(data_);
    }

    void push(const T &item) {
        openSlots.wait();
        {
            lock_guard<mutex> lock(mutex);
            data_.insert(data_.begin(), item);
        }
        fullSlots.post();
    }

    T pop() {
        fullSlots.wait();
        {
            lock_guard<mutex> lock(mutex);
            lastIndex = data_.size() - 1;
            T item = data_[lastIndex];
            data_pop_back();
        }
        openSlots.post();
        return item;
    }

    bool empty() {
        lock_guard<mutex> lock(mutex);
        return count_ == 0;
    }

private:
    size_t size_;
    size_t count_;
    vector <T *> data_;

    Semaphore openSlots;
    Semaphore fullSlots;
    mutex mutex;
};

#endif