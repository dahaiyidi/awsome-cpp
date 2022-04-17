#include <iostream>

struct Str
{
    void fun(int x) // 与下面的函数形成重载，由于this指针的类型是不同的
    // 不加const时， this是 Str * const
    {

    }
    void fun(int x) const // 不对类内部的成员修改此时this的类型是const Str * const
    {
        std::cout << x << std::endl;
        std::cout << this->x << std::endl;
    }
    int x;
};