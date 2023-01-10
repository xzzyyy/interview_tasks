#define BOOST_TEST_MODULE test_elvis
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "elvis.hpp"
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

BOOST_AUTO_TEST_CASE(args)
{
    const char* test_argv[] = { "elvis" };
    BOOST_REQUIRE_EXCEPTION(check_args(1, test_argv), invalid_argument,
                            [](const invalid_argument& exc){ return exc.what() == string(ERR_WRONG_ARGUMENTS_NUM); });
    BOOST_REQUIRE_EXCEPTION(parallel_process("test/666.txt"), invalid_argument, 
                            [](const invalid_argument& exc){ return exc.what() == string(ERR_PATH_NOT_EXIST); });
    BOOST_REQUIRE_EXCEPTION(parallel_process("test/1.txt"), invalid_argument, 
                            [](const invalid_argument& exc){ return exc.what() == string(ERR_PATH_NOT_DIR); });
}