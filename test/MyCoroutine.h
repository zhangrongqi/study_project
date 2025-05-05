#pragma once
#include <iostream>
#include <coroutine>

//struct MyCoroutine
//{
//	struct promise_type
//	{
//		MyCoroutine get_return_object() {
//			return MyCoroutine(std::coroutine_handle<promise_type>::from_promise(*this));
//		}
//		std::suspend_always initial_suspend() { return{}; }
//		std::suspend_always final_suspend() noexcept { return{}; }
//		void return_value(int v) { _value = v; }
//		auto yield_value(int v) { _value = v; return std::suspend_always{}; }
//		void unhandled_exception() {};
//
//	public:
//		int get() { return _value; }
//
//	private:
//		int _value;
//	};
//
//
//	MyCoroutine(std::coroutine_handle<promise_type> coroutine) :handle(coroutine) {}
//	//void resume() { handle.resume(); }
//	operator bool() { return !handle.done(); }
//	int get() { handle.resume(); return handle.promise().get(); }
//
//private:
//	std::coroutine_handle<promise_type> handle;
//};
//
//MyCoroutine coroFunc()
//{
//	std::cout << "hello world" << std::endl;
//	co_yield 666;
//	co_yield 777;
//	co_return 888;
//}
//
//MyCoroutine fibonacci(int n)
//{
//	int a = 0;
//	int b = 1;
//	co_yield a;
//	co_yield b;
//
//	while (--n)
//	{
//		int r = a + b;
//		co_yield r;
//		a = b;
//		b = r;
//	}
//	co_return (a + b);
//}

/*
#include "MyCoroutine.h"

int main()
{
	MyCoroutine coro = coroFunc();
	//coro.resume();

	//int value = coro.get();
	//std::cout << "value is " << value << std::endl;

	while (coro)
	{
		int value = coro.get();
		std::cout << "value is " << value << std::endl;
	}

	MyCoroutine coro_fib = fibonacci(40);

	while (coro_fib)
	{
		int value = coro_fib.get();

		std::cout << "fib value is " << value << std::endl;
	}

	return 0;
}
*/

struct promise;

struct MyCoroutine : std::coroutine_handle<promise>
{
	using promise_type = ::promise;
};
struct promise
{
	MyCoroutine get_return_object() { return { MyCoroutine::from_promise(*this) }; }
	auto initial_suspend() { return std::suspend_always{}; };
	auto final_suspend() noexcept { return std::suspend_always{}; }
	void unhandled_exception() {}
	void return_void(){}
	//void return_value(int v) { _value = v; }

public:
	int get() { return _value; }
private:
	int _value;
};

struct awaitable
{
	bool await_ready()
	{
		std::cout << "   awaitable::await_ready called\n";
		return false;
	}

	void await_suspend(std::coroutine_handle<> h)
	{
		std::cout << "   awaitable::await_suspend called\n";
		h.resume();
	}

	auto await_resume()
	{
		std::cout << "   awaitable::await_resum called\n";
		return 666;
	}
};

MyCoroutine coroFunc(void)
{
	std::cout << "   coroFunc: co_awaot awaitable\n";
	co_await awaitable{};
	std::cout << "   coroFunc: return\n";
}

/*
#include "MyCoroutine.h"

int main()
{
	std::cout << "main: create coroutine\n";

	MyCoroutine coro = coroFunc();

	std::cout << "main: resume coroutine\n";

	coro.resume();

	std::cout << "main: finished\n";

	return 0;
}

	//main: create coroutine
	//main: resume coroutine
	//   coroFunc: co_awaot awaitable
	//   awaitable::await_ready called
	//   awaitable::await_suspend called
	//   awaitable::await_resum called
	//   coroFunc: return
	//main: finished
*/