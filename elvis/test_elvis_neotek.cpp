#define BOOST_TEST_MODULE test_elvis_neotek
#include <boost/test/included/unit_test.hpp>
#include "elvis_neotek.hpp"
using namespace std;

BOOST_AUTO_TEST_CASE(one_sep)
{
    Parser parser;
    parser.add_text("1,22,333");
    parser.add_sep(",");
    vector<string> expected = {"1", "22", "333"},
                   actual = parser.parse();
    BOOST_TEST(expected == actual);
}

BOOST_AUTO_TEST_CASE(two_sep)
{
    Parser parser;
    parser.add_text("1,22;333");
    parser.add_sep(",");
    parser.add_sep(";");
    vector<string> expected = {"1", "22", "333"},
                   actual = parser.parse();
    BOOST_TEST(expected == actual);
}