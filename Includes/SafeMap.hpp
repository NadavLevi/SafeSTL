#ifndef SAFE_MAP_HPP
#define SAFE_MAP_HPP

#include <map>
#include <mutex>

namespace SafeSTL {
    template<typename Key, typename Value>
    class SafeMap {
    private:
        std::map<Key, Value> _map;
        std::mutex _mutex;

    public:
        SafeMap() = default;

        SafeMap(const SafeMap &sm) : _map(std::move(sm._map)), _mutex(std::move(sm._mutex)) {}

        bool empty() {
            std::unique_lock<std::mutex> lock(_mutex);
            return _map.empty();
        }

        uint64_t size() {
            std::unique_lock<std::mutex> lock(_mutex);
            return _map.size();
        }

        void emplace(Key &&k, Value &&v) {
            std::unique_lock<std::mutex> lock(_mutex);
            _map.emplace(k, v);
        }

        void clear() {
            std::unique_lock<std::mutex> lock(_mutex);
            _map.clear();
        }

        void erase(const Key &k) {
            std::unique_lock<std::mutex> lock(_mutex);
            _map.erase(k);
        }

        auto find(const Key &k) {
            std::unique_lock<std::mutex> lock(_mutex);
            return _map.find(k);
        }

        auto end() {
            std::unique_lock<std::mutex> lock(_mutex);
            return _map.end();
        }
    };
}


#endif