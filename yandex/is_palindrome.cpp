// Palindrome

#include <string>
#include <cctype>

#define BOOST_TEST_MODULE test_yandex
#include <boost/test/included/unit_test.hpp>

bool IsPalindrome(const std::string& str) {
    size_t len = str.length();

    if (len == 0)
        return true;
    
    size_t l = 0;
    size_t r = len - 1;

    do
    {
        while (l < r && !std::isalnum(static_cast<unsigned char>(str[l])))
            ++l;
        while (l < r && !std::isalnum(static_cast<unsigned char>(str[r])))
            --r;
        if (l == r)
            return true;

        if (std::tolower(static_cast<unsigned char>(str[l])) != std::tolower(static_cast<unsigned char>(str[r])))
            return false;

        if (r - l <= 2)
            break;

        ++l;
        --r;
    }
    while (true);

    return true;
}

// ""               true
// "a"              true
// "aga"            true
// "agb"            false
// ",,,"            true
// ",,."            true
// ",a,"            true
// ",,,aaa"         true
// ".,aa.b,a.a"     true

BOOST_AUTO_TEST_CASE(is_palindrome)
{
    BOOST_TEST(IsPalindrome(""));
    BOOST_TEST(IsPalindrome("a"));
    BOOST_TEST(IsPalindrome("aga"));
    BOOST_TEST(!IsPalindrome("agb"));
    BOOST_TEST(IsPalindrome(",,,"));
    BOOST_TEST(IsPalindrome(",,."));
    BOOST_TEST(IsPalindrome(",a,"));
    BOOST_TEST(IsPalindrome(",,,aaa"));
    BOOST_TEST(IsPalindrome(".,aa.b,a.a"));
}
