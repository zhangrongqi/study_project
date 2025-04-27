#pragma once
#include <algorithm>

namespace ShellSort
{
	template<typename T>
	void shellSort(T* arr, size_t arrLength)
	{
		if (arrLength < 2)
			return;

		for (size_t gap = arrLength / 2; gap > 0; gap /= 2)
		{
			for (size_t i = gap; i < arrLength; ++i)
			{
				T key = arr[i];
				size_t j = i - gap;

				while (j >= 0 && arr[j] > key)
				{
					arr[j + gap] = arr[j];
					j -= gap;
				}

				arr[j + gap] = key;
			}
		}
	}
}