#include <gtest/gtest.h>
#include <vector>
#include <tuple>

using ip_tuple = std::tuple<int, int, int, int>;

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

using namespace testing;

void compare_vectors(const std::vector<ip_tuple>& out, 
    const std::vector<ip_tuple>& res)
{
    ASSERT_EQ(out.size(), res.size());

    for(size_t i = 0; i < out.size(); i++)
    {
        ASSERT_EQ(res[i], out[i]);
    }
}

TEST(sort_test, test)
{
    std::vector<ip_tuple> vec {
        {1, 70, 44, 170}, {222, 173, 235, 246}, {1, 1, 234, 8}, 
        {222, 82, 198, 61}, {1, 29, 168, 152}, {222, 130, 177, 64}
    };

    std::vector<ip_tuple> res {
        {222, 173, 235, 246}, {222, 130, 177, 64}, {222, 82, 198, 61}, 
        {1, 70, 44, 170}, {1, 29, 168, 152}, {1, 1, 234, 8}
    };

    std::sort(vec.begin(), vec.end(), comparator);

    for(size_t i = 0; i < vec.size(); i++)
    {
        ASSERT_EQ(vec[i], res[i]);
    }
}

TEST(filter, test1)
{
    std::vector<ip_tuple> vec {
        {222, 173, 235, 246}, {222, 130, 177, 64}, {222, 82, 198, 61}, 
        {1, 70, 44, 170}, {1, 29, 168, 152}, {1, 1, 234, 8}
    };

    std::vector<ip_tuple> res {
        {1, 70, 44, 170}, {1, 29, 168, 152}, {1, 1, 234, 8}
    };

    auto out = filter(vec, 1);

    compare_vectors(out, res);
}

TEST(filter, test2)
{
    std::vector<ip_tuple> vec {
        {222, 173, 235, 246}, {222, 130, 177, 64}, {222, 82, 198, 61}, 
        {222, 82, 65, 54}, {222, 82, 31, 4}, {1, 70, 44, 170}, 
        {1, 29, 168, 152}, {1, 1, 234, 8}, {1, 1, 1, 1}
    };

    std::vector<ip_tuple> res {
        {222, 82, 198, 61}, {222, 82, 65, 54}, {222, 82, 31, 4}
    };

    auto out = filter(vec, 222, 82);

    compare_vectors(out, res);
}

TEST(filter, test3)
{
    std::vector<ip_tuple> vec {
        {222, 173, 235, 246}, {222, 130, 177, 64}, {222, 82, 198, 65}, 
        {222, 82, 65, 54}, {222, 82, 31, 4}, {1, 70, 44, 170}, 
        {1, 29, 168, 152}, {1, 1, 65, 8}, {1, 1, 1, 1}
    };

    std::vector<ip_tuple> res {
        {222, 82, 198, 65}, {222, 82, 65, 54}, {1, 1, 65, 8}
    };

    auto out = filter_any(vec, 65);

    compare_vectors(out, res);
}

int main(int argc, char** argv) 
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
