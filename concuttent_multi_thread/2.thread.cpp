#include <iostream>
#include <string>
#include <thread>
#include <windows.h>
#include <chrono>
class A
{
public:
    mutable int m_i;  // mutable 代表可以修改，即便在const 函数中。
    //类型转换构造函数，可以将int转化为A
    A(int a) :m_i(a)
    {
        std::cout << "constructor" << this << ", threadid = " << std::this_thread::get_id() << std::endl;
    }
    A(const A& a): m_i(a.m_i)
    {
        std::cout << "copy constructor" << this << ", threadid = " << std::this_thread::get_id() << std::endl;
    }
    ~A()
    {
        std::cout << "destructor" << this << ", threadid = " << std::this_thread::get_id() << std::endl;
    }

    void thread_work(int n)
    {
        std::cout << "sub thread thread_work." << this << ", threadid = " << std::this_thread::get_id() << std::endl;
    }
};
//void myprint(const int& i, char* pmybuf)
void myprint(const int i, const std::string& pmybuf)
{
    // 不能传引用，不能传指针（std::thread 都会采用值传递）
    // 此处，i并不是mavar的引用，实际是值传递，也就是说是安全的。(当使用类创建线程时，类中有引用成员的，引用成员也是不安全因素【第一篇文章已经写了】，因为没有深copy？？)
    // 此时pmybuf就是mybuf数组的地址（实际上是传递了一个地址过来），则此时是不安全的。
    // 
    // const引用：
    //非const引用只能绑定到与该引用同类型的对象，
    // const引用则可以绑定到不同但相关的类型的对象或绑定到左值，同时const引用可以初始化为不同类型的对象或者初始化为右值，如字面值常量。例如：
    //    int i = 42;
    //// legal for const references only
    //const int& r = 42;//初始化为右值
    //const int& r2 = r + i;//同样的初始化对于非const引用却是不合法的，而且会导致编译时错误。
    //double dval = 3.14;
    //const int& ri = dval;//不同类型对象，相当于int temp = dval; const int& ri = temp; 
    std::cout << i << std::endl;
    std::cout << pmybuf << std::endl;
    return;
}

void myprint2(const int i, const A pmybuf)
{
    std::cout << "&pmybuf:" <<  &pmybuf << std::endl;
}

void myprint3(const A& pmybuf)
{
    pmybuf.m_i = 199; 
    std::cout << "sub thread myprint3, parameter address:" << &pmybuf << std::this_thread::get_id() << std::endl;
}
void myprint4(std::unique_ptr<int> p)
{
    std::cout << "sub thread myprint4, parameter address:" << std::this_thread::get_id() << std::endl;
}
int main()
{
    // 传递int简单类型参数，建议值传递
    // 如果传递类对象，应该避免隐式类型转换。应该使用显式类型转换，创建临时对象，在函数形参里面，使用&来接收，避免多次重复创建对象。
    // 使用detach会出现很多坑，使用join则安全很多。
    // std::thread的源码去除了引用和const状态，形成了默认按值传参的处理方式。记住是传值的，就能理解所有问题。http://www.dudurun.com/blog/5 
    // 但是使用std::ref可以实现引用传参的效果。
    // 
    // 线程id，每个线程实际上都对应了一个id数字。使用std::this_thread::get_id()获取
    // 
    // 
    // 传递临时对象作为线程参数
    int mvar = 1;
    int& mvary = mvar;
    char mybuf[] = "this is a test!";
    //std::thread myobj(myprint, mvar, mybuf);// 存在可能：在使用detach时，mybuf被回收了（main函数执行完毕了），还用mybuf转string。
    //std::thread myobj(myprint, mvar, std::string(mybuf)); // 直接转化为string对象，可以保证安全。
    // 隐式类型转化是不安全的.可能在主线程结束后，隐式转换还没有开始，mybuff就已经失效了，这样依然会产生不可预料的结果。
    ////myobj.join();
    //myobj.detach();

    //int mvar2 = 2;
    ////在创建线程的同时构造临时对象的方法传递参数是可行的。
    //std::thread myobj2(myprint2, mvar, A(mvar2)); // 在使用detach时，一定要构造临时对象作为参数传递给线程

    //myobj2.detach();

    //std::cout << "main thread id:" << std::this_thread::get_id() << std::endl;

    //std::thread myobj3(myprint3, A(mvar)); // 结果显示：如果是隐式转换，在子线程中创建A类对象。 使用了显式类型转换，在主线程中就完成了A类对象构造。
    //myobj3.join();

    //A a(2);
    ////std::thread myobj4(myprint3, a);
    //std::thread myobj4(myprint3, std::ref(a));  // 可以实现”引用“的目的

    //myobj4.join();
    //std::cout << "--------------" << a.m_i << std::endl;

    //传入智能指针
    //std::unique_ptr<int> p(new int(100));
    //std::thread obj5(myprint4, std::move(p));  // unique_ptr 不能copy只能move
    ////如果使用 detach则还是有可能出现问题，可能在主线程中已经释放了内存，但是子线程还指向了被系统回收的内存。此时必须要使用join
    //obj5.join();


    //传入类内成员函数
    A a2(3);
    std::thread obj6(&A::thread_work, a2, 15);
    obj6.join();

    //std::this_thread::sleep_for(std::chrono::seconds(1));


    std::cout << "end..." << std::endl;
}