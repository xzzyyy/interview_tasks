#ifndef _3_OPTIMIZATION_HPP
#define _3_OPTIMIZATION_HPP

#include <vector>
#include <random>
#include <numeric>
#include <execution>
#include <thread>		// this_thread
#include <mutex>		// mutex
#include <chrono>		// chrono::milliseconds
#include <limits>		// numeric_limits<...>

struct Optimization
{
	// it's not specified if `func` is it pure (чистая) function, or not, so we must treat it as not pure
	static bool func(int i)
	{
		return i % 2 == 1;
	}

	std::vector<int> generator(const int count)
	{
		std::vector<int> result;
		for (int i = 0; i < count; ++i)
		{
			result.push_back(i);
			
			for (int j = 0; j < count; ++j)
				if (func(i))
					result.push_back(i * j);
		}
		return result;
	}

	// предложить оптимизации по производительности и по потреблению памяти
	template<class ExPol> std::vector<int> generator_speed(ExPol&& ex_pol, const int count)
	{
		std::vector<int> res(count * (count + 1));
		int sq_filled = 0;

        std::vector<int> plus_one_row(count);
        iota(plus_one_row.begin(), plus_one_row.end(), 0);

		for (int i = 0; i < count; ++i)
		{
		    res[sq_filled++] = i;
			if (!func(i))
				continue;

            transform(ex_pol, plus_one_row.cbegin(), plus_one_row.cend(),
					  res.begin() + sq_filled, [i](const int src_val){ return src_val * i; });
			sq_filled += count;
        }

		res.resize(sq_filled);
        return res;
	}

	// std::vector<int> generator_memory(int idx)
	// {
	// 	static std::vector<bool> func_value;
		
	// 	// ?
		
	// 	return result;
	// }
};

// для каких бы значений ты бы написал юнит-тесты?
// 0, 1, max_value, -1

#endif
