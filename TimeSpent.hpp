#ifndef TIMESPENT_HPP
#define TIMESPENT_HPP

#include <chrono>
#include <stdexcept>

struct TimeSpent
{
    TimeSpent()
        : res_ms(-2)
    {
        
    }
    void start()
    {
        res_ms = -1;
        start_ts = std::chrono::high_resolution_clock::now();
    }
    void stop()
    {
        if (res_ms == -2)
            throw std::runtime_error("Stopwatch was not started");
        res_ms = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::high_resolution_clock::now() - start_ts)
            .count();
    }
    int spent() const
    {
        if (res_ms < 0)
            throw std::runtime_error("Stopwatch was not started/stopped");
        return res_ms;
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_ts;
    int res_ms;
};

#endif
