#include <iostream>
#include <string>
#include <thread>
#include <windows.h>
#include <chrono>
#include <vector>
#include <list>
#include <mutex>

std::vector<int> g_v = { 1, 2, 3};
void print(int n)
{
	//std::cout << "print in sub thread." << n << std::endl;
	std::cout << "thread id:" << std::this_thread::get_id() << ' ' << g_v[0] << g_v[1] << g_v[2] << std::endl;
}

class A
{
public:
	void in()
	{
		for (int i = 0; i < 10000; ++i)
		{
			std::cout << "insert" << i<< std::endl;
			std::lock(mymutex1, mymutex2);
			std::lock_guard<std::mutex> guard1(mymutex1, std::adopt_lock); //有了std::adopt_lock,则不会再lock
			std::lock_guard<std::mutex> guard2(mymutex2, std::adopt_lock); //有了std::adopt_lock,则不会再lock
			//mymutex1.lock();
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
			//mymutex2.lock();
			l.push_back(i);
			std::cout << "size" << l.size() << std::endl;
			//mymutex1.unlock();
			//mymutex2.unlock();

		}
	}
	void out()
	{

		for (int i = 0; i < 10000; ++i)
		{
			//构造muguard对象时，执行了lock
			//在出作用域时，局部对象析构，在析构函数中unlock
			//因此可以使用{}控制std::lock_guard生命周期
			//std::lock_guard<std::mutex> myguard(mymutex);
			// 
			
			std::lock(mymutex1, mymutex2); // 同时锁住两个互斥量，避免产生死锁
			std::lock_guard<std::mutex> guard1(mymutex1, std::adopt_lock); //有了std::adopt_lock,则不会再lock
			std::lock_guard<std::mutex> guard2(mymutex2, std::adopt_lock); //有了std::adopt_lock,则不会再lock
			//mymutex1.lock();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			//mymutex2.lock();
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
			/*mymutex2.unlock();
			mymutex1.unlock();*/
		}
	}
private:
	std::list<int> l;
	std::mutex mymutex1;
	std::mutex mymutex2;

};
int main()
{
	//创建多个线程
	//多个线程执行顺序不确定
	/*std::vector<std::thread> ths;
	for (int i = 0; i < 10; ++i)
	{
		ths.push_back(std::thread(print, i));
	}

	for (auto i = ths.begin(); i != ths.end(); ++i)
	{
		i->join();
	}*/

	//数据共享
	//只读数据是安全稳定的。
	//有读有写。读和写不能同时进行。
	A a;
	std::thread obj_in(&A::in, &a);
	std::thread obj_out(&A::out, &a);
	obj_in.join();
	obj_out.join();

	// 互斥量 mutex是类对象，多个线程尝试用lock()成员函数加锁，但是只有一个线程能锁定成功。
	// 	   如果没有加锁成功，则流程卡在lock()处等待直到可以kock
	// 步骤：先lock(), 操作共享数据, unlock().
	//lock() 与unlock(）必须成对使用。
	//为了防止忘记unlock, 则可以使用std::lock_guard类模板。可以直接取代lock, unlock.
	

	//死锁,产生的条件：两个互斥量。
	//两个互斥量AB, 两个线程都需要同时lock AB, 而一个线程lock了A， 另外一个线程lock了B,此时产生死锁。

	// 死锁的解决方案:
	// 1)两个锁的顺序是一致的.
	// 2)使用std::lock() 一次就可以锁住两个及以上的互斥量. 如果所有的锁没有lock成功,则释放所有锁,防止死锁. 使用std::lock后还需要手动调用unlock
	// std::lock()结合std::lock_guard<std::mutex> guard1(mymutex1, std::adopt_lock)即可不用手动调用unlock

	// adopt_lock 	assume the calling thread already has ownership of the mutex 


	std::cout << "end...\n";

}