#include <iostream>
#include <utility>

template <typename T>
class B
{
public:
    void fun()
    {

    }
};

// 类模板特化
// 特化版本与基础版本可以拥有完全不同的实现
template <>
class B<int>
{
public:
    void fun2()
    {

    }
};

template <typename T, typename T2>
class C
{
public:
    void fun()
    {

        std::cout << "1\n";
    }
};

// 类模板支持部分特化
template <typename T>
class C<int, T>
{
public:
    void fun2()
    {
        std::cout << "2\n";
    }
};

template <typename T>
class B<T*>
{
public:
    void fun2()
    {
        std::cout << "B<T*>\n";
    }
};

template <typename T>
class B2
{
public:
    B2(T input)
    {
        // std::cout << "B<T*>\n";
    }
};

int main()
{
    // 类模板的（完全）特化，部分特化（偏特化）
    // 类模板的特化是非常重要的
    // 特化版本与基础版本可以拥有完全不同的实现
    B<int> x;
    x.fun2();

    // 部分特化
    std::cout << "部分特化" << std::endl;
    C<int, double> x1;
    x1.fun2();

    B<int*> x2;
    x2.fun2();
 
    // 类模板的实参推导 from c++17
    std::cout << "类模板的实参推导" << std::endl;
    //  - 基于构造函数的实参推导
    B2(3);
    std::pair h{3, 3.14}; // 会转化为std::pair<int, double> ....

    //  - 用户自定义的推导指引

    // c++17 之前的解决方案： 引入辅助模板函数   

}