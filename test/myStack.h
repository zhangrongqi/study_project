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

#include <iostream> // ����ͷ�ļ���
using namespace std; // ָ��ȱʡ�������ռ䡣
template <class T, int len = 10>
class Array
{
private:T items[len]; // ����Ԫ�ء�
public:Array() { len = 5; } // Ĭ�Ϲ��캯����
	  ~Array() {} // ��������
	  T& operator[](int ii) { return items[ii]; } // ���ز�����[]�������޸������е�Ԫ�ء�
	  const T& operator[](int ii) const { return items[ii]; } // ���ز�����[]�������޸������е�Ԫ�ء�
};


template <typename T>
void testFunc(T& p_param)
{

}

template <>
void testFunc <int>(int& p_param)
{

}

