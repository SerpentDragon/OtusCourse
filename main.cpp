#include <map>
#include <vector>
#include <iostream>

int factorial(int n)
{
    int result = 1;
    while(n) result *= n--;
    return result;
}

template<class T>
class allocator
{
public:

    using value_type = T;

    allocator() : 
        is_reserved_(false), reserve_size_(10), 
        allocated_size_(0), mem_ptr_(nullptr) 
    {

    }

    template<typename U>
    allocator(const allocator<U>&) {};

    T* allocate(std::size_t n)
    {
        if(!is_reserved_)
        {
            std::size_t prev_n = n;

            if (n < reserve_size_)
                n = reserve_size_;

            if(mem_ptr_ = std::malloc(n * sizeof(T)))
            {
                allocated_size_ += n;
                is_reserved_ = true;
                return static_cast<T*>(mem_ptr_);
            }
            else 
                throw std::bad_alloc();
        }

        if (allocated_size_ + n < reserve_size_)
        {
            allocated_size_ += n;
            return static_cast<T*>(mem_ptr_) + allocated_size_;
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
bool operator==(const allocator<T>&, const allocator<U>&) { return false; }

int main()
{
    std::map<int, int, std::less<int>, allocator<std::pair<int, int>>> mapa;

    for(int i = 0; i < 10; i++) mapa.insert({ i, factorial(i) });


    for(const auto& p : mapa)
        std::cout << p.first << " " << p.second << std::endl;

    std::cout << mapa.size() << std::endl;


    return 0;
}
