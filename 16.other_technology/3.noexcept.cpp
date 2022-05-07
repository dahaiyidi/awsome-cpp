#include <iostream>

void fun() noexcept(true) //noexcept是限定符 noexcept(false) 标致可能抛出异常，  noexcept(true) 标致着不会抛出异常
// noexcept 不作为函数重载依据
// 在声明了 noexcept 的函数中抛出异常会导致 terminate 被调用，程序终止,即便写了catch，程序也会直接充值。
{
    // throw 123;
}

void fun3() noexcept(true)
{

}

void fun2() noexcept(noexcept(fun()) && noexcept(fun3()))
{
    fun();
    fun3();
}

class Base
{
public:
    virtual void fun() noexcept
    {}
};

class Derive : public Base
{
public:
    void fun() noexcept override  // 当在Base中是noexcept，则在Derive中也应该是noexcept，当Base是noexcept(false)时， 此处可以为noexcept，也可以是noexcept(false)
    {}
};

int main()
{
    // 描述函数是否会抛出异常
    //  如果函数不会抛出异常，则应表明以为系统提供更多的优化空间
    // ● C++ 98 的方式： throw() / throw(int, char)
    // ● C++11 后的改进： noexcept / noexcept(false)
    std::cout << noexcept(fun()) << std::endl; // noexcept 是操作符， 而不是限定符，接收一个表达式，根据表达式是否可能抛出异常返回 false/true

    try
    {
        fun();
    }
    catch(...)
    {
        std::cout << "exception is catched.\n";
    }

    // 函数指针、虚拟函数重写时要保持形式兼容
    // 函数指针
    void (*ptr)() noexcept = fun;  // fun 必须要为noexcept
    (*ptr)();
}