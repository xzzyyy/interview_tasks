#include <iostream>

struct A
{
    A() { std::cout << "A "; }
    A(const A &) { std::cout << "A_copy "; }
    A(A &&) { std::cout << "A_move "; }
    
    int data = 0;
};

struct B
{
    B() { std::cout << "B "; }
    B(const B & other)
        : value(other.value)
    {
        std::cout << "B_copy ";
    }
    B(B && other)
        : value(other.value)
    {
        std::cout << "B_move ";
    }
    
    A value;
};

void out_b(B && b)
{
    std::cout << b.value.data;
}

int main()
{
    B b1;
    std::cout << "\n";
    
    B b2(b1);
    std::cout << "\n";
    
    B b3(std::move(b1));
    std::cout << "\n";
    
    out_b(std::move(b3));
    std::cout << "\n";
    
    return 0;
}
