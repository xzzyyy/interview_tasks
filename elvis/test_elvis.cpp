#include <stdexcept>
#include <chrono>
#define BOOST_TEST_MODULE test_elvis
#include <boost/test/included/unit_test.hpp>
#include "elvis.hpp"
using namespace std;

constexpr string_view INPUT_TEST_FILES_PATH = "elvis/test/in";
constexpr string_view OUT_TEST_FILES_PATH = "elvis/test/out";

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
                            [](const invalid_argument& exc){ return exc.what() == string{ERR_WRONG_ARGUMENTS_NUM}; });
    BOOST_REQUIRE_EXCEPTION(parallel_process(string{INPUT_TEST_FILES_PATH} + "/666_in.txt"), invalid_argument, 
                            [](const invalid_argument& exc){ return exc.what() == string{ERR_PATH_NOT_EXIST}; });
    BOOST_REQUIRE_EXCEPTION(parallel_process(string{INPUT_TEST_FILES_PATH} + "/1_in.txt"), invalid_argument, 
                            [](const invalid_argument& exc){ return exc.what() == string{ERR_PATH_NOT_DIR}; });
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
    ifstream exp_stream(string{OUT_TEST_FILES_PATH} + "/1_out.txt");
    string item;
    exp_stream >> item;
    while (exp_stream)
    {
        expected.push_back(item);
        exp_stream >> item;
    }

    vector<string> actual = process_file(string{INPUT_TEST_FILES_PATH} + "/1_in.txt");
    BOOST_TEST(expected == actual);
    
    for (const auto& str : expected)
        cerr << str << " ";
    cerr << endl;
    for (const auto& str : actual)
        cerr << str << " ";
    cerr << endl;
}

BOOST_AUTO_TEST_CASE(multithreading)
{
    using namespace chrono;

    auto beg = high_resolution_clock::now();
    parallel_process(string{INPUT_TEST_FILES_PATH}, 3u, true);
    int ms3thr = duration_cast<milliseconds>(high_resolution_clock::now() - beg).count();

    beg = high_resolution_clock::now();
    parallel_process(string{INPUT_TEST_FILES_PATH}, 1u, true);
    int ms1thr = duration_cast<milliseconds>(high_resolution_clock::now() - beg).count();

    cerr << "1 thread: " << ms1thr << endl;
    cerr << "3 threads: " << ms3thr << endl;
    BOOST_TEST(ms3thr < ms1thr / 1.1);      // only 1.1 because test data is very different in length for 
                                            // different threads
}
