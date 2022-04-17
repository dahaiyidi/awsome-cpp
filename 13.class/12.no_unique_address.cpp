#include <iostream>

struct Base
{
    void fun()
    {

    }
};

struct Derive: public Base
{
    int x;
};

struct Derive2
{
    int x;
    [[no_unique_address]] Base b;
};

int main()
{
    std::cout << sizeof(Base) << std::endl;  //1.
    std::cout << sizeof(Derive) << std::endl;  // 4. 空基类优化,使的空间仍然只为int的大小(4).如果将Base作为Derive的一个成员(而不是继承自Base),则int大小为4, Base大小为1, 则大小为4+4

    // 原本我们只需要调用Base里卖的一些函数,而没有继承的意思(没有is的含义),引入了一个新的关键字 
    //  空基类优化与[[no_unique_address]] 属性 fromc++20
    std::cout << sizeof(Derive2) << std::endl;  // 4.空基类优化,使的空间仍然只为int的大小(4).如果将Base作为Derive的一个成员(而不是继承自Base),则int大小为4, Base大小为1, 则大小为4+4
}