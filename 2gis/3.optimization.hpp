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
			}
		}
		int operator()(int res_idx)
		{
			int size = prev(sub_arr_beg.cend())->second + static_cast<int>(sub_arr_beg.size());
			if (res_idx < 0)
				throw std::underflow_error(std::string("required idx [") + std::to_string(res_idx) + 
										   "] is less than 0");
			if (res_idx >= size)
				throw std::overflow_error(std::string("required idx [") + std::to_string(res_idx) + 
										  "] is more than total array size [" + std::to_string(size) + "]");
			
			int idx = sub_arr_beg.lower_bound(res_idx)->second;
			int sub_idx = res_idx - idx;
			
			if (sub_idx == 0)
				return idx;
			else
				return (sub_idx - 1) * idx;
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

	Gen generator_space(const int count)
	{
		return Gen(count);
	}
};

#endif

// для каких бы значений ты бы написал юнит-тесты?
// 0, 1, max_value, -1
