#include <iostream>

struct Str
{
    Str()
    {
        throw 111;
    }
};

struct Str2
{
    ~Str2()
    {
        std::cout << "Str2::~Str2 is called.\n";

    }
};

struct Cla
{
public:
    Cla()
    try : m_mem()  // 使用 function-try-block保护初始化逻辑, 需要显式写出初始化列表
    // 构造函数中抛出异常：● 已经构造的成员会被销毁，但类本身的析构函数不会被调用
    {

    }
    catch(int)
    {
        std::cout << "exception is catched at Cla::Cla\n";
        // 当使用，function-try-block时， 编译期会隐式的添加throw; 否则，在main函数中再次使用该对象，则直接崩溃。
    }
    ~Cla()
    {
        std::cout << "Cla::~Cla is called.\n";
    }
private:
    Str2 m_2;  // 如果放置在Str m_mem; 后，则会先构造m_mem
    Str m_mem;
};

void fun()
try
{
    throw 123;
}
catch(...)
{
    std::cout << "123\n";
}

// 函数try
void fun(Str x)
try // 并不会捕获Str {}产生的异常，因为此异常是在调用方的语境中抛出的，也就是说需要捕获fun(Str{});处的异常，不是执行fun函数体时产生的异常。
{
    throw 333;
}
catch(...)
{
    std::cout << "333\n"; // 不会隐式的含有throw;
}

int main()
{
    try
    {
        Cla obj;
    }
    catch(int)
    {
        std::cout << "exception is catched at main\n";
    }

    fun();

    try
    {
        fun(Str{});
    }
    catch(...)
    {
        std::cout << "444\n";
    }

    std::cout << "" << std::endl;

}