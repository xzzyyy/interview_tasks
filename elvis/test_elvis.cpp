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
    const char* test_argv[] = {"elvis"};
    BOOST_REQUIRE_EXCEPTION(check_args(1, test_argv), invalid_argument,
                            [](const invalid_argument& exc){ return exc.what() == string(ERR_WRONG_ARGUMENTS_NUM); });
    BOOST_REQUIRE_EXCEPTION(parallel_process("test/666.txt"), invalid_argument, 
                            [](const invalid_argument& exc){ return exc.what() == string(ERR_PATH_NOT_EXIST); });
    BOOST_REQUIRE_EXCEPTION(parallel_process("test/1.txt"), invalid_argument, 
                            [](const invalid_argument& exc){ return exc.what() == string(ERR_PATH_NOT_DIR); });
}

BOOST_AUTO_TEST_CASE(one_sep_part_of_another)
{
    Parser parser;
    parser.add_text("1,22;333;4");
    parser.add_sep(",");
    parser.add_sep(";");
    parser.add_sep(";3");
    vector<string> expected = {"1", "22", "33", "4"},
                   actual = parser.parse();
    BOOST_TEST(expected == actual);
}

BOOST_AUTO_TEST_CASE(two_sep_in_row)
{
    Parser parser;
    parser.add_text("1,,22");
    parser.add_sep(",");
    vector<string> expected = {"1", "22"},
                   actual = parser.parse();
    BOOST_TEST(expected == actual);
}

BOOST_AUTO_TEST_CASE(one_file)
{
    vector<string> expected;
    ifstream exp_stream("test/1_out.txt");
    string item;
    exp_stream >> item;
    while (exp_stream)
    {
        expected.push_back(item);
        exp_stream >> item;
    }

    vector<string> actual = process_file("test/1.txt");
    BOOST_TEST(expected == actual);
    
    for (const auto& str : expected)
        cerr << str << " ";
    cerr << endl;
    for (const auto& str : actual)
        cerr << str << " ";
    cerr << endl;
}
