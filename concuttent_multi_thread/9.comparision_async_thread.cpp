#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <list>
#include <mutex>
#include <future>

int mythread()
{
	std::cout << "mythread() start, thread id: " << std::this_thread::get_id() << std::endl;
	return 888;
}

int main()
{
	std::cout << "main thread start, thread id: " << std::this_thread::get_id() << std::endl;
	std::future<int> result = std::async(mythread);  // 创建异步任务
	//std::future<int> result = std::async(std::launch::async, mythread);  // 不会创建新的线程，直到get，wait才执行，而且如果后面没有get或者wait,则函数就不会被执行.
	//std::cout << result.get() << std::endl;
	// std::launch::deferred, 延迟调用， std::launch::async 强制创建一个线程
	// std::launch::async： 强制异步任务创建新线程，并在之上进行。
	// 如果没有参数， 则是std::launch::async | std::launch::deferred: 意味着async的行为可能是（两者选其一）：创建新线程并立即执行，或者，没有创建新线程且延迟到get\ wait 才执行。 系统自行确定是异步（创建新线程）还是同步(不创建新线程)。
	// 

	// std::async（创建异步任务） 和std::thread(创建线程)
	// std::async：可能不会创建新线程（如，无参数，或者使用std::launch::deferred）。 很容易拿到线程入口函数的返回值。
	// std::thread 若系统资源紧张，则创建线程可能失败，执行std::s=thread 时整个程序崩溃
	// 线程数量一般不超过100-200
	

	// 通过 std::future_status判断std::async是否创建了新线程
	std::future_status status = result.wait_for(std::chrono::milliseconds(0));
	if (status == std::future_status::deferred)
	{
		// 未创建新线程
		std::cout << "no thread is created. " << std::endl;
		std::cout << result.get() << std::endl;  // 其实子线程没有创建，在主线程直接执行调用的函数。

	}
	else
	{
		// 创建了新线程
		std::cout << "new thread is created. " << std::endl;
		std::cout << result.get() << std::endl;  // 其实子线程没有创建，在主线程直接执行调用的函数。
	}

}