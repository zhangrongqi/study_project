#define _CRT_SECURE_NO_WARNINGS

////#include <iostream>
////#include <boost/version.hpp>
////#include <boost/config.hpp>
////#include<boost/type_index.hpp>
//
//
////////////////////////////////////////////////////////
//// ����ģ���Ƶ�����
//// ///////////////////////////////////////////////////
////template<typename T>
////void f(T param)
////{
////	using std::cout;
////	using std::endl;
////	using boost::typeindex::type_id_with_cvr;
////	cout << "fr -- " << "type_id_with_cvr(T).name() = " << type_id_with_cvr<T>().pretty_name() << endl;
////	cout << "fr -- " << "type_id_with_cvr(param).name() = " << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
////	cout << "###################################################" << endl;
////}
////template<typename T>
////void fr(T& param)
////{
////	using std::cout;
////	using std::endl;
////	using boost::typeindex::type_id_with_cvr;
////	cout << "fr -- " << "type_id_with_cvr(T).name() = " << type_id_with_cvr<T>().pretty_name() << endl;
////	cout << "fr -- " << "type_id_with_cvr(param).name() = " << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
////	cout << "###################################################" << endl;
////}
////
////template<typename T>
////void fp(T* param)
////{
////	using std::cout;
////	using std::endl;
////	using boost::typeindex::type_id_with_cvr;
////	cout << "fr -- " << "type_id_with_cvr(T).name() = " << type_id_with_cvr<T>().pretty_name() << endl;
////	cout << "fr -- " << "type_id_with_cvr(param).name() = " << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
////	cout << "###################################################" << endl;
////
////}
////
////void quickSort(int arr[])
////{
////	int baseIndex = sizeof(arr) / sizeof(int) / 2;
////	int baseValue = arr[baseIndex];
////
////	swap(arr[0], arr[baseIndex]);
////
////
////}
////
////using namespace std;
////int main()
////{
////	    int a = 10;
////	
////	    const int* ptr_a = &a;
////	
////	    int const arr[10] = { 0 };
////	
////	    cout << "fr(ptr_a) --> " << endl;
////	    fr(ptr_a);
////	    cout << "fp(ptr_a) --> " << endl;
////	    fp(ptr_a);
////	    cout << "fr(a) --> " << endl;
////	    fr(a);
////	    cout << "fp(&a) --> " << endl;
////	    fp(&a);
////	    cout << "fr(arr) --> " << endl;
////	    fr(arr);
////	    cout << "fp(arr) --> " << endl;
////	    fp(arr);
////	
////	std::system("pause");
////
////	return 0;
////}
//
//
////////////////////////////////////////////////////////
//// �鲢�����㷨
//// 
//// ������ݹ�:
////		��ͨ���Σ����εĸ�����εĸ����������ͬ 
////
////		�ݹ���Σ����εĸ�����εĽ��������ͬ
//// 
//// ���εĻ���˼��:
////		�����㷨�ǽ�һ������ֱ�ӽ���Ĵ����⣬�ָ��һЩ��ģ��С����ͬ���⣬�Ա�������ƣ��ֶ���֮��
////		���ԭ����ɷָ��k�������⣬1 < k ��n������Щ�����ⶼ�ɽⲢ��������Щ������Ľ����ԭ����Ľ⣬��ô���ַ��η����ǿ��еġ�
////		�ɷ��η�������������������ԭ����Ľ�Сģʽ�����Ϊʹ�õݹ鼼���ṩ�˷��㡣
////		����������£�����Ӧ�÷����ֶΣ�����ʹ��������ԭ��������һ�¶����ģȴ������С������ʹ��������С��������ֱ�������⡣
////		����Ȼ���µݹ���̵Ĳ�����
//// 
//// �����ܽ�������������¼�������:
////		1) ������Ĺ�ģ��С��һ���ĳ̶ȾͿ������׵ؽ��
////		2) ��������Էֽ�Ϊ���ɸ���ģ��С����ͬ���⣬����������������ӽṹ���ʡ�
////		3) ���ø�����ֽ����������Ľ���Ժϲ�Ϊ������Ľ⣻
////		4) ���������ֽ���ĸ������������໥�����ģ���������֮�䲻�����������������⡣
//// 
////	��һ�������Ǿ���������ⶼ��������ģ���Ϊ����ļ��㸴����һ�������������ģ�����Ӷ����ӣ�
////	�ڶ���������Ӧ�÷��η���ǰ����Ҳ�Ǵ���������������ģ���������ӳ�˵ݹ�˼���Ӧ�ã�
////	�����������ǹؼ����ܷ����÷��η���ȫȡ���������Ƿ���е���������������߱��˵�һ���͵ڶ��������������߱�����������������Կ�����̰�ķ���̬�滮����
////	�����������漰�����η���Ч�ʣ�������������ǲ�����������η�Ҫ����಻��Ҫ�Ĺ������ظ��ؽ⹫���������⣬��ʱ��Ȼ���÷��η�����һ���ö�̬�滮���Ϻá�
////
//// ���裺
////		�ֽ⣺��ԭ����ֽ�Ϊ���ɸ���ģ��С���໥��������ԭ������ʽ��ͬ�������⣻
////		��������������ģ��С�����ױ������ֱ�ӽ⣬����ݹ�ؽ���������⣻
////		�ϲ���������������Ľ�ϲ�Ϊԭ����Ľ⡣
//// 
//// �ݹ�ʹ�����������ε�ÿһ����ִ����ͬ�����̣�����쳲��������еĵݹ�д����
//// ///////////////////////////////////////////////////
//
////void merge(int* arr, int begin, int middle, int end)
////{
////	int i = begin;
////	int j = middle + 1;
////
////	int* tempArr = new int[end - begin + 1];
////
////	int tempArrIndex = 0;
////
////	while (i <= middle && j <= end)
////	{
////		if (arr[i] < arr[j])
////		{
////			tempArr[tempArrIndex++] = arr[i++];
////		}
////		else
////		{
////			tempArr[tempArrIndex++] = arr[j++];
////		}
////	}
////
////	while (i <= middle)
////	{
////		tempArr[tempArrIndex++] = arr[i++];
////	}
////
////	while (j <= end)
////	{
////		tempArr[tempArrIndex++] = arr[j++];
////	}
////
////	for (i = begin, tempArrIndex = 0; i <= end; i++, tempArrIndex++)
////	{
////		arr[i] = tempArr[tempArrIndex];
////	}
////
////	delete[] tempArr;
////}
////
////void mergeSort(int* arr, int begin, int end)
////{
////	if (begin < end)
////	{
////		int middle = (begin + end) / 2;
////		mergeSort(arr, begin, middle);
////		mergeSort(arr, middle + 1, end);
////		merge(arr, begin, middle, end);
////	}
////}
//
////#include "mergeSort.h"
////
////int main()
////{
////	using std::cout;
////	using std::endl;
////
////	int arr[9] = {9, 0, 8, 5, 1, 7, 3, 6, 2};
////
////	mergeSort(arr, 0, sizeof(arr) / sizeof(int) - 1);
////
////	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
////	{
////		cout << arr[i] << endl;
////	}
////
////	system("pause");
////	return 0;
////}
//
//
//
//
////#include "modbus.h"
////#include "modbus-tcp.h"
////#include "registerCalculator.h"
////
////int main()
////{
//	//modbus_t* ctx;
//
//	//ctx = modbus_new_tcp("127.0.0.1", 502);
//
//	//modbus_connect(ctx);
//
//	//uint8_t registerValue = 0;
//
//	//modbus_read_bits(ctx, registerCalculator('M', 100), 1, &registerValue);
//
//
//	//std::cout << registerValue << std::endl;
//
//	//using std::cout;
//	//using std::endl;
//
//	//char temp = 'a';
//
//	//while (temp != 'q' && temp != 'Q')
//	//{
//	//	cout << "temp = " << temp <<  endl;
//	//	temp = getchar();
//	//}
//
//	//return 0;
////}
//
//
//// bmpתbin�ļ�
////#include <iostream>
//////#include <wingdi.h>
////
////#include <WinDef.h>
////
////using namespace std;
////
////
////typedef struct tagBITMAPFILEHEADER {
////    WORD    bfType;
////    DWORD   bfSize;
////    WORD    bfReserved1;
////    WORD    bfReserved2;
////    DWORD   bfOffBits;
////} BITMAPFILEHEADER, FAR* LPBITMAPFILEHEADER, * PBITMAPFILEHEADER;
////
////typedef struct tagBITMAPINFOHEADER {
////    DWORD      biSize;
////    LONG       biWidth;
////    LONG       biHeight;
////    WORD       biPlanes;
////    WORD       biBitCount;
////    DWORD      biCompression;
////    DWORD      biSizeImage;
////    LONG       biXPelsPerMeter;
////    LONG       biYPelsPerMeter;
////    DWORD      biClrUsed;
////    DWORD      biClrImportant;
////} BITMAPINFOHEADER, FAR* LPBITMAPINFOHEADER, * PBITMAPINFOHEADER;
////
////BYTE* RmwRead8BitBmpFile2Img(const char* filename, int* width, int* height) {
////    FILE* binFile;
////    BYTE* pImg = NULL;
////    BITMAPFILEHEADER fileHeader;
////    BITMAPINFOHEADER bmpHeader;
////    BOOL isRead = TRUE;
////    int linenum, ex; //linenum:һ�����ص��ֽ���������������ֽ� 
////
////    //open file
////    if ((binFile = fopen(filename, "rb")) == NULL) return NULL;
////
////    //read struts
////    if (fread((void*)&fileHeader, 1, sizeof(fileHeader), binFile) != sizeof(fileHeader)) isRead = FALSE;
////    if (fread((void*)&bmpHeader, 1, sizeof(bmpHeader), binFile) != sizeof(bmpHeader)) isRead = FALSE;
////
////    //�ʣ�������ж���Ϊ�˱���ʲô������
////    if (isRead == FALSE || fileHeader.bfOffBits < sizeof(fileHeader) + sizeof(bmpHeader)) {
////        fclose(binFile);
////        return NULL;
////    }
////
////    //read image info
////    *width = bmpHeader.biWidth;
////    *height = bmpHeader.biHeight;
////    linenum = (*width * 1 + 3) / 4 * 4;
////    ex = linenum - *width * 1;         //ÿһ�е�����ֽ�
////
////    fseek(binFile, fileHeader.bfOffBits, SEEK_SET);
////    pImg = new BYTE[(*width) * (*height)];
////    if (pImg != NULL) {
////        for (int i = 0; i < *height; i++) {
////            int r = fread(pImg + (*height - i - 1) * (*width), sizeof(BYTE), *width, binFile);
////            if (r != *width) {
////                delete pImg;
////                fclose(binFile);
////                return NULL;
////            }
////            fseek(binFile, ex, SEEK_CUR);
////        }
////    }
////    fclose(binFile);
////    return pImg;
////}
////
////void writeBin(const char* path, BYTE* buf, int size)
////{
////    FILE* outfile;
////
////    if ((outfile = fopen(path, "wb")) == NULL)
////    {
////        printf("\nCan not open the path: %s \n", path);
////        exit(-1);
////    }
////    fwrite(buf, sizeof(char), size, outfile);
////    fclose(outfile);
////}
////
////int main()
////{
////    // D:\Desktop\ttt\02_0.bmp
////    // D:\Desktop\ttt\02_0.bin
////
////    int* width;
////    int* height;
////    BYTE* binBuffer;
////
////    RmwRead8BitBmpFile2Img("D:\\Desktop\\ttt\\02_0.bmp", width, height);
////
////    writeBin("D:\\Desktop\\ttt\\02_0.bin", binBuffer, (*width) * (*height));
////
////	return 0;
////}
//
////#include<iostream>
////using namespace std;
////
////int arr[10] = { 2,3,2,1,3,1,0,0,2,2 };
////
////int arrSize = sizeof(arr) / sizeof(int);
////bool canJump(int arr[])
////{
////	int maxDistance = 0;
////	int arrLength = sizeof(arr) / sizeof(int) - 1;
////
////	for (int i = 0; i <= arrLength; ++i)
////	{
////		if (maxDistance >= i)
////		{
////			maxDistance = max(maxDistance, i + arr[i]);
////
////			if (maxDistance >= arrLength)
////			{
////				return true;
////			} 
////		}
////		else
////		{
////			return false;
////		}
////	}
////	return true;
////}
//
////bool judge0(int index)
////{
////
////	for (int j = 0; j < index; ++j)
////	{
////		if (arr[j] > index - j)
////		{
////			return true;
////		}
////	}
////
////	return false;
////}
////
////bool myJump(int arr[], int arrSize)
////{
////	for (int i = 0; i < arrSize; ++i)
////	{
////		if (0 == arr[i] && !judge0(i))
////		{
////			return false;
////		}
////	}
////	return true;
////}
////
////int main()
////{
////	if (myJump(arr, arrSize))
////	{
////		cout << "true" << endl;
////	}
////	else
////	{
////		cout << "false" << endl;
////	}
////
////	return 0;
////}
//
//
//
//#include<iostream>
////#include<vector>
//#include <map>
//using namespace std;
//
////int arr[100] = {2,9,2,21,3,21,5,1,7,2,
////				2,19,2,1,3,1,5,1,7,2, 
////				2,9,12,1,3,31,25,21,7,2, 
////				2,9,2,11,3,1,5,1,7,2, 
////				2,9,2,1,13,1,5,1,27,2, 
////				2,9,2,21,3,11,5,31,7,22, 
////				2,9,2,1,3,1,15,1,7,2, 
////				22,9,2,21,3,1,5,11,7,2,
////				2,23,2,12,3,31,5,1,17,2, 
////				12,13,2,1,3,1,5,1,17,12};
//
//int arr[] = { 10, 5, 3, 7, 2, 1 };
//
//int m = 3;
//
//template<int sz>
//int maxTime(int(&arr)[sz] ,const int m)
//{
//	int temp = 0;
//	map<int, int> usingTimeMap;
//
//	for (int i = 0; i < m; ++i)
//	{
//		usingTimeMap[i] = 0;
//	}
//
//	map<int, int>::iterator min_it = usingTimeMap.begin();
//
//	for (int i = 0; i < sz; ++i)
//	{
//		for (int j = 0; j < sz - i - 1; ++j)
//		{
//			if (arr[j] < arr[j + 1])
//			{
//				temp = arr[j];
//				arr[j] = arr[j + 1];
//				arr[j + 1] = temp;
//			}
//		}
//	}
//
//	for (int i = 0; i < sz; ++i)
//	{
//		int min = usingTimeMap.begin()->second;
//		for (map<int, int>::iterator it = usingTimeMap.begin(); it != usingTimeMap.end(); ++it)
//		{
//			if (it->second <= min)
//			{
//				min = it->second;
//				min_it = it;
//			}
//		}
//
//		min_it->second += arr[i];
//	}
//
//	return 0;
//}
//
//int main()
//{
//	maxTime(arr ,m);
//	return 0;
//}


