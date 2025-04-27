#pragma once
#include <memory>
#include <utility>

namespace MyFunction
{
	// 抽象接口类
	template <class R, class... Args>
	struct ICallable {
		virtual R invoke(Args&&... args) = 0;
		virtual ~ICallable() = default;
	};

	// 桥接类
	template <class Func, class R, class... Args>
	class ICallableImpl : public ICallable<R, Args...> {
		using FunctionType = typename std::decay<Func>::type; // 确保存储值类型
		FunctionType callable; // 按值存储
	public:
		ICallableImpl(Func&& c)
			: callable(std::forward<Func>(c)) {
		} // 完美转发构造

		R invoke(Args&&... args) override
		{
			return callable(std::forward<Args>(args)...);
		}
	};

	template <class Signature>
	class MyFunction;

	template <class R, class... Args>
	class MyFunction<R(Args...)> {
		std::unique_ptr<ICallable<R, Args...>> funcPtr;
	public:
		template <typename Func>
		MyFunction(Func&& p_func)
			: funcPtr(std::make_unique<ICallableImpl<Func, R, Args...>>(
				std::forward<Func>(p_func)))
		{
		}

		R operator()(Args&&... args) const
		{
			return funcPtr->invoke(std::forward<Args>(args)...);
		}
	};
};












