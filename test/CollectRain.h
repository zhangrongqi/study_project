#pragma once
#include <vector>
#include <iostream>

int collectRain_1(std::vector<int> p_collector)
{
	std::vector<int> forward_arr(p_collector.size(), 0);
	std::vector<int> reverse_arr(p_collector.size(), 0);

	int maxNum = 0;

	for (int i = 0; i < p_collector.size(); ++i)
	{
		maxNum = std::max(maxNum, p_collector[i]);
		forward_arr[i] = maxNum;
	}

	maxNum = 0;

	for (int j = static_cast<int>(p_collector.size() - 1); j >= 0; --j)
	{
		maxNum = std::max(maxNum, p_collector[j]);
		reverse_arr[j] = maxNum;
	}

	int sumNum = 0;

	for (int index = 0; index < p_collector.size(); ++index)
	{
		sumNum += (std::min(forward_arr[index], reverse_arr[index]) - p_collector[index]);
	}

	return sumNum;
}

int collectRain_2(std::vector<int> p_collector)
{
	int sumNum = 0;

	return sumNum;
}