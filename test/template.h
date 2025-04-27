//#pragma once
//#include <iostream> // 包含头文件。
//using namespace std; // 指定缺省的命名空间。
//class CGirl // 超女类。
//{
//public:int m_bh; // 编号。
//	  string m_name; // 姓名。
//	  int m_rank; // 排名。
//};
//template <typename T>
//void Swap(T& a, T& b); // 交换两个变量的值函数模板。
//template<>
//void Swap<CGirl>(CGirl& g1, CGirl& g2); // 交换两个超女对象的排名。
//// template<>
//// void Swap(CGirl& g1, CGirl& g2); // 交换两个超女对象的排名。
//int main()
//{
//	int a = 10, b = 20;
//	Swap(a, b); // 使用了函数模板。
//	cout << "a=" << a << ",b=" << b << endl;
//	CGirl g1, g2;
//	g1.m_rank = 1; g2.m_rank = 2;
//	Swap<>(g1, g2); // 使用了超女类的具体化函数。
//	cout << "g1.m_rank=" << g1.m_rank << ",g2.m_rank=" << g2.m_rank << endl;
//}
//template <typename T>
//void Swap(T& a, T& b) // 交换两个变量的值函数模板。
//{
//	T tmp = a; a = b;
//	b = tmp; cout << "调用了 Swap(T& a, T& b)\n";
//}
//template<>
//void Swap<CGirl>(CGirl& g1, CGirl& g2) // 交换两个超女对象的排名。
//// template<>
//// void Swap(CGirl& g1, CGirl& g2) // 交换两个超女对象的排名。
//{
//	int tmp = g1.m_rank;
//	g1.m_rank = g2.m_rank;
//	g2.m_rank = tmp; cout << "调用了 Swap(CGirl& g1, CGirl& g2)\n";
//}
//
//void Swap(CGirl& g1, CGirl& g2)
//{
//	int tmp = g1.m_rank;
//	g1.m_rank = g2.m_rank;
//	g2.m_rank = tmp; cout << "调用了 Swap(CGirl& g1, CGirl& g2)\n";
//}

#include <iostream> // 包含头文件。
using namespace std; // 指定缺省的命名空间。
template <class T1, class T2 = string>
class AA
{
public:T1 m_a; // 通用类型用于成员变量。
	  T2 m_b; // 通用类型用于成员变量。
	  AA() {} // 默认构造函数是空的。
	  // 通用类型用于成员函数的参数。
	  AA(T1 a, T2 b) :m_a(a), m_b(b) {}
	  // 通用类型用于成员函数的返回值。
	  T1 geta() // 获取成员 m_a 的值。
	  {
		  T1 a = 2; // 通用类型用于成员函数的代码中。
		  return m_a + a;
	  }
	  T2 getb(); // 获取成员 m_b 的值。
};
template <class T1, class T2>
T2 AA<T1, T2>::getb() // 获取成员 m_b 的值。
{
	return m_b;
}
//int main()
//{
//	AA<int, string>* a = new AA<int, string>(3, "西施"); // 用模板类 AA 创建对象 a。
//	cout << "a->geta()=" << a->geta() << endl; cout << "a->getb()=" << a->getb() << endl;
//	delete a;
//}