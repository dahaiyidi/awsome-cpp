#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <list>
#include <mutex>
#include <future>

class A
{
public:
	int mythread(int mypar)
	{
		std::cout << "A::mythread() start, thread id: " << std::this_thread::get_id() << std::endl;
		std::cout << mypar << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "A::mythread() end, thread id: " << std::this_thread::get_id() << std::endl;
		return 888;
	}
};


int mythread(int mypar)
{
	std::cout << "mythread(int) start, thread id: " << std::this_thread::get_id() << std::endl;
	std::cout << mypar << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "mythread(int) end, thread id: " << std::this_thread::get_id() << std::endl;
	return 888;
}

std::vector<std::packaged_task<int(int)> > mytasks;

void mythread2(std::promise<int>& tmpp, int calc)
{
	calc++;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	int res = calc;
	tmpp.set_value(res); // 计算结果保存在tmpp
}

void mythread3(std::future<int>& tmpf)
{
	auto res = tmpf.get();
	std::cout << "mythread3 res: " << res << std::endl;
}

int main()
{
	// std::async std::future 创建后台任务并返回值
	// 希望线程返回一个结果
	//std::async 是函数模板,用来启动一个异步任务,返回std::future对象, std::future是类模板
	// 启动一个异步任务:自动创建一个线程并开始执行队形的线程入口函数,返回一个std::future对象.
	// std::future对象中就含有线程入口函数所返回的结果(线程返回的结果),我们可以通过调用future对象的成员函数get()获取. 
	// std::future提供了访问异步操作结果的机制,结果不能立即拿到,但未来等线程执行结束时,就可以拿到存储在future对象中的信息.
	// 
	//
	std::cout << "main, thread id: " << std::this_thread::get_id() << std::endl;
	std::future<int> result = std::async(mythread, 1);
	std::cout << "continure...." << std::endl;
	int def = 0;
	// std::future 对象的get()成员函数等待线程执行结束并返回值
	// 一直卡在get()直到拿到值.
	//get 只能调用一次
	std::cout << result.get() << std::endl;  // 卡在这里,等待mythread执行完毕. 
	//result.wait(); // 仅仅等待,不需要返回值

	//适应类的成员函数
	A a;
	std::future<int> result2 = std::async(&A::mythread, &a, 2); // &a 是A::mythread的第一个参数（也就是this），2是A::mythread第二个参数对应int mypar
	std::cout << result2.get() << std::endl;  


	
	// 通过向std::async() 传递一个参数，参数类型是std::launch 类型（枚举类型）来达到特殊的目的。
	// std::launch::deferred， 线程入口函数调用被延迟到std::future 的wait() 或get()才调用， 如果没有wait,get, 则线程根本就不会创建。
	// 
	std::cout << "std::launch::deferred...." << std::endl;
	std::future<int> result3 = std::async(std::launch::deferred, &A::mythread, &a, 3); // &a 是A::mythread的第一个参数（也就是this），2是A::mythread第二个参数对应int mypar
	std::cout << result3.get() << std::endl;  // 此时才创建线程

	//std::launch::async 在调用async函数的时候就开始创建线程 
	//std::cout << "std::launch::async...." << std::endl;
	//std::future<int> result4 = std::async(std::launch::async, &A::mythread, &a, 4); // 立即启动线程

	// 如果没有参数， 则是std::launch::async | std::launch::deferred: 意味着async的行为可能是（两者选其一）：创建新线程并立即执行，或者，没有创建新线程且延迟到get\ wait 才执行。 系统自行确定是异步（创建新线程）还是同步(不创建新线程)。

	// std::packages_task 打包任务，把任务包装起来，是类模板，参数是可调用对象。
	std::cout << "std::packages_task...." << std::endl;
	std::packaged_task<int(int)> pt(mythread);
	// lambda 
	//std::packaged_task<int(int)> pt([](int mypar)
	//	{
	//		std::cout << "mythread(int) start, thread id: " << std::this_thread::get_id() << std::endl;
	//		std::cout << mypar << std::endl;
	//		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//		std::cout << "mythread(int) end, thread id: " << std::this_thread::get_id() << std::endl;
	//		return 888;
	//	});
	std::thread t1(std::ref(pt), 5);
	t1.join();
	std::future<int> result5 = pt.get_future();
	std::cout << result5.get() << std::endl;

	// std::packaged_task包装的对象可直接调用, 相当于简单的函数调用
	std::cout << "std::packaged_task is called directly." << std::endl;
	std::packaged_task<int(int)> pt2(mythread);
	pt2(6);  // 相当于简单的函数调用
	std::future<int> result6 = pt2.get_future();
	std::cout << result6.get() << std::endl;

	// 容器
	std::cout << "std::packaged_task --- vector." << std::endl;

	std::packaged_task<int(int)> pt3(mythread);
	mytasks.push_back(std::move(pt3));
	std::packaged_task<int(int)> pt4;
	auto iter = mytasks.begin();
	pt4 = std::move(*iter);
	mytasks.erase(iter);
	pt4(7);  // 相当于简单的函数调用
	std::future<int> result7 = pt4.get_future();
	std::cout << result7.get() << std::endl;

	// std::promise 类模板
	// 在某个线程中给它赋值，然后在其他的线程中取出
	std::cout << "std::promise........." << std::endl;
	std::promise<int> myprom;  // 保存的值的类型为int
	std::thread t2(mythread2, std::ref(myprom), 180);
	t2.join();
	std::future<int> result8 = myprom.get_future(); // 用于获取线程返回值
	//std::cout << result8.get() << std::endl; // get只能调用一次

	// 在其他子线程中获取值
	std::thread t3(mythread3, std::ref(result8));
	t3.join();

	std::cout << "end......................" << std::endl;

	// 

}