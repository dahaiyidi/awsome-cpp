#include <iostream>

void fun(int) // 与void fun(const int) 具有相同的级别，不能同时出现。
{
    std::cout << "::fun.\n";
}

namespace MyNS
{
    void fun(double); // 如果不写这句话，g()就会调用::fun(int)， 因为编译器编译到这里，只认识一个fun。可以参考匹配级别
    // int fun; 如果没有上一句，而添加这一句，则fun(3) 会尝试调用该fun,报错。 系统先进行纸面上的名称查找，变量名和函数名都是同一个名字。
    void g()
    {
        fun(3);  // 会调用MyNS::fun,虽然::fun接受int变量,看上去更符合，但是名称查找已经限制就要调用MyNS::fun(double)
    }

    void fun(double)
    {
        std::cout << "MyNS::fun.\n";        
    }
}

template <typename T>
void fun2(T x)
{
    g2(x); //虽然前面还没有看到g2的定义，但是不会报错。
    // 因为编译器在处理函数模板时，只check形式是否存在语法错误。在调用函数时才实例化函数，那时已经g2的定义了。
}

namespace MyNS2
{
    struct Str{};
    void g2(Str x)
    {
        std::cout << "MyNS2::g2" << std::endl;

    }
}

void fun3(int& )
{
    std::cout << "fun3(int& )\n";
}

void fun3(const int& x)  // 重载中的特殊规则：可以与上面的函数共同出现，虽然在同一个级别中。
// 常左值引用绑定到右值，非常左值引用不可绑定到右值！ 
{
    std::cout << "fun3(const int& )\n";
}

void fun4(int x, float y){}
void fun4(int x, double y){}

void fun5(bool x, float y){std::cout << "fun5(bool x, float y)\n";}
void fun5(int x, double y){std::cout << "fun5(int x, double y)\n";}

int main()
{
    MyNS::g(); // MyNS::fun
    MyNS2::Str obj;

    // 实参依赖查找（ Argument Dependent Lookup: ADL ）只对自定义类型生效
    g2(obj); // 会调用MySN2::g2() 并不会报错

    fun2(obj); // 正常运行会调用MySN2::g2()

    // 函数重载的特殊情况
    int x;
    fun3(x); // 调用void fun3(int& )，因为x是变量，我们期待函数有可能改变x的，所以选择了该函数
    fun3(3); // 调用void fun3(const int& x) 因为左值引用不能绑定到右值上，直接过滤了void fun3(int& )， 所以选择了该函数。
    // 常左值引用可以绑定到右值，非常左值引用不可绑定到右值！  https://zhuanlan.zhihu.com/p/99524127

    // fun4(1, 1); // 此时报错，因为对于两个fun4来说，级别都是1，3，无法区分

    fun5(true, 1.2); // 此时，fun5(bool x, float y)匹配级别为：1，3 ， fun5(int x, double y)匹配级别为 2，1
    // 此时已经违反了：函数包含多个形参时，所选函数的所有形参的匹配级别都要优于或等于其它函数。
    // 也就说对于这两个形参，没有一个函数是能绝对占优的。此时存在warning，但是不同的编译器有不同的实现。
    // 应避免出现类似的情况！！！可以修改为以下
    fun5(static_cast<int>(true), 1.2); // 此时可以避免歧义

}