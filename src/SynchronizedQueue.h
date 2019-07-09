#ifndef SYNCHRONIZEDQUEUE_H
#define SYNCHRONIZEDQUEUE_H

#include "monitor.h"
#include <queue>

template<typename T>
class SynchronizedQueue : Monitor {
private:
    std::queue<T> values;
    Condition isEmpty;
public:
    SynchronizedQueue();

    void put(T);
    T get();
    unsigned long getSize();
};

template<typename T>
SynchronizedQueue<T>::SynchronizedQueue() {
}

template<typename T>
void SynchronizedQueue<T>::put(T value) {
    enter();
    values.push(value);
    if (values.size() == 1) {
        signal(isEmpty);
    }
    leave();
}

template<typename T>
T SynchronizedQueue<T>::get() {
    T value;
    enter();
    if (values.size() == 0)
        Monitor::wait(isEmpty);
    value = values.front();
    values.pop();
    leave();
    return value;
}

template<typename T>
unsigned long SynchronizedQueue<T>::getSize() {
    enter();
    auto size = values.size();
    leave();
    return size;
}

#endif //SYNCHRONIZEDQUEUE_H