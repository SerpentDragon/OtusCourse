#pragma once

template<class T>
class allocator
{
public:

    allocator() {};

    template<typename U>
    allocator(const allocator<U>&) {};

    T* allocate(std::size_t size)
    {
        if(void* mem_ptr = std::malloc(size * sizeof(T)))
            return static_cast<T*>(mem_ptr);
        else 
            throw std::bad_alloc();
    }

    void deallocate(T* ptr, std::size_t size)
    {
        std::free(ptr);
    }
};

template<typename T, typename U>
bool operator==(const allocator<T>&, const allocator<U>&) { return false; }
