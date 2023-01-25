#ifndef PEAKMEMORY_HPP
#define PEAKMEMORY_HPP

#include <stdexcept>
#include <windows.h>
#include <psapi.h>

struct PeakMemory
{
    PeakMemory()
        : peak_mem(0.0)
    {
        handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());
    }
    ~PeakMemory()
    {
        CloseHandle(handle);
    }
    void note_mem_usage()
    {
        GetProcessMemoryInfo(handle, &mem_counters, sizeof(mem_counters));
        peak_mem = mem_counters.PeakWorkingSetSize;
    }
    double mega() const
    {
        if (peak_mem == 0.0)
            throw std::runtime_error("PeakMemory::note_mem_usage was never called");
        return peak_mem * 1.0 / 1024.0 / 1024.0;
    }
private:
    HANDLE handle;
    PROCESS_MEMORY_COUNTERS mem_counters;
    double peak_mem;
};

#endif
