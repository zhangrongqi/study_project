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
	»ã´¨¼Ä´æÆ÷µØÖ·¼ÆËãÆ÷
	\param registerType ¼Ä´æÆ÷ÀàĞÍ
	\param registerNum	¼Ä´æÆ÷±àºÅ

	\return ³É¹¦ ·µ»Ø¼Ä´æÆ÷µØÖ· Ê§°Ü ·µ»Ø-1
	*/
	int DLLRC_API registerCalculator(char registerType, int registerNum);

#ifdef __cplusplus
}
#endif // __cplusplus


std::string DecIntToHexStr(long long num);

int OctStrToDecStr(std::string str);