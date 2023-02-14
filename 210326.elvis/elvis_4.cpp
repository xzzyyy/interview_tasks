//////////////////////////////////
// 4. Что напечатает?
//////////////////////////////////


//////////////////////////////////
// a.h
//////////////////////////////////

struct A
{
	virtual void func1() const;
	void func2() const;
	virtual void func3() const;
};

struct B: public A
{
	void func1() const;
	void func2() const;
	void func3() const override;
};

A * CreateImpl();


//////////////////////////////////
// a.cpp
//////////////////////////////////

// #include "a.h"
#include <iostream>

A * CreateImpl()
{
	return new B;
}

void A::func1() const
{
	std::cout << "A::func1" << " ";
	func2();
}

void A::func2() const
{
	std::cout << "A:func2" << " ";
	func3();
}

void A::func3() const
{
	std::cout << "A::func3" << " ";
}

void B::func1() const
{
	std::cout << "B::func1" << " ";
	A::func1();
}

void B::func2() const
{
	std::cout << "B::func2" << " ";
	func3();
}

void B::func3() const
{
	std::cout << "B::func3" << " ";
}


//////////////////////////////////
// main.cpp
//////////////////////////////////

// #include "a.h"
#include <memory>

int main( int argc, char ** argv)
{ 
	std::unique_ptr<A> a( CreateImpl() ); 
	a->func1(); 
	return 0;
}

// B::func1 A::func1 A::func2 B::func3
