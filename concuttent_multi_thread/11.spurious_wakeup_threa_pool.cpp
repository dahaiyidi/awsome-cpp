#include <iostream>
#include <string>
#include <thread>
#include <windows.h>
#include <chrono>
#include <vector>
#include <list>
#include <mutex>
#include <windows.h>


class A
{
public:
	std::atomic<int> atm;
	A()
	{
		atm = 0; // 原子操作，不能拷贝复制，拷贝构造
		// 但是，可以以原子方式读load()
		std::atomic<int> atm2(atm.load());
		auto atm3(atm.load());
		// 原子方式写, store()
		atm2.store(12);

	}
	void in()
	{
		for (int i = 0; i < 1000; ++i)
		{
			++atm;
			//std::cout << "insert" << i << std::endl;
			//std::unique_lock<std::mutex> ulock1(mymutex1);
			//l.push_back(i);
			//std::cout << "size" << l.size() << std::endl;
			//my_cond.notify_one(); // 把wait()的线程唤醒, 也不一定被唤醒成功.
		}
	}
	void out()
	{
		while (true)
		{
			std::cout << atm << std::endl; // 读atm是原子操作，但是整句话不是原子操作
		}

		//for (int i = 0; i < 1000; ++i)
		//{

		//	while (true)
		//	{
		//		std::unique_lock<std::mutex> ulock1(mymutex1);
		//		my_cond.wait(ulock1, [this] { 
		//			if (!l.empty())
		//				return true;
		//			return false;
		//			});  // // 此处利用lambda处理虚假唤醒的情况。
		//		l.pop_front();
		//		ulock1.unlock();  //因为unique_lock的灵活性,可以随时unlock
		//		std::cout << "pop, thread id: " << std::this_thread::get_id() << std::endl;

		//	}

		//}
	}
private:
	std::list<int> l;
	std::mutex mymutex1;
	std::condition_variable my_cond;  // 条件变量对象

};

int main()
{
	// 虚假唤醒，如push了一个元素，但是调用了多次norify_one，或者使用了notify_all， 恰好有超过一个线程在wait同一个std::condition_variable，则有的线程会被虚假唤醒。
	// 	  wait, norify_one, notify_all
	// 在wait中，利用第二参数，写lambda处理虚假唤醒的情况。


	// 线程池:把一堆线程放到一起统一管理，统一调度，循环利用线程的方式
	// 不可能为每个用户分配一个线程
	// 程序稳定性：偶尔就创建一个线程的代码是不安全的。
	// 实现： 
	// 在程序启动时，一次性创建好一定数量的线程
	// 一般来讲，2000个线程是极限。
	// 线程数量不要超过500
	

	A a;
	std::thread obj_out(&A::out, &a);
	std::thread obj_in(&A::in, &a);
	std::thread obj_in2(&A::in, &a);
	obj_out.join();
	obj_in.join();
	obj_in2.join();

	std::cout << "end.........." << std::endl;

}