#pragma once

namespace InsertionSort
{
	template<typename T>
	void insertionSort(T* arr, size_t arrLength)
	{
		if (arrLength < 2)
			return;

		for (size_t i = 1; i < arrLength; ++i)
		{
			T key = arr[i];
			size_t j = i - 1;

			while (j >= 0 && arr[j] > key)
			{
				arr[j + 1] = arr[j];
				--j;
			}

			arr[j + 1] = key;
		}
	}
}