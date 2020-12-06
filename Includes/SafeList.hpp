#ifndef SAFE_LIST_HPP
#define SAFE_LIST_HPP

#include <list>
#include <mutex>

namespace SafeSTL {
    template<typename T>
    class SafeList {
    private:
        std::list<T> _list;
        std::mutex _mutex;

    public:
        SafeList() = default;

        SafeList(const SafeList &sl) : _list(std::move(sl._list)), _mutex(std::move(sl._mutex)) {}

        auto begin() {
            std::unique_lock<std::mutex> lock(_mutex);
            return _list.begin();
        }

        auto end() {
            std::unique_lock<std::mutex> lock(_mutex);
            return _list.end();
        }

        const T &back() {
            std::unique_lock<std::mutex> lock(_mutex);
            return _list.back();
        }

        const T &front() {
            std::unique_lock<std::mutex> lock(_mutex);
            return _list.front();
        }

        bool empty() {
            std::unique_lock<std::mutex> lock(_mutex);
            return _list.empty();
        }

        uint64_t size() {
            std::unique_lock<std::mutex> lock(_mutex);
            return _list.size();
        }

        void emplace(T &&t) {
            std::unique_lock<std::mutex> lock(_mutex);
            _list.emplace(t);
        }

        void emplace_back(T &&t) {
            std::unique_lock<std::mutex> lock(_mutex);
            _list.emplace_back(t);
        }

        void emplace_front(T &&t) {
            std::unique_lock<std::mutex> lock(_mutex);
            _list.emplace_front(t);
        }

        template<typename SafeListIterator>
        auto erase(SafeListIterator it) {
            std::unique_lock<std::mutex> lock(_mutex);
            _list.erase(it);
        }

        void pop_back() {
            std::unique_lock<std::mutex> lock(_mutex);
            _list.pop_back();
        }

        void pop_front() {
            std::unique_lock<std::mutex> lock(_mutex);
            _list.pop_front();
        }

        void push_back(T &&t) {
            std::unique_lock<std::mutex> lock(_mutex);
            _list.push_back(t);
        }

        void push_front(T &&t) {
            std::unique_lock<std::mutex> lock(_mutex);
            _list.push_front(t);
        }

        bool clear() {
            std::unique_lock<std::mutex> lock(_mutex);
            _list.clear();
        }

    };
}

#endif
