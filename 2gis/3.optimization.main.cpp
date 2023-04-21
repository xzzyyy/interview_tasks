#include <iostream>
#include <string>
#include <chrono>
#include <execution>
#include <stdexcept>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "3.optimization.hpp"
#include "../TimeSpent.hpp"
#include "../PeakMemory.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
        cout << "3.optimization <size1,size2,...>" << endl;

    string all_sizes(argv[1]);
    vector<string> sizes_vec;
    
    boost::split(sizes_vec, all_sizes, boost::is_any_of(","));

    for (const string& size_str : sizes_vec)
    {
        using namespace chrono;
        int size = stoi(size_str);
        Optimization opt;
        TimeSpent check_time;
        PeakMemory mem;
        double used_mem = 0.0;

        {
            auto res = opt.generator_space(size);
            used_mem = mem.mega();
            cout << "res[666]: " << res[666] << "; peak WS: " << used_mem << endl;
        }

        {
            check_time.start();
            auto res = opt.generator(size);
            check_time.stop();
            used_mem = mem.mega();
            cout << "unopt | ms: " << check_time.spent()
                 << "; res[666]: " << res[666] << "; peak WS: " << used_mem << endl;
        }

        {
            check_time.start();
            auto res = opt.generator_speed(size);
            check_time.stop();
            used_mem = mem.mega();
            cout << "opt | ms: " << check_time.spent()
                 << "; res[666]: " << res[666] << "; peak WS: " << used_mem << endl;
        }
    }
}
