#ifndef BLOCKING_MAP_H
#define BLOCKING_MAP_H

#include <mutex>
#include <condition_variable>
#include <deque>
#include <unordered_map>
#include "../types.h"

template <typename T>
class BlockingMap
{
private:
    std::mutex              d_mutex;
    std::condition_variable d_condition;
    unordered_map <Id, T *> d_map;
    vector<Id>             d_vector;
    

public:
    void put(T const& id, T* value) {
        std::lock_guard lock(this->d_mutex);
        m_map.emplace(id, value);
        d_vector.push_back(id);
    }

    T* get(T const& id) {
        std::shared_lock lock(this->d_mutex);
        auto it = m_map.find(id);
        if (it != m_map.end())
            return it->second;
        return NULL;
    }

     getAllKeys(){
        return this->d_vector;
    }


    void delete(T const& id) {
        std::lock_guard lock(this->d_mutex);
        auto it = m_map.find(id);
        if (it != m_map.end()) {
            m_map.erase(id);
            delete it->second;
        }
    }
};

#endif