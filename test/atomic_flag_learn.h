#pragma once
#include <atomic>

// 自旋锁 
// cpu 消耗较高 适合临界区域代码执行耗时少的场合 谨慎使用自定义的自旋锁
class SpinLock
{
public:
	void lock()
	{
		// test_and_set 用于把表示设置为true 并返回原有的值
		while (flag.test_and_set(std::memory_order_acquire)) {}
	}

	void unlock()
	{
		// clear 清除标志 原子写操作
		flag.clear(std::memory_order_release);
	}

private:
	std::atomic_flag flag = ATOMIC_FLAG_INIT;
	//std::atomic_flag flag{};
};

/*
#include "atomic_flag_learn.h"
#include <future>
#include <iostream>
#include <mutex>
#include <chrono>

int main()
{
	SpinLock sp_lock;

	int count = 0;

	constexpr int MAX_NUM = 1000;

	auto inc = [&]()
		{
			for (int i = 0; i < MAX_NUM; ++i)
			{
				// SpinLock满足BasicLockable类型，可以使用lock_guard
				std::lock_guard<SpinLock>lock(sp_lock);
				++count;
			}
		};

	auto job1 = std::async(std::launch::async, inc);
	auto job2 = std::async(std::launch::async, inc);

	//job1.get();
	//job2.get();

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	std::cout << "count = " << count << std::endl;

	return 0;
} 
*/

#include <iostream>
#include <thread>
#include <chrono>

struct Channnel
{
	void getData()
	{
		std::cout << "[Consumer] Wait for fata ready\n";
		dataReady.wait(false);
		std::cout << "[Consumer] Data is: " << data << '\n';
		dataReady.clear();
	}

	void setData(const std::string& v)
	{
		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::cout << "[Producer] Write data\n";

		data = v;

		dataReady.test_and_set();
		dataReady.notify_one();
	}

private:
	std::atomic_flag dataReady = ATOMIC_FLAG_INIT;
	std::string data;
};

/*
#include "atomic_flag_learn.h"
#include <thread>

int main()
{
	Channnel ch;

	std::thread t1{ &Channnel::getData, std::ref(ch)};
	std::thread t2{ &Channnel::setData, std::ref(ch), "Hello world"};

	t1.join();
	t2.join();

	return 0;
}
*/