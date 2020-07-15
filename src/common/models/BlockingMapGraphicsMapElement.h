#ifndef BLOCKING_MAP_GRAPHICS_MAP_ELEMENT_H
#define BLOCKING_MAP_GRAPHICS_MAP_ELEMENT_H

#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <deque>
#include <unordered_map>
#include "../types.h"
#include "../../client/screenManager/graphics/GraphicsMapElement.h"

class BlockingMapGraphicsMapElement
{
private:
    std::mutex              d_mutex;
    std::condition_variable d_condition;
    unordered_map <Id, GraphicsMapElement*>   d_map;
    vector<Id>              d_vector;
    
public:

    void put(Id const& id, GraphicsMapElement *value) {
        std::unique_lock<std::mutex> lock(this->d_mutex);
        auto it = d_map.find(id);
        if (it != d_map.end())
            delete it->second;
        else
            d_vector.push_back(id);

        d_map.emplace(id, value);
        this->d_condition.notify_one();
    }

    GraphicsMapElement* get(Id const& id) {
        std::unique_lock<std::mutex> lock(this->d_mutex);
        auto itAux = d_map.find(id);
        this->d_condition.wait(lock, [=]{ return itAux->second->isSet(); });
        auto it = d_map.find(id);
        if (it != d_map.end())
            return it->second;

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

#endif