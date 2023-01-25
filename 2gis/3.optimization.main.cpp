#include <iostream>
#include <string>
#include <chrono>
#include <execution>
#include <stdexcept>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <windows.h>
#include <psapi.h>
#include "3.optimization.hpp"
#include "../TimeSpent.hpp"
using namespace std;

double megabytes(size_t bytes)
{
    return bytes * 1.0 / 1024.0 / 1024.0;
}

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

        auto handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());
        PROCESS_MEMORY_COUNTERS mem_counters;

        {
            auto res = opt.generator_space(size);
            GetProcessMemoryInfo(handle, &mem_counters, sizeof(mem_counters));
            cout << "res[666]: " << res[666] << "; peak WS: " << megabytes(mem_counters.PeakWorkingSetSize) << endl;
        }

        {
            check_time.start();
            auto res = opt.generator(size);
            check_time.stop();
            GetProcessMemoryInfo(handle, &mem_counters, sizeof(mem_counters));
            cout << "unopt | ms: " << check_time.spent()
                 << "; res[666]: " << res[666] << "; peak WS: " << megabytes(mem_counters.PeakWorkingSetSize) << endl;
        }

        {
            check_time.start();
            auto res = opt.generator_speed(size);
            check_time.stop();
            GetProcessMemoryInfo(handle, &mem_counters, sizeof(mem_counters));
            cout << "opt | ms: " << check_time.spent()
                 << "; res[666]: " << res[666] << "; peak WS: " << megabytes(mem_counters.PeakWorkingSetSize) << endl;
        }

        CloseHandle(handle);
    }
}
