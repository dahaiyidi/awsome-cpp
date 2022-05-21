#include <iostream>
#include <string>
#include <thread>
#include <windows.h>
#include <chrono>
#include <vector>
#include <list>
#include <mutex>

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
		for (int i = 0; i < 1000; ++i)
		{
			std::cout << "insert" << i << std::endl;
			std::unique_lock<std::mutex> ulock1(mymutex1);
			l.push_back(i);
			std::cout << "size" << l.size() << std::endl;
			//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			my_cond.notify_one(); // 把wait()的线程唤醒, 也不一定被唤醒成功.
			//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}
	void out()
	{

		for (int i = 0; i < 1000; ++i)
		{
			//if (!l.empty())  // 双重检查,提高效率,避免每次都需要上锁,如果l为空,则没有必要上锁.
			//{
			//	std::unique_lock<std::mutex> ulock1(mymutex1);

			//	//mymutex2.lock();
			//	if (!l.empty())
			//	{
			//		int command = l.front();
			//		std::cout << "pop" << std::endl;
			//		l.pop_front();
			//	}
			//	else
			//	{
			//		std::cout << "empty!" << std::endl;
			//	}
			//}

			while (true)
			{
				std::unique_lock<std::mutex> ulock1(mymutex1);
				// 条件变量的wait中环境中，必须使用std::unique_lock。

				// wait, 如果第二个参数的返回值是false,wait将解锁,并堵塞到本行. 堵塞到其他某个线程调用notify_one成员函数为止. 
				// 如果第二个参数是true,则继续执行.
				// 如果wait无第二个参数,则就和第二个参数lambda表达式返回false效果一样, 堵塞到本行,  堵塞到其他某个线程调用notify_one成员函数为止.
				// 
				// 其他线程可以用notify_one唤醒. 阻塞态就变为就绪态,开始重新尝试获取互斥量锁,如果获取不到,就会一直尝试获取. 如果拿到锁,加锁.然后,
				//   若lambda返回false, 则释放锁,开始新一轮的阻塞,登台再次唤醒. 
				//   如果lambda为true,wait返回,开始正常执行. 
				//   若没有第二个参数,wait返回,开始正常执行.
				my_cond.wait(ulock1, [this] {
					if (!l.empty())
						return true;
					return false;
					});
				l.pop_front();
				ulock1.unlock();  //因为unique_lock的灵活性,可以随时unlock
				std::cout << "pop, thread id: " << std::this_thread::get_id() << std::endl;

			}

		}
	}
private:
	std::list<int> l;
	std::mutex mymutex1;
	std::condition_variable my_cond;  // 条件变量对象

};

int main()
{
	// 条件变量std::condition_variable, wait(), notify_one()
	// 条件变量的wait中环境中，必须使用std::unique_lock。
	// std::condition_variable 是一个类,需要与互斥量合作.
	// notify_one()只能通知一个线程,但是哪个线程被通知无法控制.
	// 被wait阻塞的线程做相互影响的事情时,那么选择只通知一个.

	// notify_all()
	// 被wait阻塞的线程做互相不影响的事情时,可以使用notify_all(). 对阻塞的互相影响的线程使用notify_all() 通知,也没什么作用相当于notify_one(),比如本程序,out都需要同一个互斥量.


	A a;
	std::thread obj_in(&A::in, &a);
	std::thread obj_out(&A::out, &a);
	std::thread obj_out2(&A::out, &a);
	obj_in.join();
	obj_out.join();
	obj_out2.join();

	std::cout << "end.........." << std::endl;

}