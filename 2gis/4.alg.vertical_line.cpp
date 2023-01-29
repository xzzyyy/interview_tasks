#include <limits>
#include <boost/test/unit_test.hpp>
#include "4.alg.vertical_line.hpp"
using namespace std;

BOOST_AUTO_TEST_CASE(vertical_line, * boost::unit_test::tolerance(0.00001))
{
    BOOST_TEST(VerticalLine::find_vertical_x({ {1,4},{3,3},{6,2},{9,3},{11,4} }) == 6.0);
    BOOST_TEST(VerticalLine::find_vertical_x({ {3,3},{3,4},{9,3},{9,4} }) == 6.0);
    BOOST_TEST(VerticalLine::find_vertical_x({ {3,4},{5,3},{7,2},{9,4},{11,3} }) == numeric_limits<double>::infinity());
    BOOST_TEST(VerticalLine::find_vertical_x({ {1,4},{3,2},{9,3},{11,4} }) == numeric_limits<double>::infinity());
    BOOST_TEST(VerticalLine::find_vertical_x({ {3,3},{4,3},{5,3},{7,3},{8,3},{9,3} }) == 6.0);
    BOOST_TEST(VerticalLine::find_vertical_x({ {3,3},{4,3},{5,3},{7,3},{8,3},{10,3} })
               == numeric_limits<double>::infinity());
}
