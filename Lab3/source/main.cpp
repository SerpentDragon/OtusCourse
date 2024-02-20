#include <map>
#include <iostream>
#include "map/custom_map.hpp"
#include "allocator/map_allocator.hpp"

int factorial(int n)
{
    int result = 1;
    while(n) result *= n--;
    return result;
}

int main()
{
    // std::map<int, int> first_map;
    // for(int i = 0; i < 10; i++) first_map.insert({ i, factorial(i) });

    // std::map<int, int, std::less<int>, map_allocator<std::pair<int, int>>> second_map;
    // for(int i = 0; i < 10; i++) second_map.insert({ i, factorial(i) });

    // std::cout << "std::map with map_allocator:\n";
    // for(const auto& val : second_map)
    //     std::cout << val.first << " " << val.second << std::endl;

    MapIterator<custom_map<int, int>> it;

    return 0;
}
