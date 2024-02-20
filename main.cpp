#include <list>
#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <type_traits>

template<typename T, 
    typename Enable = typename std::enable_if<std::is_integral<T>::value>::type>
void print_ip(T value) 
{
    std::size_t len = sizeof(T);

    uint8_t* byte = reinterpret_cast<uint8_t*>(&value);

    for(int i = len - 1; i >= 0; i--)
    {
        std::cout << static_cast<int>(byte[i]);
        if (i > 0) [[likely]] std::cout << ".";
    }
    std::cout << std::endl;
}

template<typename T,
    typename Enable = typename std::enable_if<std::is_same<T, std::string>::value>::type>
void print_ip(const T& str)
{
    std::cout << str << std::endl;
}

template<typename T>
struct is_vector_or_list : std::false_type {};

template<typename T>
struct is_vector_or_list<std::vector<T>> : std::true_type {};

template<typename T>
struct is_vector_or_list<std::list<T>> : std::true_type {};

template<typename T, typename std::enable_if<is_vector_or_list<T>{}, bool>::type = true>
void print_ip(const T& container)
{
    for(auto it = container.begin(); it != container.end(); ++it)
    {
        std::cout << *it;

        if (it != std::prev(container.end())) [[likely]]
            std::cout << ".";
    }
    std::cout << std::endl;
}

int main()
{
    print_ip( int8_t{-1} ); // 255
    print_ip( int16_t{0} ); // 0.0
    print_ip( int32_t{2130706433} ); // 127.0.0.1
    print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41

    print_ip( std::string{"Hello, World!"} ); // Hello, World!
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100

    return 0;
}
