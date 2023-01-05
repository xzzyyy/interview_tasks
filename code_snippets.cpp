// new and delete array syntax
#include <iostream>
using namespace std;

int main()
{
    int* arr = new int[3];
    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;
    
    cout << arr[0] << ' ' << arr[1] << ' ' << arr[2] << endl;
    
    delete[] arr;
}



// operators inside class
#include <iostream>
using namespace std;

struct SuperInt
{
    int x;
    
    SuperInt& operator+=(const SuperInt& superInt)
    {
        x += superInt.x;
        return *this;
    }
    SuperInt& operator*=(int r)
    {
        x *= r;
        return *this;
    }
    
	SuperInt(int x):
        x(x)
    {
    }
};

int main()
{
    SuperInt superInt1(1), superInt2(2);
    
    superInt1 += superInt2;
    cout << superInt1.x << endl;
    
    superInt1 *= 3;
    cout << superInt1.x << endl;
}



// creating threads
// each thread has its own stack for every function
// it's impossible to have address of "reference variable" (because it is alias)
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

string str = "gopa";

void func()
{
    thread::id th_id = this_thread::get_id();
    const string& s_ref = str;
    
    this_thread::sleep_for(1s);
    cout << th_id << ' ' << &th_id << ' ' << &s_ref << endl;
    this_thread::sleep_for(1s);
    cout << th_id << ' ' << &th_id << ' ' << &s_ref << endl;
    this_thread::sleep_for(1s);
    cout << th_id << ' ' << &th_id << ' ' << &s_ref << endl;
}

int main()
{
    thread t1(func), t2(func);
    t1.join();
    t2.join();
}



// temporary cannot be bound to non-const reference
#include <iostream>
using namespace std;
 
int subscribe(string& sub, const string& sessionId)		// try string&
{
    return (sub += sessionId).length() > 5 ? 5 : 0;
}

int main(void) {
    string range = "0G";
    string first = "lalala";
    cout << subscribe(first, string("superbook_") + range) << endl;
}



// aggregate initialization of simple class type
#include <iostream>
using namespace std;

int main(void) {
    struct LevelData { double _p; int _s; }; LevelData ld = { 1.1, 2 };  
    
    cout << ld._p << endl;
    cout << ld._s << endl;
}



// comparator function for algorithm inside class
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct PriceLevel
{
    double p;
    int s;
};

struct OrderBook
{
    typedef vector<PriceLevel> LevelsType;
    LevelsType v;
  
    OrderBook();  
    static bool cmp(const PriceLevel& l, const PriceLevel& r);
    void f();
};

OrderBook::OrderBook()
{
    PriceLevel l1 = { 1.0, 1 };
    PriceLevel l2 = { 2.0, 2 };
    PriceLevel l3 = { 3.0, 3 };
    v.push_back(l1);
    v.push_back(l2);
    v.push_back(l3);
}

bool OrderBook::cmp(const PriceLevel& l, const PriceLevel& r)
{
    return l.p < r.p;
}

void OrderBook::f()
{
    PriceLevel pl = { 1.9, 1 };
    LevelsType::iterator lvl = upper_bound(v.begin(), v.end(), pl, cmp);	// cmp should be static
    if (lvl == v.end())
        cout << "last" << endl;
    else
    {
        cout << lvl->p << endl;
        cout << lvl->s << endl;
    }
}

int main(void) {
    OrderBook ob;
    ob.f();
}



// implicit assignment operator copies array types
#include <iostream>
using namespace std;

struct S
{
    int arr[2];
};

int main(void) {
    S s;
    s.arr[0] = 111;
    s.arr[1] = 222;
    
    S copy = s;
    cout << copy.arr[0] << ", " << copy.arr[1] << endl;
}
