#pragma once
#include <iostream>

namespace ListMergeSort
{
    struct ListNode {
        int val;
        ListNode* next;
        ListNode(int x) : val(x), next(nullptr) {}
    };

    // �ϲ�������������
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            }
            else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }

    // ʹ�ÿ���ָ���ҵ������е�
    ListNode* findMiddle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head->next;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    // �鲢����������
    ListNode* mergeSort(ListNode* head) {
        if (!head || !head->next) return head;

        // �ҵ������е�
        ListNode* mid = findMiddle(head);
        ListNode* right = mid->next;
        mid->next = nullptr; // �ָ�����

        // �ݹ��������Ҳ���
        ListNode* leftSorted = mergeSort(head);
        ListNode* rightSorted = mergeSort(right);

        // �ϲ���������
        return merge(leftSorted, rightSorted);
    }

    // ��ӡ����
    void printList(ListNode* head) {
        while (head) {
            std::cout << head->val << " ";
            head = head->next;
        }
        std::cout << std::endl;
    }

    //// ���Դ���
    //int main() {
    //    // ����ʾ������: 4->2->1->3
    //    ListNode* head = new ListNode(4);
    //    head->next = new ListNode(2);
    //    head->next->next = new ListNode(1);
    //    head->next->next->next = new ListNode(3);

    //    std::cout << "Original list: ";
    //    printList(head);

    //    head = mergeSort(head);

    //    std::cout << "Sorted list:  ";
    //    printList(head);

    //    // �ͷ��ڴ棨ʵ��ʹ��ʱ��Ҫ��
    //    while (head) {
    //        ListNode* temp = head;
    //        head = head->next;
    //        delete temp;
    //    }

    //    return 0;
    //}
}