//#include <iostream>
//#include <thread>
//#include <mutex>
//#include <condition_variable>
//
//using namespace std;
//
//mutex mtx;
//condition_variable cv;
//int cargo = 0;
//bool has_shipment = false;
//
//void consume(int n)
//{
//	for (int i = 0; i < n; ++i)
//	{
//		unique_lock<mutex> lck(mtx);
//		cv.wait(lck, [] {return has_shipment; });
//		cout << "consume: " << cargo << '\n';
//		cargo = 0;
//		has_shipment = false;
//	}
//}
//
//int main()
//{
//	thread consume_thread(consume, 10);
//
//	for (int i = 0; i < 10; ++i)
//	{
//		while (has_shipment) this_thread::yield();
//		{
//			lock_guard<mutex> lck(mtx);
//			cargo = i + 1;
//			has_shipment = true;
//		}
//		cv.notify_one();
//	}
//
//	consume_thread.join();
//
//	return 0;
//}

//#include "dijkstra.h"   
//
//int main() {
//    int num_vertices = 4;
//    vector<vector<pii>> graph(num_vertices);
//
//    // ��ӱ�
//    graph[0].push_back({ 1, 1 });
//    graph[0].push_back({ 2, 4 });
//    graph[1].push_back({ 0, 1 });
//    graph[1].push_back({ 2, 2 });
//    graph[1].push_back({ 3, 5 });
//    graph[2].push_back({ 0, 4 });
//    graph[2].push_back({ 1, 2 });
//    graph[2].push_back({ 3, 1 });
//    graph[3].push_back({ 1, 5 });
//    graph[3].push_back({ 2, 1 });
//
//    dijkstra(graph, 0);
//
//    return 0;
//}




