///////////////////////////////
// 3. Что напечатает?
///////////////////////////////

struct A
{
	int func1( int a ) 
	{
		std::cout << "A::func1 " << a << std::endl;
		return 0;
	}
};

struct B: A
{
	virtual int func1( int a )
	{
		std::cout << "B:func1 " << a << std::endl; 
		return 0;
	}
};

int main( int argc, char ** argv )
{
	A* a = new B;
	a->func1( 1 ); 
	return 0;
}

// A::func1 1
// because A::func1 is not virtual
