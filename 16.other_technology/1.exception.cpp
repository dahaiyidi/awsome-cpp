#include <iostream>

class Base
{};

class Derive: public Base
{};

void f1()
{
    throw 111;
    // throw Derive{};
    std::cout << "aaaaa" << std::endl;
}

void f2()
{
    try
    {
        f1();

    }
    // catch 语句块的匹配按照从上到下进行
    catch(int e) // 异常对象， 异常对象会在栈展开过程中被保留，并最终传递给匹配的 catch 语句
    {
        std::cout << "int exception is catched in f2. " << e << std::endl;
        throw;  // 在 catch 中调用 throw 继续抛出相同的异常
        // 如果throw;并不被包含在catch内部的话，则程序会直接终止
    }
    catch(int e2) // 语法无问题，但是永远不会执行到
    {
        std::cout << "e2 double exception is catched in f2. " << e2 << std::endl;
    }
    catch(double e) // double不能匹配到int, 但是const int可以匹配int, 基类引用可以匹配派生类的对象，指针可以匹配对应的数组或函数
    {
        std::cout << "double exception is catched in f2. " << e << std::endl;
    }
    catch(Base& e)   // throw Derive{};  发现可以初始化Base&a，则选择这个catch
    {
        std::cout << "Base exception is catched in f2. " << std::endl;
    }
    catch(Derive& e)
    {
        std::cout << "Base exception is catched in f2. " << std::endl;
    }
    catch(...)  // 使用 catch(...) 匹配任意异常, 放置在最后
    {
        std::cout << "exception is catched in f2. " << std::endl;
    }

}

void f3()
{
    try
    {
        f2();

    }
    catch(int)
    {
        std::cout << "exception is catched in f3." << std::endl;
    }
}

int main()
{
    //  异常处理
    // C++ 中的处理方法：通过关键字 try/catch/throw 引入异常处理机制
    // 异常触发时的系统行为 栈展开 
    // - 抛出异常后续的代码不会被执行
    // - 局部对象会按照构造相反的顺序自动销毁
    // - 系统尝试匹配相应的 catch 代码段
    //      如果匹配则执行其中的逻辑，之后执行 catch 后续的代码
    //      如果不匹配则继续进行栈展开，直到 跳出 “ ” main 函数，触发 terminate 结束运行
    
    // 在一个异常未处理完成时抛出新的异常会导致程序崩溃
    // – 不要在析构函数或 operator delete 函数重载版本中抛出异常
    // – 通常来说， catch 所接收的异常类型为引用类型
    try
    {
        f3();
    }

    catch(int)
    {
        std::cout << "exception is occured." << std::endl;
    }

    std::cout << "end..." << std::endl;
}