//#include "myStack.h"
//#include <iostream>
//
//
//using namespace std; // ָ��ȱʡ�������ռ䡣
//template <typename T1, typename T2>
//auto func(T1 x, T2 y) -> decltype(x + y)
////auto func(T1 x, T2 y)
//{
//	// �����Ĵ��롣
//	decltype(x + y) tmp = x + y; cout << "tmp=" << tmp << endl;
//	//auto tmp = x + y; cout << "tmp=" << tmp << endl;
//	return tmp;
//}
//template<typename T1, typename T2 = string>
//void showFunc(T1 p_1, T2 p_2)
//{
//	cout << "p_2.Length = " << p_2.length() << endl;
//}


//
//int main()
//{
	//showFunc(3, string("3.14"));

	//std::vector<int> test_arr = { 0, 1, 0,2,1,0,1,3,2,1,2,1 };

	//int res = collectRain_1(test_arr);

	//std::cout << res << std::endl;

	//myStack<int> testStack = myStack<int>(5);

	//int i = 0;

	//while (!testStack.isFull())
	//	testStack.push(i++);

	//int show = 0;

	//while (!testStack.isEmpty())
	//{
	//	testStack.pop(show);
	//	std::cout << "show = " << show << std::endl;
	//}


	//int type_int = 10;
	//float* float_ptr1 = (float*)&type_int; // int* -> float* ��ʽת����Ч
	//// float* float_ptr2 = static_cast<float*>(&type_int); // int* -> float* ʹ�� static_cast ת����Ч
	//char* char_ptr1 = (char*)&type_int; // int* -> char* ��ʽת����Ч
	//// char* char_ptr2 = static_cast<char*>(&type_int); // int* -> char* ʹ�� static_cast ת����Ч
	//void* void_ptr = &type_int; // �κ�ָ�붼������ʽת��Ϊ void*
	//float* float_ptr3 = (float*)void_ptr; // void* -> float* ��ʽת����Ч
	//float* float_ptr4 = static_cast<float*>(void_ptr); // void* -> float* ʹ�� static_cast ת���ɹ�
	//char* char_ptr3 = (char*)void_ptr; // void* -> char* ��ʽת����Ч
	//char* char_ptr4 = static_cast<char*>(void_ptr); // void* -> char* ʹ�� static_cast ת���ɹ�

	//long long showAddress = 0;

	//int test = 10;

	//int* int_ptr = &test;

	//showAddress = reinterpret_cast<long long> (int_ptr);

	//std::cout << "int_ptr show address = " << showAddress << std::endl;

	//void* void_ptr = static_cast<void*> (int_ptr);

	//showAddress = reinterpret_cast<long long> (void_ptr);

	//std::cout << "void_ptr show address = " << showAddress << std::endl;

	//float* float_ptr = static_cast<float*> (void_ptr);

	//showAddress = reinterpret_cast<long long> (float_ptr);

	//std::cout << "float_ptr show address = " << showAddress << std::endl;

	//float_ptr = reinterpret_cast<float*> (int_ptr);

	//showAddress = reinterpret_cast<long long> (float_ptr);

	//std::cout << "float_ptr show address = " << showAddress << std::endl;

	//int float_num = 3;

	//char c = static_cast<char> (float_num);

	//string testStr = "abcd";

	//cout << "show testStr first address by reinterpret_cast = " << reinterpret_cast<long long>(testStr.c_str()) << endl;

	//cout << "show testStr first address by (void*) = " << (void*)(testStr.c_str()) << endl;

	//char cc[8]; // ��ջ�Ϸ��� 8 �ֽڵ��ڴ�ռ䡣
	//// �� cc ���ڴ�ռ������ַ�����
	//strcpy(cc, "hello"); 
	//cout << "cc=" << cc << endl << endl;
	//// �� cc ���ڴ�ռ����� int ��������
	//int* a, * b; 
	//a = (int*)cc; // ǰ 4 ���ֽڵĿռ��������� a��
	//b = (int*)cc + 4; // �� 4 ���ֽڵĿռ��������� b��
	//*a = 12345; 
	//*b = 54321; 
	//cout << "*a=" << *a << endl;
	//cout << "*b=" << *b << endl << endl;
	//cout << "cc = " << cc << endl;
	//// �� cc ���ڴ�ռ����� double��
	//double* d = (double*)cc; 
	//*d = 12345.7; 
	//cout << "*d=" << *d << endl << endl;
	//// �� cc ���ڴ�ռ����ڽṹ�塣
	//struct stt
	//{
	//	int a; 
	//	char b[4];
	//}*st; 
	//st = (struct stt*)cc; 
	//st->a = 38; 
	//strcpy(st->b, "abc"); 
	//cout << "st->a=" << st->a << endl; 
	//cout << "st->b=" << st->b << endl << endl;
	// void* malloc(size_t size);
	//char* cc1 = (char*)malloc(8);
	//int* cc1 = (int*)malloc(8);

	//void* tempPtr = operator new (sizeof(myStack<int>));

	//myStack<int>* myStackPtr = new (tempPtr) myStack<int>(8);

	//myStackPtr->~myStack();

	//operator delete (tempPtr);



