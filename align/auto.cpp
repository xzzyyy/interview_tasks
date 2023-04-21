#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "../align/auto.hpp"

BOOST_AUTO_TEST_CASE(test_directions)
{
    Auto a;

    BOOST_TEST(a.state() == "^");
    BOOST_TEST(a.turn_left() == "<");
    BOOST_TEST(a.turn_right() == "^");
    BOOST_TEST(a.turn_right() == ">");
    BOOST_TEST(a.turn_right() == "v");
    BOOST_TEST(a.turn_right() == "<");
    BOOST_TEST(a.turn_left() == "v");
}

BOOST_AUTO_TEST_CASE(test_beep)
{
    Auto a;

    BOOST_TEST(a.should_beep() == "^ beep");

    a.turn_right();
    BOOST_TEST(a.should_beep() == "> beep");

    a.turn_left();
    BOOST_TEST(a.should_beep() == "^ beep");

    BOOST_TEST(a.state() == "^");
}
