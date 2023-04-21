// Equiilibrium Point

// Find if there is index such that sum of all elements to the left including the index
// is equal to the sum of all elements to the right including the index.

#include <vector>
#include <numeric>

#define BOOST_TEST_MODULE equilibrium_point
#include <boost/test/included/unit_test.hpp>

std::size_t GetEquilibriumPoint(const std::vector<int>& numbers)
{
    int sum_to_left = 0;
    int sum_to_right = std::accumulate(numbers.cbegin(), numbers.cend(), 0);
    
    for (std::size_t i = 0; i < numbers.size(); ++i)
    {
        sum_to_left += numbers[i];
        if (i >= 1)
            sum_to_right -= numbers[i - 1];

        if (sum_to_left == sum_to_right)
            return i;
    }
    
    return static_cast<std::size_t>(-1);
}

// { }          -1
// { 0 }        0
// { 1 1 1 }    1

BOOST_AUTO_TEST_CASE(test_GetEquilibriumPoint)
{
    BOOST_TEST(static_cast<std::size_t>(-1) == GetEquilibriumPoint({}));
    BOOST_TEST(0u == GetEquilibriumPoint({ 0 }));
    BOOST_TEST(1u == GetEquilibriumPoint({ 1, 1, 1 }));
}
