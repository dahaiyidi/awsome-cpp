#include <iostream>
#include "header.h"
// template <typename T>
// void fun(T x)
// {
//     std::cout << x << std::endl;
// }

// // 显式实例化的定义
// template
// void fun<int>(int x);
// // 也可以这样写:
// // template
// // void fun(int x);

// 显式实例化的声明
// 在main.cpp 里面就不会有fun<double>(double x)函数了。

extern template
void fun(double x);

template <typename T>
void fun2(T x)
{
    std::cout << x << std::endl;
}

// 显式实例化放置在这里则会实例化template <typename T>  void fun2(T x)
// template
// void fun2(int* x);
// 因为到这里只看到了这个符合的函数模板

template <typename T>
void fun2(T* x)
{
    std::cout << x << std::endl;
}

// 显式实例化放置在这里则会实例化template <typename T>  void fun2(T* x)
// 选择实例化比较特殊的函数模板
template
void fun2(int* x);

int main()
{
    fun(3.1);
}