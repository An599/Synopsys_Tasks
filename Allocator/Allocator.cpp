// Allocator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>
template <typename T>

class Allocator {
private:

public:
    Allocator() {};
    ~Allocator() {};

    T* allocate(std::size_t size) {
        if (std::numeric_limits<std::size_t>::max() / sizeof(T) < size)
            trow std::bad_array_new_length();
        return static_cast<T*>(::operator new(size * sizeof(T)));
    }
    void deallocate(T* ptr, std::size_t size ) {
        ::operator delete(*ptr);
    }
    template <typename... Args>
    construct(T* ptr, Args&&... args) {
        new (ptr) T(std::forward<Args>(args)...);
    }
    void destruct(T* ptr) {
        ptr->~T();
    }
};
