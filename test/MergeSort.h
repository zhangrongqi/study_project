#pragma once

namespace MergeSort
{
	void merge(int* arr, int begin, int middle, int end)
	{
		int i = begin;
		int j = middle + 1;

		int* tempArr = new int[end - begin + 1];

		int tempArrIndex = 0;

		while (i <= middle && j <= end)
		{
			if (arr[i] < arr[j])
			{
				tempArr[tempArrIndex++] = arr[i++];
			}
			else
			{
				tempArr[tempArrIndex++] = arr[j++];
			}
		}

		while (i <= middle)
		{
			tempArr[tempArrIndex++] = arr[i++];
		}

		while (j <= end)
		{
			tempArr[tempArrIndex++] = arr[j++];
		}

		for (i = begin, tempArrIndex = 0; i <= end; i++, tempArrIndex++)
		{
			arr[i] = tempArr[tempArrIndex];
		}

		delete[] tempArr;
	}

	void mergeSort(int* arr, int begin, int end)
	{
		if (begin < end)
		{
			int middle = (begin + end) / 2;
			mergeSort(arr, begin, middle);
			mergeSort(arr, middle + 1, end);
			merge(arr, begin, middle, end);
		}
	}
}