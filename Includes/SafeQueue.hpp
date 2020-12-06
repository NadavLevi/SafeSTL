#ifndef SAFE_QUEUE_HPP
#define SAFE_QUEUE_HPP

#include <mutex>
#include <queue>
namespace SafeSTL {
template<typename T>
class SafeQueue {
private:
    std::queue<T> _queue;
    std::mutex _mutex;

public:
    SafeQueue() = default;

    SafeQueue(const SafeQueue &sq) : _queue(std::move(sq._queue)), _mutex(std::move(sq._mutex)) {}

    bool empty() {
        std::unique_lock<std::mutex> lock(_mutex);
        return _queue.empty();
    }

    uint64_t size() {
        std::unique_lock<std::mutex> lock(_mutex);
        return _queue.size();
    }

    void push(T &t) {
        std::unique_lock<std::mutex> lock(_mutex);
        _queue.push(t);
    }

    void emplace(T &&t) {
        std::unique_lock<std::mutex> lock(_mutex);
        _queue.emplace(t);
    }

    void top(T &t) {
        std::unique_lock<std::mutex> lock(_mutex);
        t = _queue.front();
    }

    T &top() {
        std::unique_lock<std::mutex> lock(_mutex);
        return _queue.front();
    }

    bool pop(T &t) {
        std::unique_lock<std::mutex> lock(_mutex);
        if (_queue.empty()) {
            return false;
        }
        t = std::move(_queue.front());
        _queue.pop();
        return true;
    }

    bool popAll(SafeQueue<T> &t) {
        std::unique_lock<std::mutex> lock(_mutex);
        T tmp;
        while (!_queue.empty()) {
            t.push(_queue.front());
            _queue.pop();
        }
    }

    bool clear() {
        std::unique_lock<std::mutex> lock(_mutex);
        while (!_queue.empty()) {
            _queue.pop();
        }
    }
}

};

#endif