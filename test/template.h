//#pragma once
//#include <iostream> // ����ͷ�ļ���
//using namespace std; // ָ��ȱʡ�������ռ䡣
//class CGirl // ��Ů�ࡣ
//{
//public:int m_bh; // ��š�
//	  string m_name; // ������
//	  int m_rank; // ������
//};
//template <typename T>
//void Swap(T& a, T& b); // ��������������ֵ����ģ�塣
//template<>
//void Swap<CGirl>(CGirl& g1, CGirl& g2); // ����������Ů�����������
//// template<>
//// void Swap(CGirl& g1, CGirl& g2); // ����������Ů�����������
//int main()
//{
//	int a = 10, b = 20;
//	Swap(a, b); // ʹ���˺���ģ�塣
//	cout << "a=" << a << ",b=" << b << endl;
//	CGirl g1, g2;
//	g1.m_rank = 1; g2.m_rank = 2;
//	Swap<>(g1, g2); // ʹ���˳�Ů��ľ��廯������
//	cout << "g1.m_rank=" << g1.m_rank << ",g2.m_rank=" << g2.m_rank << endl;
//}
//template <typename T>
//void Swap(T& a, T& b) // ��������������ֵ����ģ�塣
//{
//	T tmp = a; a = b;
//	b = tmp; cout << "������ Swap(T& a, T& b)\n";
//}
//template<>
//void Swap<CGirl>(CGirl& g1, CGirl& g2) // ����������Ů�����������
//// template<>
//// void Swap(CGirl& g1, CGirl& g2) // ����������Ů�����������
//{
//	int tmp = g1.m_rank;
//	g1.m_rank = g2.m_rank;
//	g2.m_rank = tmp; cout << "������ Swap(CGirl& g1, CGirl& g2)\n";
//}
//
//void Swap(CGirl& g1, CGirl& g2)
//{
//	int tmp = g1.m_rank;
//	g1.m_rank = g2.m_rank;
//	g2.m_rank = tmp; cout << "������ Swap(CGirl& g1, CGirl& g2)\n";
//}

#include <iostream> // ����ͷ�ļ���
using namespace std; // ָ��ȱʡ�������ռ䡣
template <class T1, class T2 = string>
class AA
{
public:T1 m_a; // ͨ���������ڳ�Ա������
	  T2 m_b; // ͨ���������ڳ�Ա������
	  AA() {} // Ĭ�Ϲ��캯���ǿյġ�
	  // ͨ���������ڳ�Ա�����Ĳ�����
	  AA(T1 a, T2 b) :m_a(a), m_b(b) {}
	  // ͨ���������ڳ�Ա�����ķ���ֵ��
	  T1 geta() // ��ȡ��Ա m_a ��ֵ��
	  {
		  T1 a = 2; // ͨ���������ڳ�Ա�����Ĵ����С�
		  return m_a + a;
	  }
	  T2 getb(); // ��ȡ��Ա m_b ��ֵ��
};
template <class T1, class T2>
T2 AA<T1, T2>::getb() // ��ȡ��Ա m_b ��ֵ��
{
	return m_b;
}
//int main()
//{
//	AA<int, string>* a = new AA<int, string>(3, "��ʩ"); // ��ģ���� AA �������� a��
//	cout << "a->geta()=" << a->geta() << endl; cout << "a->getb()=" << a->getb() << endl;
//	delete a;
//}