//	return 0;
//}

//#include <iostream>
//#include <memory>
//using namespace std; class BB; class AA
//{
//public:string m_name;
//	  AA() 
//	  { 
//		  cout << m_name << "���ù��캯�� AA()��\n"; 
//	  }
//	  AA(const string& name) 
//		  : m_name(name) 
//	  { 
//		  cout << "���ù��캯�� AA(" << m_name << ")��\n"; 
//	  } 
//	  ~AA() 
//	  { 
//		  cout << "��������������~AA(" << m_name << ")��\n"; 
//	  } 
//	  weak_ptr<BB> m_p;
//}; class BB
//{
//public:string m_name;
//	  BB() 
//	  { 
//		  cout << m_name << "���ù��캯�� BB()��\n";
//	  }
//	  BB(const string& name) : m_name(name) 
//	  { 
//		  cout << "���ù��캯�� BB(" << m_name << ")��\n"; 
//	  } 
//	  ~BB() { 
//		  cout << "��������������~BB(" << m_name << ")��\n"; 
//	  } 
//	  weak_ptr<AA> m_p;
//};

//class base
//{
//public:
//	base()
//	{
//
//	}
//	~base() = default;
//};
//
//class derive : base
//{
//public:
//	explicit derive(int i = 0)
//	{
//
//	}
//
//	operator int() const
//	{
//		return 1;
//	}
//
//	int operator ()() const
//	{
//
//	}
//
//	~derive() = default;
//};
//
//void func(int p_d)
//{
//
//}

