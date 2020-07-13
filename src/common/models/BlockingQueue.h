#ifndef QUEUE_H
#define QUEUE_H

#include <mutex>
#include <condition_variable>
#include <deque>

template <typename T>
class BlockingQueue
{
private:
    std::mutex              d_mutex;
    std::condition_variable d_condition;
    std::deque<T>           d_queue;
public:
    void push(T value) {
        std::unique_lock<std::mutex> lock(this->d_mutex);
        d_queue.push_front(value);
        this->d_condition.notify_one();
    }
    T pop() {
        std::unique_lock<std::mutex> lock(this->d_mutex);
        this->d_condition.wait(lock, [=]{ return !this->d_queue.empty(); });
        T rc(std::move(this->d_queue.back()));
        this->d_queue.pop_back();
        return rc;
    }

    bool empty() {
        std::unique_lock<std::mutex> lock(d_mutex);
        return d_queue.empty();
    }

};

#endif

// #include <vector>
// #include <mutex>
// #include "Semaphore.h"

// using namespace std;


// #define QUANTITY_EVENTS 100

// class Semaphore;
// template<typename T>
// class BlockingQueue {

//     private:
//     size_t size_;
//     size_t count_;
//     vector <T *> data_;

//     Semaphore* openSlots;
//     Semaphore* fullSlots;
//     std::mutex mutex;

//     public:
    
//     BlockingQueue(size_t size = QUANTITY_EVENTS) {
//         data_.reserve(size);
//         openSlots = new Semaphore(size_);
//         fullSlots = new Semaphore((size_t) 0);
//     }

//     ~BlockingQueue() {
//         /*int i = this->count_ - 1;
//         while (i >= 0)
//             delete data_[i--];*/ // segmentation fault
        
//         delete this->openSlots;
//         delete this->fullSlots;
//     }

//     void push(const T &item) {
//         openSlots->wait();
//         {
//             lock_guard<std::mutex> lock(mutex);
//             data_.insert(data_.begin(), (T*) item);
//         }
//         fullSlots->post();
//     }

//     T* pop() {
//         fullSlots->wait();
//         T* item;
//         {
//             lock_guard<std::mutex> lock(mutex);
//             auto lastIndex = data_.size() - 1;
//             item = data_[lastIndex];
//             data_.pop_back();
//         }
//         openSlots->post();
//         return item;
//     }

//     bool empty() {
//         lock_guard<std::mutex> lock(mutex);
//         return count_ == 0;
//     }

// };

// #endif