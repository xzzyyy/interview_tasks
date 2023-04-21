#define BOOST_TEST_MODULE misc-ut
#include <boost/test/included/unit_test.hpp>
#include "PeakMemory.hpp"
using namespace std;

BOOST_AUTO_TEST_CASE(pid)
{
    auto pid = PeakMemory::this_process_id();
    BOOST_TEST(pid != 0u, "pid != 0u");
    BOOST_TEST(pid < 100'000'000u, "pid < 100'000'000u");
}

BOOST_AUTO_TEST_CASE(process_mem, * boost::unit_test::timeout(2))
{
    auto peak_mem = PeakMemory::mega();
    BOOST_TEST(peak_mem > 0.1, "peak_mem > 100KB");
    BOOST_TEST(peak_mem < 100.0, "peak_mem < 100MB");
}
