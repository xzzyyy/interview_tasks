#include <iostream>
#include <memory>
#define BOOST_TEST_MODULE 2gis
#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>
#include "CoutRedirect.hpp"
using namespace std;
using namespace boost::test_tools;

// ---code------------------------------------------------

struct A
{
    A() 
    { 
        cout << "A "; 
    }

    A(const A&) 
    { 
        cout << "A_copy "; 
    }

    A(A&&) 
    { 
        cout << "A_move "; 
    }
    
// private:
    int data = 0;
};

struct B
{
    B() 
    { 
        cout << "B "; 
    }

    B(const B& other)
        : value(other.value)
    {
        cout << "B_copy ";
    }

    B(B&& other)
        : value(other.value)
    {
        cout << "B_move ";
    }
    
// private:
    A value;
};

void print_b(B&& b)
{
    cout << b.value.data << ' ';
}

// ---code------------------------------------------------

BOOST_AUTO_TEST_CASE(classes)
{
    output_test_stream testout;
    
    shared_ptr<B> b;
    {
        CoutRedirect guard(testout.rdbuf());
        b.reset(new B);
    }
    BOOST_CHECK(testout.is_equal("A B "));

    {
        CoutRedirect guard(testout.rdbuf());
        B b_copy(*b);
    }
    BOOST_CHECK(testout.is_equal("A_copy B_copy "));

    shared_ptr<B> b_move;
    {
        CoutRedirect guard(testout.rdbuf());
        b_move.reset(new B(move(*b)));
    }
    BOOST_CHECK(testout.is_equal("A_copy B_move "));

    {
        CoutRedirect guard(testout.rdbuf());
        print_b(move(*b_move));
    }
    BOOST_CHECK(testout.is_equal("0 "));
}
