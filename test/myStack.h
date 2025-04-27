#pragma once

template<class T>
class myStack
{
private:
	T* m_pData; // data pointer
	size_t m_stackSize;
	int m_stackTop;

public:
	myStack(size_t p_stackSize) : m_stackSize(p_stackSize), m_stackTop(0)
	{
		m_pData = new T[p_stackSize];
	}

	~myStack()
	{
		delete[] m_pData;

		m_pData = nullptr;
	}

	bool isEmpty() const
	{
		return 0 == m_stackTop;
	};

	bool isFull() const
	{
		return m_stackTop == m_stackSize;
	};

	bool pop(T& p_popData)
	{
		if (isEmpty())
			return false;

		p_popData = m_pData[--m_stackTop];

		return true;

	};

	bool push(const T& p_pushData)
	{
		if (isFull())
			return false;

		m_pData[m_stackTop] = p_pushData;

		++m_stackTop;

		return true;
	};
};

#include <iostream> // 包含头文件。
using namespace std; // 指定缺省的命名空间。
template <class T, int len = 10>
class Array
{
private:T items[len]; // 数组元素。
public:Array() { len = 5; } // 默认构造函数。
	  ~Array() {} // 析构函数
	  T& operator[](int ii) { return items[ii]; } // 重载操作符[]，可以修改数组中的元素。
	  const T& operator[](int ii) const { return items[ii]; } // 重载操作符[]，不能修改数组中的元素。
};


template <typename T>
void testFunc(T& p_param)
{

}

template <>
void testFunc <int>(int& p_param)
{

}

