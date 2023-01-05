#include <vector>

bool func(int i);

std::vector<int> generator(const int count)
{
	std::vector<int> result;
	for (int i = 0; i < count; ++i)
	{
		result.push_back(i);
		
		for (int j = 0; j < count; ++j)
		{
			if (func(i))
			{
				result.push_back(i * j);
			}
		}
	}
	return result;
}

// предложить оптимизации по производительности и по потреблению памяти

std::vector<int> generator_speed(const int count)
{
	std::vector<int> result;
	for (int i = 0; i < count; ++i)
	{
		result.push_back(i);

		// this is possible if func is always outputting same value for same input
		if (func(i))
		{
			for (int j = 0; j < count; ++j)
			{
				result.push_back(i * j);
			}
		}
	}
	return result;
}

std::vector<int> generator_memory(int idx)
{
	static std::vector<bool> func_value;
	
	// ?
	
	return result;
}

// для каких бы значений ты бы написал юнит-тесты?
// 0, 1, max_value, -1
