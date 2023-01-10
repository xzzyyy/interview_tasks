#include "elvis.hpp"
#include <iostream>
using namespace std;

void print_help()
{
    cout << "elvis_neotek <input-folder> <output-file>" << endl;
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        cerr << "ERROR: 2 parameters should be passed" << endl;
        print_help();
        return EINVAL;
    }

    filesystem::path in_folder(argv[1]);
    if (!filesystem::exists(in_folder))
    {
        cerr << "ERROR: input folder doesn't exist" << endl;
        return ENOENT;
    }

    ofstream out_f(argv[2]);
    if (!out_f)
    {
        cerr << "ERROR: can't create output file" << endl;
        return EIO;
    }

    parallel_process(in_folder, out_f);

    return 0;
}