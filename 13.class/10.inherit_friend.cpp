#include <iostream>

class Derive;

struct Base
{
    friend void fun2(const Derive&);
protected:
    int x = 10;
};

struct Derive : public Base
{
    // 此处友元无法访问继承来的x??? 实践证明是可以访问的.
    friend void fun(const Derive&);
private:
    int y = 20;
};

void fun(const Derive& val)
{
    std::cout << val.x << std::endl;
}

void fun2(const Derive& val)
{
    std::cout << val.x << std::endl;  // 基类的friend 可以访问派生类中的基类的相关成员.无法访问派生类独有的成员
    // std::cout << val.y << std::endl;  // 不可访问
}

int main()
{

    // 友元关系无法继承，但基类的友元可以访问派生类中基类的相关成员
    Derive d;
    fun(d);
    fun2(d);
}