//#include <vector>
//#include <functional>
//#include <algorithm>

//template <typename T>
//void show(T&& param)
//{
//	std::cout << "param -- " << param << std::endl;	
//}
////
//void print()
//{
//
//}
////
//template <typename T, typename ...Args>
//void print(T&& param, Args&& ...args)
//{
//	if (sizeof ...(args) == 0) 
//	{
//		return;
//	}
//
//	show(std::forward<T>(param));
//
//	print(std::forward<Args>(args)...);
//}

//template<typename ...Args>
//void print(Args&& ...args)
//{
//	(show(std::forward<Args>(args)), ...);
//}

//#include "My_type_traits.h"
//
//#include <assert.h>
//
//int main()
//{
	//shared_ptr<AA> pa = make_shared<AA>(" a"); //  a + 1

	//{
	//	shared_ptr<BB> pb = make_shared<BB>(" b"); // b + 1

	//	pa->m_p = pb;
	//	pb->m_p = pa; 

	//	shared_ptr<BB> pp = pa->m_p.lock(); // �� weak_ptr ����Ϊ shared_ptr�� // b + 1

	//	if (pp == nullptr)
	//		cout << "�����ڲ���pa->m_p �ѹ��ڡ�\n"; 
	//	else
	//		cout << "�����ڲ���pp->m_name=" << pp->m_name << "�����ڲ���pp->use_count=" << pp.use_count() <<  endl;
	//}

	//shared_ptr<BB> pp = pa->m_p.lock(); // �� weak_ptr ����Ϊ shared_ptr��

	//if (pp == nullptr) 
	//	cout << "�����ⲿ��pa->m_p �ѹ��ڡ�\n"; 
	//else
	//	cout << "�����ⲿ��pp->m_name=" << pp->m_name << endl;

	//derive div;

	//func(div);

	//std::vector<int> num{ 1,2,3,4,5,6 };

	//std::for_each(num.begin(), num.end(), [](const int& showNum)
	//	{
	//		std::cout << "num -- " << showNum << std::endl;
	//	});

	//int a = 7;

	//double b = 7.7;

	//std::string showstr = "showstr";

	//print('c', "asd", 1, 4.5, a,b, showstr);

	//constexpr bool showType = My_type_traits::my_is_int_v<const int>;

	//static_assert(showType, "showType == false");
