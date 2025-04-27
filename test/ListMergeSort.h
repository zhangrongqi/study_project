#pragma once
#include <iostream>

namespace ListMergeSort
{
    struct ListNode {
        int val;
        ListNode* next;
        ListNode(int x) : val(x), next(nullptr) {}
    };

    // 合并两个有序链表
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

    // 使用快慢指针找到链表中点
    ListNode* findMiddle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head->next;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    // 归并排序主函数
    ListNode* mergeSort(ListNode* head) {
        if (!head || !head->next) return head;

        // 找到链表中点
        ListNode* mid = findMiddle(head);
        ListNode* right = mid->next;
        mid->next = nullptr; // 分割链表

        // 递归排序左右部分
        ListNode* leftSorted = mergeSort(head);
        ListNode* rightSorted = mergeSort(right);

        // 合并有序链表
        return merge(leftSorted, rightSorted);
    }

    // 打印链表
    void printList(ListNode* head) {
        while (head) {
            std::cout << head->val << " ";
            head = head->next;
        }
        std::cout << std::endl;
    }

    //// 测试代码
    //int main() {
    //    // 创建示例链表: 4->2->1->3
    //    ListNode* head = new ListNode(4);
    //    head->next = new ListNode(2);
    //    head->next->next = new ListNode(1);
    //    head->next->next->next = new ListNode(3);

    //    std::cout << "Original list: ";
    //    printList(head);

    //    head = mergeSort(head);

    //    std::cout << "Sorted list:  ";
    //    printList(head);

    //    // 释放内存（实际使用时需要）
    //    while (head) {
    //        ListNode* temp = head;
    //        head = head->next;
    //        delete temp;
    //    }

    //    return 0;
    //}
}