#pragma once

#include <memory>

template<typename T>
class ring_buffer
{
public:
    ring_buffer(const size_t size)
        : elements(std::unique_ptr<T[]>(new T[size]))
    {
    }

    void write(const T& element)
    {
        elements[head++ % _size] = element;
    }

    T* read() const
    {
        return (tail < head) ? &elements[tail++ % _size] : nullptr;
    }

    void clear()
    {
        tail = 0;
        head = 0;
    }

    bool empty() const
    {
        return tail == head;
    }

private:
    std::unique_ptr<T[]> elements = nullptr;
    mutable std::atomic<size_t> tail = 0;
    mutable std::atomic<size_t> head = 0;
};