#include <iostream>
#include <boost/test/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>
#include "CoutRedirect.hpp"
using namespace std;

template<class T> struct A
{
    A() = default;
    int f() const { return data.get(); }
    int f() { return data.inc(); }
    const char* c_str() const { return data.c_str(); }      // not an error (SFINAE) because it was not called anywhere
    
    T data;
};

struct B
{
    int inc() { return i++; }
    int get() const { return i; }
    
    int i = 0;
};

void print(int a, int b, int c)
{
    cout << a << ' ' << b << ' ' << c << '\n';
}

BOOST_AUTO_TEST_CASE(templates)
{
    A<B> a;
    auto& a_ref = a;
    const auto& a_cref = a;
    
    boost::test_tools::output_test_stream testout;
    {
        CoutRedirect redirect(testout.rdbuf());
        print(a_ref.f(), a_cref.f(), a.data.i);     // execution order can be any
    }
    
    // a_ref.f()              | a == 0    | a_cref.f() or a.data.i | b, c == 0 | a_cref.f() | a, b == 0
    // a_cref.f() or a.data.i | b, c == 1 | a_ref.f()              | a ==    0 | a.data.i   | c == 0
    // a.data.i or a_cref.f() | c, b == 1 | a.data.i or a_cref.f() | c, b == 1 | a_ref.f()  | b, a == 0
    
    // a 0 0 0 0
    // b 1 0 1 0
    // c 1 1 0 0

    BOOST_CHECK(
        testout.is_equal("0 1 1\n", false) ||
        testout.is_equal("0 0 1\n", false) ||
        testout.is_equal("0 1 0\n", false) ||
        testout.is_equal("0 0 0\n", false)
    );
    testout.flush();
}
