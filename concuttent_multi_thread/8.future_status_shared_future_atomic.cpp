#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <list>
#include <mutex>
#include <future>

int mythread(int n)
{
	std::cout << "mythread() start, thread id: " << std::this_thread::get_id() << std::endl;
	std::cout << n << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	std::cout << "mythread() end, thread id: " << std::this_thread::get_id() << std::endl;
	return 888;
}

void mythread2(std::shared_future<int> &tmpf)
{
	std::cout << "void mythread2(std::shared_future<int> &) start, thread id: " << std::this_thread::get_id() << std::endl;
	std::cout << "void mythread2, res: " << tmpf.get() << std::endl;  // future的get()源码是std::move, 则get只能调用一次, shared_future可以执行多次get
	std::cout << "void mythread2, res: " << tmpf.get() << std::endl;  // 
	std::cout << "void mythread2, res: " << tmpf.get() << std::endl;  //
}

//int g_mycout = 0;
std::atomic<int> g_mycout = 0;  // 具备原子操作的int
//std::mutex g_mymutex; 

void mythread3()
{
	for (int i = 0; i < 1000000; ++i)
	{
		//g_mymutex.lock();
		++g_mycout;  // 原子操作， 可以写为g_mycout++,但不可以写g_mycout = g_mycout + 1
		//g_mymutex.unlock();
	}
}

std::atomic<bool> g_ifend = false;

void mythread4()
{
	while (!g_ifend)
	{
		std::cout << "start thread id:" << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));	
	}
	std::cout << "end thread id:" << std::this_thread::get_id() << std::endl;
}

int main()
{
	// std::future 其他成员函数
	std::cout << "main, thread id: " << std::this_thread::get_id() << std::endl;
	std::future<int> result = std::async(std::launch::deferred, mythread, 1);
	std::cout << "continure...." << std::endl;
	int def = 0;
	//std::cout << result.get() << std::endl;  // 卡在这里,等待mythread执行完毕. 

	// std::future_status
	std::future_status status = result.wait_for(std::chrono::milliseconds(3000));
	if (status == std::future_status::timeout)
	{
		// 超时，表示线程还没有执行完毕
		std::cout << "timeout." << std::endl;
	}
	else if (status == std::future_status::ready)
	{
		// 线程执行完毕
		std::cout << "ready. " << result.get() << std::endl;
	}
	else if (status == std::future_status::deferred)
	{
		// 如果async第一个参数设置为std::launch::deferred.
		std::cout << "deferred. " << std::endl;  
		std::cout << result.get() << std::endl;  // 其实子线程没有创建，在主线程直接执行调用的函数。

	}

	// future的get()源码是std::move, 则get只能调用一次。要使用多次，可以使用shared_future
	// std::shared_future
	std::cout << "std::shared_future..." << std::endl;
	std::packaged_task<int(int)> mypt(mythread);
	std::thread t1(std::ref(mypt), 2);
	t1.join();

	//std::future<int> result2 = mypt.get_future();
	////std::shared_future<int> result2_s(std::move(result2));
	//// 或者
	//std::shared_future<int> result2_s(result2.share());

	// 或者直接从mypt生成shared_future
	std::shared_future<int> result2_s(mypt.get_future());
	//std::cout << "valid? " << result2.valid() << std::endl;
	std::thread t2(mythread2, std::ref(result2_s));
	t2.join();

	// 原子操作 std::atomic
	// 互斥量，多线程编程中保护共享数据
	// 有两个线程，对一个变量操作，一个线程读，另一个线程写。
	// 原子操作：不需要用到互斥量加锁（无锁）技术的多线程并发编程方式。 在多线程中，不会被打断的程序执行片段。 比互斥量效率更高。
	// 是不可分割的操作，要么完成，要么没有完成，没有中间状态。
	// 原子操作只适用于单个变量，而互斥量一般针对一段代码。
	// std::atomic 一般用于统计
	// ++, --, +=, &=..等类似的才支持原子操作
	std::cout << "std::atomic........" << std::endl;

	// 使用互斥量可以实现原子操作的效果
	std::thread obj1(mythread3);
	std::thread obj2(mythread3);
	obj1.join();
	obj2.join();
	std::cout << "g_mycount: " << g_mycout << std::endl;


	// std::atomic<bool>
	std::thread obj3(mythread4);
	std::thread obj4(mythread4);
	std::this_thread::sleep_for(std::chrono::milliseconds(4000));
	g_ifend = true; // 用原子操作，来控制线程的结束
	obj3.join();
	obj4.join();

	std::cout << "end......................" << std::endl;

	// 

}