#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "3.optimization.hpp"
#include "../TimeSpent.hpp"
#include "../PeakMemory.hpp"
using namespace std;

BOOST_AUTO_TEST_CASE(optim)
{
    Optimization opt;
    constexpr int SIZE = 10;

    auto gen = opt.generator_space(SIZE);
    BOOST_CHECK_THROW(gen[-1], underflow_error);
    BOOST_CHECK_THROW(gen[SIZE * (SIZE + 1)], overflow_error);

    auto vec_noopt = opt.generator(SIZE);
    auto vec_opt = opt.generator_speed(SIZE);
    BOOST_TEST(vec_noopt.size() == vec_opt.size(), "no opt: " << vec_noopt.size() << "; opt: " << vec_opt.size());

    for (int i = 0; i < static_cast<int>(vec_noopt.size()); ++i)
    {
        BOOST_TEST(vec_noopt[i] == vec_opt[i], "i: " << i << "; no opt: " << vec_noopt[i] << "; opt: " << vec_opt[i]);
        BOOST_TEST(vec_noopt[i] == gen[i], "i: " << i << "; no opt: " << vec_noopt[i] << "; gen: " << gen[i]);
    }
}

BOOST_AUTO_TEST_CASE(optim_benchmarks)
{
    constexpr int SIZE = 20000;
    Optimization opt;
    TimeSpent stopwatch;
    PeakMemory mem_mon;

    {
        auto res = opt.generator_space(SIZE);
        mem_mon.note_mem_usage();
        BOOST_TEST_MESSAGE("opt space | res[666]:" << res[666]);
    }
    double space_opt = mem_mon.mega();

    {
        stopwatch.start();
        auto res = opt.generator(SIZE);
        stopwatch.stop();
        mem_mon.note_mem_usage();
        BOOST_TEST_MESSAGE("src | res[666]: " << res[666]);
    }
    int unopt_ms = stopwatch.spent();
    double space_src = mem_mon.mega();

    BOOST_TEST_MESSAGE("space | src: " << space_src << "; opt: " << space_opt);
    BOOST_CHECK(space_src / 1.1 > space_opt);

    stopwatch.start();
    opt.generator_speed(SIZE);
    stopwatch.stop();
    int opt_ms = stopwatch.spent();

    BOOST_TEST_MESSAGE("speed | src: " << unopt_ms << "; opt: " << opt_ms);
    BOOST_CHECK(unopt_ms / 1.1 > opt_ms * 1.0);
}
