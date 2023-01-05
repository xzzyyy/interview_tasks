#include <iostream>

template <class T>
struct A
{
    A() = default;
    
    int f() const { return data.get(); }
    int f() { return data.inc(); }
    const char * c_str() const { return data.c_str(); }
    
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
    std::cout << a << ' ' << b << ' ' << c << std::endl;
}

int main()
{
    A<B> a;
    auto & a_ref = a;
    const auto & a_cref = a;
    
    print(a_ref.f(), a_cref.f(), a.data.i);
    
    return 0;
}