//
//	return 0;
//}

//#include <iostream>
//#include <algorithm>
//#include <ranges>
//#include <vector>
//
//using namespace std;
//
//int main()
//{
//	vector<string> stringVct{ "asd", "bfc", "ttf", "ddy", "axt", "aact", "wdc" };
//
//	//vector<string> showVct;
//
//	char compareChar = 'c';
//
//	auto compareFunc = [compareChar](const string& compareString) ->bool {return compareString.find(compareChar) != string::npos; };
//
//	//copy_if(stringVct.begin(),stringVct.end(), back_inserter(showVct), compareFunc);
//
//	//ranges::copy_if(stringVct, back_inserter(showVct), compareFunc);
//
//	auto showVct = stringVct | views::filter(compareFunc);
//
//	for (const auto& it : showVct)
//	{
//		cout << it << '\n';
//	}
//
//	return 0;
//}

//#include "PromiseAndFuture.h"
//
//int main()
//{
//	constexpr long long steps = 000000000;
//
//	std::promise<double> promise_pi;
//
//	//auto future_pi = promise_pi.get_future();
//
//	//auto future_pi_share = promise_pi.get_future().share();
//
//	std::shared_future<double> future_pi_share{ promise_pi.get_future() };
//
//	std::thread t1(PromiseAndFuture::compute_pi, steps, std::move(promise_pi));
//
//	//std::thread t2(PromiseAndFuture::display_pi, std::move(future_pi));
//
//	std::thread t3(PromiseAndFuture::display_pi_share, future_pi_share);
//
//	std::thread t4(PromiseAndFuture::display_pi_share, future_pi_share);
//
//
//	if (t1.joinable())
//		t1.join();
//
//	//if (t2.joinable())
//	//	t2.join();
//
//	if (t3.joinable())
//		t3.join();
//
//	if (t4.joinable())
//		t4.join();
//
//	return 0;
//}

