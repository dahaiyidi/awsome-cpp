#include <iostream>

struct Base
{
    Base()
    {
        std::cout << "Base default constructor is called." << std::endl;
    }

    Base(int)
    {
        std::cout << "Base(int) constructor is called." << std::endl;
    }

    Base(const Base& val)
    {
        std::cout << "Base copy constructor is called." << std::endl;
    }

    Base& operator= (const Base&)
    {
        std::cout << "Base assignment is called." << std::endl;
        return *this;
    }

    ~Base()
    {
        std::cout << "Base destructor is called." << std::endl;
    }
};

struct Derive : Base
{
    Derive() = default;
    Derive(int x)
        : Base(x)
    {
        
    }
    ~Derive()
    {
        std::cout << "Derive destructor is called." << std::endl;
    }
};

int main()
{
    // 派生类[合成]的缺省构造函数会隐式的调用基类的缺省构造函数.如果不是合成的则会调用基类的缺省构造函数.
    Derive d;
    // 派生类[合成]的缺省copy构造函数会隐式的调用基类的缺省copy构造函数.如果不是合成的则会调用基类的缺省构造函数.
    Derive x(d);
    // 派生类[合成]的赋值函数将隐式调用基类的赋值函数
    x = d;

    // 派生类的析构函数会调用基类的析构函数

    // 派生类的其它构造函数将隐式调用基类的缺省构造函数
    std::cout << "派生类的其它构造函数将隐式调用基类的缺省构造函数" << std::endl;
    Derive d2(2); // 此处会调用Base default constructor, 因为不同的类的参数可能是不同的,则直接调用基类的缺省构造函数
    // 所有的特殊成员函数在显式定义时都可能需要显式调用基类相关成员
    // 在初始化列表中显式的调用, : Base(x), 此时即可调用基类的Base(int) constructor
    // 通过c++ indights 可以知道,如果没有显式的写明调用基类的哪个构造函数,则调用没有参数的基类构造函数,就是基类的缺省构造函数.
    // 其他的各种拷贝构造,拷贝赋值,也是类似的. 只要是自己定义的函数,就需要显式的调用基类的相关成员
    
    // 构造与销毁顺序
    // – 基类的构造函数会先调用，之后才涉及到派生类中数据成员的构造
    // – 派生类中的数据成员会被先销毁，之后才涉及到基类的析构函数调用

    std::cout << "----------end" << std::endl;

}