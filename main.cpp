#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) : capacity{capacity} {}

    int get(int key) {
        auto mapItr = cacheMap.find(key);

        if (mapItr == cacheMap.end()) return -1;

        int value = mapItr->second->second;
        prioritize(key, mapItr->second);
        return value;
    }

    int put(int key, int value) {
        auto mapItr = cacheMap.find(key);
        if (mapItr != cacheMap.end()) {
            mapItr->second->second = value;
            prioritize(key, mapItr->second);
        } else {
            if (cacheList.size() == capacity) {
                int keyToDelete = cacheList.front().first;
                cacheList.pop_front();
                cacheMap.erase(keyToDelete);
            }
            cacheList.push_back({key, value});
            cacheMap[key] = prev(cacheList.end());
        }
    }

private:
    int capacity;
    list<pair<int, int>> cacheList;
    unordered_map<int, list<pair<int, int>>::iterator> cacheMap;

    void prioritize(int key, list<pair<int, int>>::iterator itr) {
        pair<int, int> priority{*itr};
        cacheList.erase(itr);
        cacheList.push_back(priority);
        cacheMap[key] = prev(cacheList.end());
    }
};


int main() {
    std::cout << "Hello, World!" << std::endl;
}
