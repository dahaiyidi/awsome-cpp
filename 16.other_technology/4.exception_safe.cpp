#include <iostream>
#include <stdexcept>
#include <memory>

void fun()
{
    throw std::runtime_error("Invalid input");
}

void fun2()
{
    // int *ptr = new int[3];
    // throw 12;
    // delete[] ptr; // 有可能存在内存泄漏，不是异常安全的代码
    // 应该把内存分配回收放在一个类中

    // 这是异常安全的代码
    // 异常安全是指当异常发生时，不会泄漏资源，也不会使系统处于不一致的状态。
    // 基本保证。抛出异常后，对象仍然处于合法（valid）的状态。但不确定处于哪个状态。
    // 强烈保证。如果抛出了异常，程序的状态没有发生任何改变。就像没调用这个函数一样。
    // 不抛异常保证。这是最强的保证，函数总是能完成它所承诺的事情。

    std::unique_ptr<int> ptr = std::make_unique<int>(3);
    throw 111;
}

int main()
{
    // 标准异常
    // – 不要滥用：异常的执行成本非常高. 不要把throw当成return来使用。
    // – 不要不用：对于真正的异常场景，异常处理是相对高效、简洁的处理方式
    // – 编写异常安全的代码
    // https://www.google.com/url?sa=i&url=https%3A%2F%2Fflylib.com%2Fbooks%2Fen%2F2.253.1%2Fstandard_library_exception_hierarchy.html&psig=AOvVaw2uefLXdFEjVaQ0TbIjDQa7&ust=1651975320629000&source=images&cd=vfe&ved=0CAwQjRxqFwoTCKDnrOOlzPcCFQAAAAAdAAAAABAD
    try
    {
        fun();
    }
    catch(std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }
}