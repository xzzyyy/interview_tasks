#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "../align/auto.h"

BOOST_AUTO_TEST_CASE(TestAuto)
{
	Auto a;

	BOOST_TEST(a.get_state() == "^");
	BOOST_TEST(a.turn_left() == '<');
	BOOST_TEST(a.turn_right() == '^');
	BOOST_TEST(a.turn_right() == '>');
	BOOST_TEST(a.turn_right() == 'v');
	BOOST_TEST(a.turn_right() == '<');
	BOOST_TEST(a.turn_left() == 'v');

	a.should_beep();
	BOOST_TEST(a.get_state() == "v beep");
	a.new_cycle();
	BOOST_TEST(a.get_state() == "v");
}
