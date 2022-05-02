// test.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <thread>

void myprint()
{
    std::cout << "sub process start" << std::endl;
    /*std::cout << "sub process start" << std::endl;*/
    std::cout << "sub process end" << std::endl;
}

class TA 
{
public:
    int m_i;

    //这里是一个bug
    //int& m_i;
    //TA(int &i):m_i(i)
    //{
    //    std::cout << "TA constructor is called." << std::endl;
    //}
    TA(int i) :m_i(i)
    {
        std::cout << "TA constructor is called." << std::endl;
    }

    //拷贝构造函数
    TA(const TA& ta): m_i(ta.m_i)
    {
        std::cout << "TA copy constructor is called." << std::endl;
    }
    
    //析构
    ~TA()
    {
        std::cout << "destructor is called." << std::endl;
    }

    void operator()() 
    {
        std::cout << "TA::operator start." << std::endl;
        std::cout << "m_i：" << m_i << std::endl;
        std::cout << "m_i：" << m_i << std::endl;
        std::cout << "m_i：" << m_i << std::endl;
        std::cout << "m_i：" << m_i << std::endl;
        std::cout << "m_i：" << m_i << std::endl;
        
        std::cout << "TA::operator end." << std::endl;       
    }

};

int main()
{
    //进程与线程---------------------------------
    // 进程就是运行起来的可执行程序
    // 每个进程都有一个主线程，且是唯一的
    // 线程：用来执行代码的，是执行代码的一条道路，一个新线程代表一条新的通路
    // 除了主线程之外，可以同通过自己写代码创建其他线程，其他线程走的是别的道路，干不同的事情。
    // 主线程是自动启动的，一个进程最少有一个线程（主线程）
    // 多线程(并发)
    // 线程并不是越多越好，每个线程都需要一个独立的栈空间(1M)线程之间切换要保存很多context。
    
    // 并发：多个独立任务同时进行、发生
    // 实现：多个进程实现并发，也可以在单独的进程中创建多个线程实现并发。优先考虑多线程技术手段。
    // 一个进程中的所有线程共享内存，全局变量，指针，引用都可以在线程之间传递
    // 共享内存带来新问题：数据一致性。

    // 线程优点：
    // 线程启动速度快，更轻量级
    // 系统资源开销更小，执行速度更快。共享内存。
    // 在c++之前，多线程代码不能跨平台
    // 使用多线程时，windows：CreateThread(), _beginthred(), _beginthredexe()创建线程。
    // linux中pthread_create()创建线程。当然也有跨平台的选择：POSIX thread(pthread)
    // c++11 本身就提供了多线程支持

    std::cout << "Hello World!\n"; // 实际上时主线程在执行，主线程从main()函数返回，则整个进程执行完毕。
    //主线程从main开始，自己创建的线程也需要从一个函数开始运行（初始函数，入口函数），函数运行完毕，则线程结束
    //进程是否执行完毕的标致是，主线程给是否执行完。一般情况下， 如果其他子线程还没有执行完毕，则子线程被操作系统强行中止。有例外，就是detach
    //detach: 主线程不和子线程汇合，主线程结束，不影响子线程。子线程与主线程失联，驻留后台实现。此时，子线程被c++运行时库接管，当子线程执行完毕后，由运行时库负责清理该线程的资源（守护线程）。


    //用函数创建线程
    std::thread myobj(myprint);  // 创建线程，入口是myprint(), 线程开始执行。

    //myobj.join(); // 阻塞主线程，让主线程等待子线程执行完毕，然后子线程与主线程汇合，主线程继续往下走
    //主线程等待子线程执行完后，主线程才能退出

    //myobj.detach(); // detach 后不可以再join

    //jionable 判断是否可以成功使用join()或detach()
    if (myobj.joinable())
    {
        myobj.join();
    }

    // 用类创建线程

    int i = 6;
    TA ta(i); // 如果类内的成员是引用，则主线程如果先结束，则局部变量i被销毁，则子进程肯定无法再使用i的引用。
    std::thread myobj2(ta);  // ta是一个可调用对象
    //仿函数(functor)，就是使一个类的使用看上去像一个函数。 其实现就是类中实现一个operator()，这个类就有了类似函数的行为，就是一个仿函数类了
    myobj2.join();
    //myobj2.detach();  
    //主线程先结束，不用担心ta是局部对象的问题，因为在使用类对象创建子线程时，类对象是被复制到子线程中的。
    //只要TA类中没有引用，没有指针

    //用lambda表达式创建线程
    auto mylamthread = [] {
        std::cout << "mylamthread" << std::endl;
    };
    std::thread myobj4(mylamthread);
    myobj4.join();

    std::cout << "end." << std::endl;
}