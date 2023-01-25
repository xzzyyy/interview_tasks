#include <iostream>
#include <string>
#include <chrono>
#include <execution>
#include <stdexcept>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "3.optimization.hpp"
using namespace std;

struct TimeSpent
{
    TimeSpent()
        : start(chrono::high_resolution_clock::now())
    {

    }

    ~TimeSpent()
    {
        int ms = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count();
        cout << "exec_time (ms): " << ms << endl;
    }

    chrono::time_point<chrono::high_resolution_clock> start;
};

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

        cout << "src | ";
        {
            TimeSpent check_time;
            opt.generator(size);
        }

        cout << "for, par | ";
        {
            TimeSpent check_time;
            opt.generator_speed(/* execution::par, */ size);
        }

        /* cout << "for, par_unseq | ";
        {
            TimeSpent check_time;
            opt.generator_speed(execution::par_unseq, size);
        } */
    }
}
