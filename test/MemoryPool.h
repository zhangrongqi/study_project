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
        // 静态断言，比较T和viod*大小，T的size必须 >= void*的size
        static_assert(sizeof(T) >= sizeof(void*), "sizeof(T) must be at least sizeof(void*)");
        // 初始化内存池内存
        expandPool();
    }

    ~FixedSizeMemoryPool() {
        // 通过迭代器释放blocks容器中的内存
        for (auto block : blocks_) {
            ::operator delete(block);
        }
    }

    T* allocate() {
        std::lock_guard<std::mutex> lock(mutex_);
        // 如果freeList_为nullptr，代表内存池已空，需要扩充内存池
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

    size_t nodesPerBlock_;      // 每个内存块可存储的对象数量
    void* freeList_;            // 空闲链表头
    std::vector<void*> blocks_; // 所有已分配的内存块
    std::mutex mutex_;          // 线程安全锁
};

// 测试代码
struct Test {
    int data;
    Test(int d) : data(d) {}
};

//int main() {
//    FixedSizeMemoryPool<Test> pool(10);
//
//    Test* t1 = pool.allocate();
//    new (t1) Test(42);  // 使用placement new构造对象
//    std::cout << t1->data << std::endl;
//
//    t1->~Test();        // 显式调用析构函数
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