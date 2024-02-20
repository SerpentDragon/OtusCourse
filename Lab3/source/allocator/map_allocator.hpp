#pragma once

template<class T>
class map_allocator
{
public:

    using value_type = T;

    map_allocator() : 
        is_reserved_(false), reserve_size_(10), 
        allocated_size_(0), mem_ptr_(nullptr) 
    {

    }

    template<typename U>
    map_allocator(const map_allocator<U>&) {};

    T* allocate(std::size_t n)
    {
        if(!is_reserved_)
        {
            std::size_t prev_n = n;
            
            if (n < reserve_size_)
                n = reserve_size_;

            if(mem_ptr_ = std::malloc(n * sizeof(T)))
            {
                allocated_size_ += prev_n;
                is_reserved_ = true;
                return static_cast<T*>(mem_ptr_);
            }
            else 
                throw std::bad_alloc();
        }

        if (allocated_size_ + n <= reserve_size_)
        {
            allocated_size_ += n;
            return static_cast<T*>(mem_ptr_) + allocated_size_ - n;
        }
        else
        {
            if (void* ptr = std::malloc(n * sizeof(T)))
                return static_cast<T*>(ptr);
            else
                throw std::bad_alloc();
        }
    }

    void deallocate(T* ptr, size_t n)
    {
        if (!(static_cast<T*>(mem_ptr_) < ptr 
            && ptr <= static_cast<T*>(mem_ptr_) + reserve_size_))
        {
            std::free(ptr);
        }
    }

private:

    bool is_reserved_;

    const std::size_t reserve_size_;

    std::size_t allocated_size_;

    void* mem_ptr_;
};

template<typename T, typename U>
bool operator==(const map_allocator<T>&, const map_allocator<U>&) { return false; }
