#include <iostream>
#include <string>
#include <thread>
#include <windows.h>
#include <chrono>
#include <vector>
#include <list>
#include <mutex>

std::mutex resource_mutex;
std::once_flag g_flag;


class A  //单例类
{
private:
	A() {} //构造函数是私有化的
	static A* m_instance;
	static void createInstance()  // 只被调用一次
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		m_instance = new A();
		std::cout << "A::createInstance() is called." << std::endl;
		static Clear cl;
	}
public:
	static A* getInstance()
	{
		//if (m_instance == NULL)// 双重锁定(检查)  
		//	// 本线程2,即便判断了m_instance == NULL,也有可能其他线程(线程1)正要new呢,正在new的线程1已经锁定了mutex,完成了new后, 此刻m_instance != NULL
		//	// 然后本线程2获得mutex,再次检查m_instance == NULL,此时刚好不再成立,则不会再new
		//	// 然后其他还没有判断过第一层m_instance == NULL的线程,均会得到m_instance != NULL的结果
		//{
		//	std::unique_lock<std::mutex> ulock(resource_mutex);  //如果没有双重锁定,会导致程序效率地下,因为每一次调用都需要锁.
		//	if (m_instance == NULL)
		//	{
		//		m_instance = new A();
		//		static Clear cl;
		//	}

		//}

		// 也可以使用std::call_once() 控制.
		std::call_once(g_flag, createInstance);
		return m_instance;
	}
	~A()
	{
		std::cout << "A::~A() is called." << std::endl;
	}

	void fun()
	{
		std::cout << "A::fun is called." << std::endl;
	}

	// 嵌套类,用来释放对象
	class Clear
	{
	public:
		~Clear()
		{
			if (A::m_instance)
			{
				delete A::m_instance;
				A::m_instance = NULL;
				std::cout << "Clear::~Clear() is called. delete A::m_instance" << std::endl;
			}
		}

	};

};
//类静态变量初始化
A* A::m_instance = NULL;

// 线程入口函数
void tfun()
{
	std::cout << "sub thread start." << std::endl;
	A* p = A::getInstance();
}



int main()
{
	// 设计模式
	// 单例设计模式, 在这个那个项目中,某个类只能创建一个对象. 
	// 将构造函数设置为private, 调用成员函数构造一个对象,返回对象指针,如果对象已经存在,则直接返回对象的指针.
	// 如果没有嵌套,则A的析构函数不会执行
	// 嵌套类,用来释放对象
	//A* p = A::getInstance();
	//A* p2 = A::getInstance();
	//p->fun();
	//A a;  单例模式不可以这样创建对象,只能通过调用A::getInstance();

	// 最好在主线程中创建A对象.如果在子线程中创建A对象,则会有问题,因为可能有多个线程, 可能m_instance = new A();被调用多次.
	// 使用双重锁定(检查)
	// 
	// std::call_once() 保证函数只被调用一次.具备互斥量的能力,效率比互斥量更高.
	// 需要与std::once_flag结构体结合使用,起到标记的作用.
	std::cout << "multi thread with singleton calss........." << std::endl;

	std::thread t1(tfun);
	std::thread t2(tfun);
	t1.join();
	t2.join();

	



	std::cout << "end.........." << std::endl;


}