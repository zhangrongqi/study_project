#pragma once
#include <type_traits>

namespace My_type_traits
{
	template<class T>
	struct my_is_int_helper
		:public std::false_type
	{

	};

	template<>
	struct my_is_int_helper <int>
		:public std::true_type
	{

	};

	template<>
	struct my_is_int_helper <bool>
		:public std::true_type
	{

	};

	template<>
	struct my_is_int_helper <char>
		:public std::true_type
	{

	};

	template<>
	struct my_is_int_helper <long long>
		:public std::true_type
	{

	};

	template<class T>
	struct my_is_int
		:my_is_int_helper<typename std::remove_cv<T>::type>
	{

	};

	template<class T>
	constexpr bool my_is_int_v{ my_is_int<T>::value };
}