#pragma once
#include <string>

#ifdef DLLRGISTERCALCULATOR
#define DLLRC_API __declspec(dllexport)
#else
#define DLLRC_API __declspec(dllimport)
#endif // DLLRGISTERCALCULATOR

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/*
	�㴨�Ĵ�����ַ������
	\param registerType �Ĵ�������
	\param registerNum	�Ĵ������

	\return �ɹ� ���ؼĴ�����ַ ʧ�� ����-1
	*/
	int DLLRC_API registerCalculator(char registerType, int registerNum);

#ifdef __cplusplus
}
#endif // __cplusplus


std::string DecIntToHexStr(long long num);

int OctStrToDecStr(std::string str);