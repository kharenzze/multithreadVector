//
// Created by Paolo on 08/07/2018.
//

#ifndef MULTITHREADVECTOR_MTVECTOR_H
#define MULTITHREADVECTOR_MTVECTOR_H

#include <vector>
#include <mutex>
#include <functional>
#include <thread>

using std::vector;
using std::mutex;
using std::lock_guard;
using std::size_t;

template <class T>
class MTVector {
private:
    vector<T> _v;
    mutex _m;
public:
    MTVector() = default;

    void push_back(const T& v) {
        lock_guard<mutex> lock(_m);
        _v.push_back(v);
    }

    void push_back (T&& sv) {
        lock_guard<mutex> lock(_m);
        _v.push_back(sv);
    }

    void clear() {
        lock_guard<mutex> lock(_m);
        _v.clear();
    }

    void resize(size_t n) {
        lock_guard<mutex> lock(_m);
        _v.resize(n);
    }

    void reserve(size_t n) {
        lock_guard<mutex> lock(_m);
        _v.reserve(n);
    }

    T& emplace_back(T&& v) {
        lock_guard<mutex> lock(_m);
        return _v.emplace_back(v);
    }

    void erase(size_t first, size_t last)  {
        lock_guard<mutex> lock(_m);
        _v.erase(first, last);
    }

    T pop_back() {
        lock_guard<mutex> lock(_m);
        return _v.pop_back();
    }

    size_t size() {
        lock_guard<mutex> lock(_m);
        return _v.size();
    }

    size_t  capacity () {
        lock_guard<mutex> lock(_m);
        return _v.capacity();
    }

    bool empty() {
        lock_guard<mutex> lock(_m);
        return _v.empty();
    }

    T& operator[](size_t idx) {
        lock_guard<mutex> lock(_m);
        return _v[idx];
    }

    const T& operator[](size_t idx) const {
        lock_guard<mutex> lock(_m);
        return _v[idx];
    }

    T& back() {
        lock_guard<mutex> lock(_m);
        return _v.back();
    }

    const T& back() const {
        lock_guard<mutex> lock(_m);
        return _v.back();
    }

    void forEach(std::function<void(const T&)> f) const {
        lock_guard<mutex> lock(_m);
        size_t s = _v.size();
        for (uint32_t i = 0; i < s; i++) {
            f(*_v[i]);
        }
    }

    void forEach(std::function<void(T&)> f) {
        lock_guard<mutex> lock(_m);
        size_t s = _v.size();
        for (uint32_t i = 0; i < s; i++) {
            f(_v[i]);
        }
    }

    void swapElement (size_t pos, T *other) {
       lock_guard<mutex> lock(_m);
        _v[pos] = *other;
    }

    void swap(MTVector &other) {
        lock_guard<mutex> lock(_m);
        _v = other._v;
    }
};

#endif //MULTITHREADVECTOR_MTVECTOR_H
