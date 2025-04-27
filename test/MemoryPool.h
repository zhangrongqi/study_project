#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include <new>

template <typename T>
class FixedSizeMemoryPool {
public:
    FixedSizeMemoryPool(size_t nodesPerBlock = 1024)
        : nodesPerBlock_(nodesPerBlock), freeList_(nullptr) {
        // ��̬���ԣ��Ƚ�T��viod*��С��T��size���� >= void*��size
        static_assert(sizeof(T) >= sizeof(void*), "sizeof(T) must be at least sizeof(void*)");
        // ��ʼ���ڴ���ڴ�
        expandPool();
    }

    ~FixedSizeMemoryPool() {
        // ͨ���������ͷ�blocks�����е��ڴ�
        for (auto block : blocks_) {
            ::operator delete(block);
        }
    }

    T* allocate() {
        std::lock_guard<std::mutex> lock(mutex_);
        // ���freeList_Ϊnullptr�������ڴ���ѿգ���Ҫ�����ڴ��
        if (!freeList_) {
            expandPool();
        }
        T* result = reinterpret_cast<T*>(freeList_);
        freeList_ = *(reinterpret_cast<void**>(freeList_));
        return result;
    }

    void deallocate(T* ptr) {
        std::lock_guard<std::mutex> lock(mutex_);
        *(reinterpret_cast<void**>(ptr)) = freeList_;
        freeList_ = ptr;
    }

private:
    void expandPool() {
        size_t totalSize = nodesPerBlock_ * sizeof(T);
        void* newBlock = ::operator new(totalSize);
        blocks_.push_back(newBlock);

        char* start = static_cast<char*>(newBlock);
        for (size_t i = 0; i < nodesPerBlock_; ++i) {
            char* node = start + i * sizeof(T);
            *(reinterpret_cast<void**>(node)) = (i + 1 == nodesPerBlock_) ? nullptr : (node + sizeof(T));
        }
        freeList_ = newBlock;
    }

    size_t nodesPerBlock_;      // ÿ���ڴ��ɴ洢�Ķ�������
    void* freeList_;            // ��������ͷ
    std::vector<void*> blocks_; // �����ѷ�����ڴ��
    std::mutex mutex_;          // �̰߳�ȫ��
};

// ���Դ���
struct Test {
    int data;
    Test(int d) : data(d) {}
};

//int main() {
//    FixedSizeMemoryPool<Test> pool(10);
//
//    Test* t1 = pool.allocate();
//    new (t1) Test(42);  // ʹ��placement new�������
//    std::cout << t1->data << std::endl;
//
//    t1->~Test();        // ��ʽ������������
//    pool.deallocate(t1);
//
//    return 0;
//}


//#include <iostream>
//#include <vector>
//#include <mutex>
//#include <new>
//template<class T>
//class myMemoryPool
//{
//public:
//    myMemoryPool(size_t p_nodePreBlock) :
//        m_nodePreBlock(p_nodePreBlock), m_freeNode(nullptr)
//    {
//        //static_assert();
//        expandPool();
//    }
//    ~myMemoryPool()
//    {
//        for (auto it : m_blocks)
//            ::operator delete(it);
//    }
//
//    T* allocate()
//    {
//        std::lock_guard<m_lock> Lock;
//
//        if (nullptr == m_freeNode)
//        {
//            expandPool();
//        }
//
//        T* res = reinterpret_cast<T*> (m_freeNode);
//        m_freeNode = *(reinterpret_cast<void**> (m_freeNode));
//
//        return res;
//    }
//
//    void deallocate(T* p_obj)
//    {
//        std::lock_guard<std::mutex> Lock;
//        *(reinterpret_cast<void**> (p_obj)) = m_freeNode;
//        m_freeNode = p_obj;
//    }
//
//private:
//    void expandPool()
//    {
//        void* newBlock = ::operator new(sizeof(T) * m_nodePreBlock);
//
//        char* start = reinterpret_cast<char*> (newBlock);
//
//        for (int i = 0; i < m_nodePreBlock; ++i)
//        {
//            char* node = start + i * sizeof(T);
//            *(reinterpret_cast<void**> node) = ((i + 1) == m_nodePreBlock) ? nullptr : (node + sizeof(T));
//        }
//
//        m_freeNode = start;
//    }
//
//    size_t m_nodePreBlock;
//    void* m_freeNode;
//    std::vector<void*> m_blocks;
//    std::mutex m_lock;
//};