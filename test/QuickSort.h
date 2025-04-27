#pragma once
#include <iostream>
#include <algorithm>

using namespace std;

namespace QuickSort
{
    // 分区函数，选择最后一个元素为基准，返回基准的最终位置
    int partition(int arr[], int low, int high) {
        int pivot = arr[high];  // 基准元素
        int i = low - 1;        // 小于基准的子数组末尾索引

        for (int j = low; j < high; j++) {
            // 当前元素小于等于基准时，将其交换到左侧子数组
            if (arr[j] <= pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        // 将基准元素放到正确位置
        swap(arr[i + 1], arr[high]);
        return i + 1;  // 返回基准位置
    }

    // 快速排序主函数
    void quickSort(int arr[], int low, int high) {
        if (low < high) {
            // 获取基准位置
            int pi = partition(arr, low, high);

            // 递归排序左半部分和右半部分
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    //// 示例用法
    //int main() {
    //    int arr[] = { 10, 7, 8, 9, 1, 5 };
    //    int n = sizeof(arr) / sizeof(arr[0]);

    //    quickSort(arr, 0, n - 1);

    //    cout << "Sorted array: ";
    //    for (int i = 0; i < n; i++)
    //        cout << arr[i] << " ";
    //    return 0;
    //}
}