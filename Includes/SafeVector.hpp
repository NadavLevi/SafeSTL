#ifndef SAFE_VECTOR_HPP
#define SAFE_VECTOR_HPP

#include <vector>
#include <mutex>

namespace SafeSTL {
    template<typename T>
    class SafeVector {
    private:
        std::vector<T> _vector;
        std::mutex _mutex;

    public:
        SafeVector() = default;

        SafeVector(const SafeVector &sv) : _vector(std::move(sv._vector)) {}

        T &at(size_t n) {
            std::unique_lock<std::mutex> lock(_mutex);
            return _vector.at(n);
        }

        auto begin() {
            std::unique_lock<std::mutex> lock(_mutex);
            return _vector.begin();
        }

        auto end() {
            std::unique_lock<std::mutex> lock(_mutex);
            return _vector.end();
        }

        const T &back() {
            std::unique_lock<std::mutex> lock(_mutex);
            return _vector.back();
        }

        const T &front() {
            std::unique_lock<std::mutex> lock(_mutex);
            return _vector.front();
        }

        bool empty() {
            std::unique_lock<std::mutex> lock(_mutex);
            return _vector.empty();
        }

        uint64_t size() {
            std::unique_lock<std::mutex> lock(_mutex);
            return _vector.size();
        }

        template<typename SafeVectorIterator>
        void emplace(SafeVectorIterator it, T &&t) {
            std::unique_lock<std::mutex> lock(_mutex);
            _vector.emplace(it, t);
        }

        void emplace_back(T &&t) {
            std::unique_lock<std::mutex> lock(_mutex);
            _vector.emplace_back(t);
        }

        template<typename SafeVectorIterator>
        auto erase(SafeVectorIterator it) {
            std::unique_lock<std::mutex> lock(_mutex);
            _vector.erase(it);
        }

        void pop_back(T &&t) {
            std::unique_lock<std::mutex> lock(_mutex);
            _vector.pop_back();
        }

        void push_back(T &&t) {
            std::unique_lock<std::mutex> lock(_mutex);
            _vector.push_back(t);
        }

        bool clear() {
            std::unique_lock<std::mutex> lock(_mutex);
            _vector.clear();
        }

        bool reserve(unsigned long n) {
            std::unique_lock<std::mutex> lock(_mutex);
            _vector.reserve(n);
        }


    };
}

#endif