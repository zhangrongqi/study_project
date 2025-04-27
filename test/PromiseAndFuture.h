#pragma once
#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <mutex>

namespace PromiseAndFuture
{
	std::mutex cout_mutex;

	void compute_pi(const long long num_steps, std::promise<double>&& res_promise)
	{
		try
		{
			if (0 == num_steps)
			{
				throw std::runtime_error("num_steps ²»ÄÜÊÇ 0");
			}
		}
		catch (...)
		{
			res_promise.set_exception(std::current_exception());
			return;
		}

		auto start_time = std::chrono::steady_clock::now();
		double step = 1.0 / num_steps;
		double sum = 0.0;

		for (long long i = 0; i < num_steps; ++i)
		{
			double x = (i + 0.5) * step;
			sum += 4.0 / (1.0 + x * x);
		}

		res_promise.set_value(sum * step);

		auto end_time = std::chrono::steady_clock::now();

		auto duration_time = end_time - start_time;

		std::lock_guard<std::mutex> lock(cout_mutex);
		std::cout << "time cost " << std::chrono::duration_cast<std::chrono::milliseconds>(duration_time).count() << " ms\n";
	}

	void display_pi(std::future<double>&& display_future)
	{
		double pi;
		try
		{
			pi = display_future.get();
		}
		catch (const std::runtime_error& e)
		{
			std::lock_guard<std::mutex> lock(cout_mutex);
			std::cout << e.what() << '\n';
			return;
		}

		std::lock_guard<std::mutex> lock(cout_mutex);
		std::cout << "pi is " << pi << '\n';
	}

	void display_pi_share(std::shared_future<double> display_future)
	{
		double pi;
		try
		{
			pi = display_future.get();
		}
		catch (const std::runtime_error& e)
		{
			std::lock_guard<std::mutex> lock(cout_mutex);
			std::cout << e.what() << '\n';
			return;
		}

		std::lock_guard<std::mutex> lock(cout_mutex);
		std::cout << "pi is " << pi << '\n';
	}
}


//#include "PromiseAndFuture.h"
//
//int main()
//{
//	constexpr long long steps = 1000000000;
//	constexpr long long steps = 000000000;
//
//	std::promise<double> promise_pi;
//
//	//auto future_pi = promise_pi.get_future();
//
//	//auto future_pi_share = promise_pi.get_future().share();
//
//	std::shared_future<double> future_pi_share{promise_pi.get_future()};
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