#include <iostream>
#include <string>
#include <thread>
#include <windows.h>
#include <chrono>
#include <vector>
#include <list>
#include <mutex>
#include <windows.h>

//#define __WINDOWSJQ_

// 本类用于自动释放windoes下临界区，防止忘记leave 而导致死锁，类似于std::lock_guard<std::mutex>
// 也叫做RAII类Resource Acquisition is initialization 资源获取即初始化，容器，智能指针都属于RAII
class CWinLock
{
public:
	CWinLock(CRITICAL_SECTION* pCritmp)
	{
		m_pCritical = pCritmp;
		EnterCriticalSection(m_pCritical);
	}
	~CWinLock()
	{
		LeaveCriticalSection(m_pCritical);
	}
private:
	CRITICAL_SECTION* m_pCritical;

};


class A
{
public:
	//void fun1()
	//{
	//	std::lock_guard<std::recursive_mutex> tmp(mymutex1);
	//	fun2();
	//}
	//void fun2()
	//{
	//	std::lock_guard<std::recursive_mutex> tmp(mymutex1);
	//}

	void in()
	{
		for (int i = 0; i < 1000; ++i)
		{
#ifdef __WINDOWSJQ_
			//EnterCriticalSection(&my_winsec);  
			//EnterCriticalSection(&my_winsec);  // 重复进入临界区
			CWinLock wlock(&my_winsec);
			l.push_back(i);
			//LeaveCriticalSection(&my_winsec);
			//LeaveCriticalSection(&my_winsec);

#else
			//mymutex1.lock();
			//std::lock_guard<std::recursive_mutex> lg(mymutex1);
			//fun1();  // 调用了3次lock

			//if (mymutex1.try_lock_for(std::chrono::milliseconds(100)))
			// 等价于
			if (mymutex1.try_lock_until(std::chrono::steady_clock::now() + std::chrono::milliseconds(100)))
			{
				std::cout << "insert" << i << std::endl;
				// 在特定时间内可以拿到锁
				l.push_back(i);
				mymutex1.unlock();
				std::cout << "size" << l.size() << std::endl;
			}
			else
			{
				// 在特定时间内未拿到锁

				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				std::cout << "in cannot get mutex." << std::endl;

			}


			//mymutex1.unlock();
#endif
		}
	}
	void out()
	{

		for (int i = 0; i < 1000; ++i)
		{
#ifdef __WINDOWSJQ_
			EnterCriticalSection(&my_winsec);
			if (!l.empty())
			{
				int command = l.front();
				std::cout << "pop" << std::endl;
				l.pop_front();
			}
			else
			{
				std::cout << "empty!" << std::endl;
			}
			LeaveCriticalSection(&my_winsec);
#else
			mymutex1.lock();
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));

			if (!l.empty())
			{
				int command = l.front();
				std::cout << "pop" << std::endl;
				l.pop_front();
			}
			else
			{
				std::cout << "empty!" << std::endl;
			}
			mymutex1.unlock();
#endif
		}
	}
	A()
	{
#ifdef __WINDOWSJQ_
	InitializeCriticalSection(&my_winsec); // 初始化
#endif

	}
private:
	std::list<int> l;
	//std::mutex mymutex1;
	//std::recursive_mutex mymutex1;
	std::timed_mutex mymutex1;
#ifdef __WINDOWSJQ_
	CRITICAL_SECTION my_winsec; // windows中的临界区，类似于c++11中的mutex
#endif
};

int main()
{
	// windows 临界区CRITICAL_SECTION
	// 在同一进程中，windows中的相同临界区变量代表的临界区可以多次进入，通过EnterCriticalSection， 调用了几次EnterCriticalSection，就需要调用几次LeaveCriticalSection
	// 这和c++中的互斥量不同，不允许多次lock。 但是可以lock, unlock, lock,unlock...
	// 自动析构

	// std::mutex 是独占互斥量 
	//多次lock, 会报错，则可以使用recursive_mutex允许同一线程同一互斥量多次lock。但是效率更低。所以应该首先想如何优化代码。


	// std::timed_mutex  带超时功能的独占互斥量
	// 	   try_lock_for() 不停地拿锁，等待一段时间，还没有拿到锁，则继续往下走
	// 	   try_lock_until() 参数是一个未来的时刻
	// std::recursive_timed_mutex  带超时功能的递归独占互斥量。也具有类似的函数。

	A a;
	std::thread obj_out(&A::out, &a);
	std::thread obj_in(&A::in, &a);
	obj_out.join();
	obj_in.join();

	std::cout << "end.........." << std::endl;

}