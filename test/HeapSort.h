#pragma once
#include <iostream>
using namespace std;

namespace HeapSort
{
    // 非递归版本的 heapify 函数
    void heapify(int arr[], int n, int i) {
        int current = i;       // 当前需要调整的节点
        while (true) {
            int largest = current;     // 初始化最大值为当前节点
            int left = 2 * current + 1; // 左子节点
            int right = 2 * current + 2;// 右子节点

            // 如果左子节点存在且大于当前最大值
            if (left < n && arr[left] > arr[largest])
                largest = left;

            // 如果右子节点存在且大于当前最大值
            if (right < n && arr[right] > arr[largest])
                largest = right;

            // 如果最大值不是当前节点，交换并继续调整
            if (largest != current) {
                swap(arr[current], arr[largest]);
                current = largest;  // 更新当前节点为交换后的子节点
            }
            else {
                break;  // 如果当前节点已满足堆性质，退出循环
            }
        }
    }

    // 堆排序主函数
    void heapSort(int arr[], int n) {
        // 构建最大堆（从最后一个非叶子节点开始调整）
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        // 逐个提取堆顶元素（最大值）并调整堆
        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);  // 将当前最大值移到数组末尾
            heapify(arr, i, 0);    // 调整剩余元素为最大堆
        }
    }

    //// 测试代码
    //int main() {
    //    int arr[] = { 12, 11, 13, 5, 6, 7 };
    //    int n = sizeof(arr) / sizeof(arr[0]);
    //
    //    heapSort(arr, n);
    //
    //    cout << "Sorted array: \n";
    //    for (int i = 0; i < n; ++i)
    //        cout << arr[i] << " ";
    //    cout << endl;
    //
    //    return 0;
    //}
}