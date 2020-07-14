#ifndef _BLOCKING_MAP_H_
#define _BLOCKING_MAP_H_

#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <deque>
#include <unordered_map>
#include "../types.h"

template<typename T>
class BlockingMap
{
private:
    std::mutex              d_mutex;
    std::condition_variable d_condition;
    unordered_map <Id, T*>   d_map;
    vector<Id>              d_vector;
    
public:

    void put(Id const& id, T *value) {
        std::unique_lock<std::mutex> lock(this->d_mutex);
        auto it = d_map.find(id);
        if (it != d_map.end())
            delete it->second;
        else
            d_vector.push_back(id);

        d_map.emplace(id, value);
        this->d_condition.notify_one();
    }

    T* get(Id const& id) {
        std::unique_lock<std::mutex> lock(this->d_mutex);
        auto it = d_map.find(id);
        if (it != d_map.end())
            return new T(*(it->second));

        return NULL;
    }

    vector<Id> getAllKeys(){
        return this->d_vector;
    }

    void deleteElement(Id const& id) {
        std::lock_guard<std::mutex> lock(this->d_mutex);
        // this->d_condition.wait(lock, [=]{ 
        //     auto it = d_map.find(id); 
        //     return it != d_map.end()
        // });
        auto it = d_map.find(id);
        d_map.erase(id);
        delete it->second;
    }
};

#endif // _BLOCKING_MAP_H_