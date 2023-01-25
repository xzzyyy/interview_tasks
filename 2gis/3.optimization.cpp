#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "3.optimization.hpp"
using namespace std;

BOOST_AUTO_TEST_CASE(optim)
{
    Optimization opt;
    constexpr int SIZE = 10;

    auto gen = opt.generator_space(SIZE);
    BOOST_CHECK_THROW(gen(-1), underflow_error);
    BOOST_CHECK_THROW(gen(SIZE * (SIZE + 1)), overflow_error);

    auto vec_noopt = opt.generator(SIZE);
    auto vec_opt = opt.generator_speed(SIZE);
    BOOST_TEST(vec_noopt.size() == vec_opt.size(), "no opt: " << vec_noopt.size() << "; opt: " << vec_opt.size());        // TODO BOOST_CHECK and BOOST_TEST diff?

    for (int i = 0; i < static_cast<int>(vec_noopt.size()); ++i)
    {
        BOOST_TEST(vec_noopt[i] == vec_opt[i], "i: " << i << "; no opt: " << vec_noopt[i] << "; opt: " << vec_opt[i]);
        BOOST_TEST(vec_noopt[i] == gen(i), "i: " << i << "; no opt: " << vec_noopt[i] << "; gen: " << gen(i));
    }
}

BOOST_AUTO_TEST_CASE(optim_speed)
{
    Optimization opt;
    constexpr int SIZE = 20000;

    
}
