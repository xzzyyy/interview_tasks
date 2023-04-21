#ifndef PEAKMEMORY_HPP
#define PEAKMEMORY_HPP

#if defined(_WIN32) || defined(__CYGWIN__)
#include <windows.h>
#include <psapi.h>
#elif defined(__linux__)
#include <string>
#include <string_view>
#include <fstream>
#include <boost/process.hpp>
#endif

struct PeakMemory
{
    static size_t this_process_id()
    {
#if defined(__linux__)
        std::string binary_name;
        std::ifstream("/proc/self/comm") >> binary_name;

        using namespace boost::process;
        std::string pid_str;
        {
            ipstream ps_stream;
            child ps(std::string("pidof -s ") + binary_name, std_out > ps_stream);

            pid_str = read_number(ps_stream);
            ps.wait();
        }
        return stoull(pid_str);

#elif defined(_WIN32) || defined(__CYGWIN__)
        return GetCurrentProcessId();
#endif
    }

    static double mega()
    {
        return note_mem_usage() * 1.0 / 1024.0 / 1024.0;
    }

private:

    static size_t note_mem_usage()
    {
#if defined(_WIN32) || defined(__CYGWIN__)
        PROCESS_MEMORY_COUNTERS mem_counters;
        auto handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());
        GetProcessMemoryInfo(handle, &mem_counters, sizeof(mem_counters));
        CloseHandle(handle);
        return mem_counters.PeakWorkingSetSize;

#elif defined(__linux__)
        constexpr std::string_view TMP_FN = "/tmp/peak_mem.sh";

        std::string mem_str;
        {
            std::ofstream tmp_sh{ std::string{TMP_FN}, std::ios_base::out | std::ios_base::trunc };
            tmp_sh << "#!/bin/sh" << std::endl;
            tmp_sh << "cat /proc/" << this_process_id()
                << "/status | grep 'VmPeak' | grep -E -o '[[:digit:]]+'" << std::endl;
        }
        std::system((std::string{ "chmod +x " } + std::string{ TMP_FN }).c_str());

        using namespace boost::process;
        {
            ipstream ps_stream;
            child ps{std::string{TMP_FN}, std_out > ps_stream};

            mem_str = read_number(ps_stream);
            ps.wait();
        }

        std::system((std::string{ "rm " } + std::string{ TMP_FN }).c_str());
        return stoull(mem_str) * 1024u;
#endif
    }

#if defined(__linux__)
    static std::string read_number(boost::process::ipstream& ips)
    {
        std::string line, res;
        std::getline(ips, res);
        while (ips && std::getline(ips, line) && !line.empty())
        {
            // nothing
        }
        return res;
    }
#endif
};

#endif
