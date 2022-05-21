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
	std::unique_lock<std::mutex> rtn_unique_lock()
	{
		std::unique_lock<std::mutex> tmp(mymutex1);
		return tmp;  // 返回局部对象tmp,导致i同生成临时的unique_lock对象,并调用移动构造函数.
	}
	void in()
	{
		for (int i = 0; i < 10000; ++i)
		{
			//mymutex1.lock();
			//std::unique_lock<std::mutex> ulock1(mymutex1, std::adopt_lock);
			//std::unique_lock<std::mutex> ulock1(mymutex1, std::try_to_lock);
			std::unique_lock<std::mutex> ulock1(mymutex1, std::defer_lock);
			//ulock1.lock();// 在std::defer_lock后可以lock
			//// 处理共享代码
			//ulock1.unlock();
			//
			//ulock1.lock();// 可以加unlock,也可以不用加unlock,因为使用了std::unique_lock

			// 当然可以尝试在std::defer_lock后加锁 ulock1.try_lock()
			
			//if (ulock1.owns_lock())  // 对应std::unique_lock<std::mutex> ulock1(mymutex1, std::try_to_lock);
			if (ulock1.try_lock())
			{
				l.push_back(i);
				std::cout << "insert" << i<< std::endl;
				std::cout << "size" << l.size() << std::endl;
			}
			else
				//拿不到锁,则可以先做其他的事情
			{
				std::cout << "cannot get mutex." << std::endl;
			}
			//std::unique_lock<std::mutex> ulock2= rtn_unique_lock(); //通过一个函数获得std::unique_lock<std::mutex>对象,里面就涉及了mutex所有权的转移.
		}
	}
	void out()
	{

		for (int i = 0; i < 10000; ++i)
		{
			std::unique_lock<std::mutex> ulock1(mymutex1);
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

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

		}
	}
private:
	std::list<int> l;
	std::mutex mymutex1;
	std::mutex mymutex2;

};
int main()
{
	//https://blog.csdn.net/qq_38231713/article/details/106092134
	// unique_lock比lock_guard更加灵活,效率差一些
	// unique_lock 的参数
	//		std::adopt_lock.在此之前要手动lock.  assume the calling thread already has ownership of the mutex 
	//		std::try_to_lock, 尝试锁定mutex,若没有锁定成功,也会立即返回,并不会阻塞在那里.在此之前不可手动lock. try to acquire ownership of the mutex without blocking
	//		std::defer_lock, 在此之前不可手动lock,初始化了一个没有加锁的mutex. do not acquire ownership of the mutex
	//try_lock() 在std::defer_lock之后尝试lock
	// release() 让unique_lock和mutex不再有关系. 返回管理的mutex对象指针,并释放所有权. 与unlock不同.
	//		std::unique_lock<std::mutex> ulock1(mymutex1);
	//		std::mutex* ptr = ulock1.release();
	//		ptr->unlock(); // 由于解除了unique_lock 与mymutex1的关系,需要自己unlock()

	// 锁住的代码少,粒度细,效率高
	// 锁住的代码少,粒度粗,效率低

	//unique_lock 所有权的传递
	//std::unique_lock<std::mutex> ulock1(mymutex1)代表ulock1拥有mymutex1的所有权
	//所有权可以转移:std::unique_lock<std::mutex> ulock2(std::move(ulock1))

	A a;
	std::thread obj_in(&A::in, &a);
	std::thread obj_out(&A::out, &a);
	obj_in.join();
	obj_out.join();

	std::cout << "end...\n";

}