#pragma once
#include <memory>
#include <utility>

namespace MyFunction
{
	// ����ӿ���
	template <class R, class... Args>
	struct ICallable {
		virtual R invoke(Args&&... args) = 0;
		virtual ~ICallable() = default;
	};

	// �Ž���
	template <class Func, class R, class... Args>
	class ICallableImpl : public ICallable<R, Args...> {
		using FunctionType = typename std::decay<Func>::type; // ȷ���洢ֵ����
		FunctionType callable; // ��ֵ�洢
	public:
		ICallableImpl(Func&& c)
			: callable(std::forward<Func>(c)) {
		} // ����ת������

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












