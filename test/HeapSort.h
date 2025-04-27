#pragma once
#include <iostream>
using namespace std;

namespace HeapSort
{
    // �ǵݹ�汾�� heapify ����
    void heapify(int arr[], int n, int i) {
        int current = i;       // ��ǰ��Ҫ�����Ľڵ�
        while (true) {
            int largest = current;     // ��ʼ�����ֵΪ��ǰ�ڵ�
            int left = 2 * current + 1; // ���ӽڵ�
            int right = 2 * current + 2;// ���ӽڵ�

            // ������ӽڵ�����Ҵ��ڵ�ǰ���ֵ
            if (left < n && arr[left] > arr[largest])
                largest = left;

            // ������ӽڵ�����Ҵ��ڵ�ǰ���ֵ
            if (right < n && arr[right] > arr[largest])
                largest = right;

            // ������ֵ���ǵ�ǰ�ڵ㣬��������������
            if (largest != current) {
                swap(arr[current], arr[largest]);
                current = largest;  // ���µ�ǰ�ڵ�Ϊ��������ӽڵ�
            }
            else {
                break;  // �����ǰ�ڵ�����������ʣ��˳�ѭ��
            }
        }
    }

    // ������������
    void heapSort(int arr[], int n) {
        // �������ѣ������һ����Ҷ�ӽڵ㿪ʼ������
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        // �����ȡ�Ѷ�Ԫ�أ����ֵ����������
        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);  // ����ǰ���ֵ�Ƶ�����ĩβ
            heapify(arr, i, 0);    // ����ʣ��Ԫ��Ϊ����
        }
    }

    //// ���Դ���
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