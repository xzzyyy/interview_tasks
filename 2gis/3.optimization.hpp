#ifndef _3_OPTIMIZATION_HPP
#define _3_OPTIMIZATION_HPP

#include <vector>
#include <map>
#include <random>
#include <numeric>
#include <execution>
#include <thread>		// this_thread
#include <mutex>		// mutex
#include <chrono>		// chrono::milliseconds
#include <limits>		// numeric_limits<...>
#include <stdexcept>	// overflow_error

struct Optimization
{
	struct Gen
	{
		Gen(int count)
		{
			int last_idx = 0;
			for (int i = 0; i < count; ++i)
			{
				sub_arr_beg[last_idx] = i;
				last_idx += func(i) ? count + 1 : 1;
			}												// i: 0, [0, 0], 1
															// i: 1, [1, 1], 102
															// i: 2, [102, 2], 103
		}
		int operator()(int res_idx)
		{
			int size = prev(sub_arr_beg.cend())->first + 1 + static_cast<int>(sub_arr_beg.size());
			if (res_idx < 0)
				throw std::underflow_error(std::string("required idx [") + std::to_string(res_idx) + 
										   "] is less than 0");
			if (res_idx >= size)
				throw std::overflow_error(std::string("required idx [") + std::to_string(res_idx) + 
										  "] is more than total array size [" + std::to_string(size) + "]");
			
			int subarr_start = prev(sub_arr_beg.upper_bound(res_idx))->first;
			int row_idx = prev(sub_arr_beg.upper_bound(res_idx))->second;
			int sub_idx = res_idx - subarr_start;
			
			return sub_idx == 0 ? row_idx : (sub_idx - 1) * row_idx;
		}
	private:
		std::map<int, int> sub_arr_beg;
	};

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
	std::vector<int> generator_speed(const int count)
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

            transform(std::execution::par, plus_one_row.cbegin(), plus_one_row.cend(),
					  res.begin() + sq_filled, [i](const int src_val){ return src_val * i; });
			sq_filled += count;
        }

		res.resize(sq_filled);
        return res;
	}

	Gen generator_space(const int count)
	{
		return Gen(count);
	}
};

#endif
