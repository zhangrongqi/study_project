#define _CRT_SECURE_NO_WARNINGS

////#include <iostream>
////#include <boost/version.hpp>
////#include <boost/config.hpp>
////#include<boost/type_index.hpp>
//
//
////////////////////////////////////////////////////////
//// 测试模板推导类型
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
//// 归并排序算法
//// 
//// 分治与递归:
////		普通分治：分治的各个层次的各解决方案不同 
////
////		递归分治：分治的各个层次的解决方案相同
//// 
//// 分治的基本思想:
////		分治算法是将一个难以直接解决的大问题，分割成一些规模较小的相同问题，以便各个击破，分而治之。
////		如果原问题可分割成k个子问题，1 < k ≤n，且这些子问题都可解并可利用这些子问题的解求出原问题的解，那么这种分治法就是可行的。
////		由分治法产生的子问题往往是原问题的较小模式，这就为使用递归技术提供了方便。
////		在这种情况下，反复应用分治手段，可以使子问题与原问题类型一致而其规模却不断缩小，最终使子问题缩小到很容易直接求出其解。
////		这自然导致递归过程的产生。
//// 
//// 分治能解决的问题有以下几个特征:
////		1) 该问题的规模缩小到一定的程度就可以容易地解决
////		2) 该问题可以分解为若干个规模较小的相同问题，即该问题具有最优子结构性质。
////		3) 利用该问题分解出的子问题的解可以合并为该问题的解；
////		4) 该问题所分解出的各个子问题是相互独立的，即子问题之间不包含公共的子子问题。
//// 
////	第一条特征是绝大多数问题都可以满足的，因为问题的计算复杂性一般是随着问题规模的增加而增加；
////	第二条特征是应用分治法的前提它也是大多数问题可以满足的，此特征反映了递归思想的应用；
////	第三条特征是关键，能否利用分治法完全取决于问题是否具有第三条特征，如果具备了第一条和第二条特征，而不具备第三条特征，则可以考虑用贪心法或动态规划法。
////	第四条特征涉及到分治法的效率，如果各子问题是不独立的则分治法要做许多不必要的工作，重复地解公共的子问题，此时虽然可用分治法，但一般用动态规划法较好。
////
//// 步骤：
////		分解：将原问题分解为若干个规模较小，相互独立，与原问题形式相同的子问题；
////		解决：若子问题规模较小而容易被解决则直接解，否则递归地解各个子问题；
////		合并：将各个子问题的解合并为原问题的解。
//// 
//// 递归使用条件：分治的每一步都执行相同的流程，比如斐波那契数列的递归写法。
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
//// bmp转bin文件
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
////    int linenum, ex; //linenum:一行像素的字节总数，包括填充字节 
////
////    //open file
////    if ((binFile = fopen(filename, "rb")) == NULL) return NULL;
////
////    //read struts
////    if (fread((void*)&fileHeader, 1, sizeof(fileHeader), binFile) != sizeof(fileHeader)) isRead = FALSE;
////    if (fread((void*)&bmpHeader, 1, sizeof(bmpHeader), binFile) != sizeof(bmpHeader)) isRead = FALSE;
////
////    //问，这里的判断是为了避免什么样问题
////    if (isRead == FALSE || fileHeader.bfOffBits < sizeof(fileHeader) + sizeof(bmpHeader)) {
////        fclose(binFile);
////        return NULL;
////    }
////
////    //read image info
////    *width = bmpHeader.biWidth;
////    *height = bmpHeader.biHeight;
////    linenum = (*width * 1 + 3) / 4 * 4;
////    ex = linenum - *width * 1;         //每一行的填充字节
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
//    // 添加边
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
//using namespace std; // 指定缺省的命名空间。
//template <typename T1, typename T2>
//auto func(T1 x, T2 y) -> decltype(x + y)
////auto func(T1 x, T2 y)
//{
//	// 其它的代码。
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
	//float* float_ptr1 = (float*)&type_int; // int* -> float* 隐式转换无效
	//// float* float_ptr2 = static_cast<float*>(&type_int); // int* -> float* 使用 static_cast 转换无效
	//char* char_ptr1 = (char*)&type_int; // int* -> char* 隐式转换无效
	//// char* char_ptr2 = static_cast<char*>(&type_int); // int* -> char* 使用 static_cast 转换无效
	//void* void_ptr = &type_int; // 任何指针都可以隐式转换为 void*
	//float* float_ptr3 = (float*)void_ptr; // void* -> float* 隐式转换无效
	//float* float_ptr4 = static_cast<float*>(void_ptr); // void* -> float* 使用 static_cast 转换成功
	//char* char_ptr3 = (char*)void_ptr; // void* -> char* 隐式转换无效
	//char* char_ptr4 = static_cast<char*>(void_ptr); // void* -> char* 使用 static_cast 转换成功

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

	//char cc[8]; // 在栈上分配 8 字节的内存空间。
	//// 把 cc 的内存空间用于字符串。
	//strcpy(cc, "hello"); 
	//cout << "cc=" << cc << endl << endl;
	//// 把 cc 的内存空间用于 int 型整数。
	//int* a, * b; 
	//a = (int*)cc; // 前 4 个字节的空间用于整数 a。
	//b = (int*)cc + 4; // 后 4 个字节的空间用于整数 b。
	//*a = 12345; 
	//*b = 54321; 
	//cout << "*a=" << *a << endl;
	//cout << "*b=" << *b << endl << endl;
	//cout << "cc = " << cc << endl;
	//// 把 cc 的内存空间用于 double。
	//double* d = (double*)cc; 
	//*d = 12345.7; 
	//cout << "*d=" << *d << endl << endl;
	//// 把 cc 的内存空间用于结构体。
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
//		  cout << m_name << "调用构造函数 AA()。\n"; 
//	  }
//	  AA(const string& name) 
//		  : m_name(name) 
//	  { 
//		  cout << "调用构造函数 AA(" << m_name << ")。\n"; 
//	  } 
//	  ~AA() 
//	  { 
//		  cout << "调用了析构函数~AA(" << m_name << ")。\n"; 
//	  } 
//	  weak_ptr<BB> m_p;
//}; class BB
//{
//public:string m_name;
//	  BB() 
//	  { 
//		  cout << m_name << "调用构造函数 BB()。\n";
//	  }
//	  BB(const string& name) : m_name(name) 
//	  { 
//		  cout << "调用构造函数 BB(" << m_name << ")。\n"; 
//	  } 
//	  ~BB() { 
//		  cout << "调用了析构函数~BB(" << m_name << ")。\n"; 
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

	//	shared_ptr<BB> pp = pa->m_p.lock(); // 把 weak_ptr 提升为 shared_ptr。 // b + 1

	//	if (pp == nullptr)
	//		cout << "语句块内部：pa->m_p 已过期。\n"; 
	//	else
	//		cout << "语句块内部：pp->m_name=" << pp->m_name << "语句块内部：pp->use_count=" << pp.use_count() <<  endl;
	//}

	//shared_ptr<BB> pp = pa->m_p.lock(); // 把 weak_ptr 提升为 shared_ptr。

	//if (pp == nullptr) 
	//	cout << "语句块外部：pa->m_p 已过期。\n"; 
	//else
	//	cout << "语句块外部：pp->m_name=" << pp->m_name << endl;

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

