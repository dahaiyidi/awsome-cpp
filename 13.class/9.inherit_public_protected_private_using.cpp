#include <iostream>

struct Base
{
public:
    int x;
    void fun(int){}
private:
    int y;
protected:
    int z;
    void fun(){}
    Base() = default;
    Base(int){}

    virtual void fun2()
    {
        std::cout << "fun2()\n";
    }
    virtual void fun2(int)
    {
        std::cout << "fun2(int)\n";
    }
};

struct Derive : public Base
{
public:
    using Base::z;  // 由protected 转为 public
    using Base::fun;  // 代表了基类的两个函数void fun(int) 和 void fun()
    // using Base::y;  // 不可以,因为派生类无法访问
    using Base::Base;  //可以拿到基类所有的构造函数,可以直接拿来使用. 但无法改变基类构造函数的访问权限
    using Base::fun2;  // 将protected 转为public

    // 此时,有Base引入的fun2(), 和override的fun(int) 
    void fun2(int) override
    {
        std::cout << "new fun2(int)\n";
    }

private:
    using Base::x;
};

int main()
{
    // public 与 private 继承
    // – public 继承：描述 是一个 的关系 “ ”  几乎所有的程序用public继承就好了
    // – private 继承：描述 根据基类实现出 的关系 “ ”
    // – protected 继承：几乎不会使用

    // using  改变基类成员的访问权限
    Derive d;
    d.z;
    // d.x; // 不可调用已经由public 转为private
    d.fun();
    
    // Derive d2(2);  //using无法改变构造函数的访问权限

    // using 与部分重写
    d.fun2();
    d.fun2(3);  // 调用了override的fun2(int)
}