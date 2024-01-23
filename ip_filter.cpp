#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

using ip_tuple = std::tuple<int, int, int, int>;

void print_ip(const ip_tuple& t)
{
    std::cout << std::get<0>(t) << "." << std::get<1>(t) << "." 
        << std::get<2>(t) << "." << std::get<3>(t) << std::endl;
}

bool comparator(const ip_tuple& t1, const ip_tuple& t2)
{
    int t1_1 = std::get<0>(t1), t2_1 = std::get<0>(t2);
    int t1_2 = std::get<1>(t1), t2_2 = std::get<1>(t2);
    int t1_3 = std::get<2>(t1), t2_3 = std::get<2>(t2);
    int t1_4 = std::get<3>(t1), t2_4 = std::get<3>(t2);

    if (t1_1 == t2_1)
    {
        if (t1_2 == t2_2)
        {
            if (t1_3 == t2_3)
            {
                return t1_4 > t2_4;
            }
            else return t1_3 > t2_3;
        }
        else return t1_2 > t2_2;
    }
    else return t1_1 > t2_1;
}

std::vector<ip_tuple> filter(const std::vector<ip_tuple>& vec, int byte)
{
    std::vector<ip_tuple> result;

    for(const auto& ip : vec)
    {
        if (std::get<0>(ip) == byte)
            result.push_back(ip);
    }

    return result;
}

std::vector<ip_tuple> filter(const std::vector<ip_tuple>& vec, int byte1, int byte2)
{
    std::vector<ip_tuple> result;

    for(const auto& ip : vec)
    {
        if (std::get<0>(ip) == byte1 && std::get<1>(ip) == byte2)
            result.push_back(ip);
    }

    return result;
}

std::vector<ip_tuple> filter_any(const std::vector<ip_tuple>& vec, int byte)
{
    std::vector<ip_tuple> result;

    for(const auto& ip : vec)
    {
        auto [b1, b2, b3, b4] = ip;
        if (b1 == byte || b2 == byte || b3 == byte || b4 == byte)
            result.push_back(ip);
    }

    return result;
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<ip_tuple> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(split(line, '\t').at(0), '.');
            ip_pool.push_back({ stoi(v[0]), stoi(v[1]), stoi(v[2]), stoi(v[3]) });
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), comparator);

        for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            print_ip(*ip);
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        auto ip = filter(ip_pool, 1);
        for(const auto& val : ip) print_ip(val);

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        ip = filter(ip_pool, 46, 70);
        for(const auto& val : ip) print_ip(val);

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        ip = filter_any(ip_pool, 46);
        for(const auto& val : ip) print_ip(val);

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
