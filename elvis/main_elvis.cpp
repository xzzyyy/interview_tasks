#include <iostream>
#include <thread>
#include "elvis.hpp"
using namespace std;

void print_help()
{
    cerr << "elvis <input-folder-path>" << endl;
}

int main(int argc, const char* argv[])
{
    try
    {
        check_args(argc, argv);
        parallel_process(argv[1]);
        return 0;
    }
    catch (const exception& exc)
    {
        cerr << "ERROR" << endl;
        for (int i = 0; i < argc; ++i)
            cerr << "argv" << i << ": " << argv[i] << endl;
        cerr << "exc: " << exc.what() << endl;
        print_help();
        return 1;
    }
}