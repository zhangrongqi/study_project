#pragma once
#include <iostream>
#include <algorithm>

using namespace std;

namespace QuickSort
{
    // ����������ѡ�����һ��Ԫ��Ϊ��׼�����ػ�׼������λ��
    int partition(int arr[], int low, int high) {
        int pivot = arr[high];  // ��׼Ԫ��
        int i = low - 1;        // С�ڻ�׼��������ĩβ����

        for (int j = low; j < high; j++) {
            // ��ǰԪ��С�ڵ��ڻ�׼ʱ�����佻�������������
            if (arr[j] <= pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        // ����׼Ԫ�طŵ���ȷλ��
        swap(arr[i + 1], arr[high]);
        return i + 1;  // ���ػ�׼λ��
    }

    // ��������������
    void quickSort(int arr[], int low, int high) {
        if (low < high) {
            // ��ȡ��׼λ��
            int pi = partition(arr, low, high);

            // �ݹ�������벿�ֺ��Ұ벿��
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    //// ʾ���÷�
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