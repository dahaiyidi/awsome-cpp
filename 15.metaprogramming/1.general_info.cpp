#include <iostream>
#include <type_traits>

template <int x>
struct M
{
    constexpr static int val = x + 1;
    using type = int[x];
};

constexpr int fun(int x)
// consteval int fun(int x)
{
    return x + 1;
}

constexpr int val = fun(3); // 在编译期完成

// 定义的数组???
// template <unsigned... T> struct Cont;  
// template <auto... T> struct Cont2;  
// template <typename... T> struct Cont3;  
// template <template <typename> class... T> struct Cont3;  

int fun2(int input)
{
    static int x = 0;
    return input + (x++);
}

int main()
{
    // 元程序的形式：
    // -模板，constexpr,其他编译期可使用的函数
    // -通常以函数为单位
    // 引入操纵程序的程序
    // 元编程，（在c++中）也就是，编译期计算
    M<3>::val;  // 计算是在编译期执行的
    std::cout << "..." << std::endl;
    sizeof(int); // 在编译期运算

    // 元数据
    // -基本元数据：数值，类型，模板
    M<3>::type a;
    std::cout << std::is_same_v<decltype(a), int[3]> << std::endl;
    // -数组

    // 元编程输入输出均为常量
    // 函数无副作用:对相同的输入，就产生相同的输出，fun2就有副作用

    // type_traits元编程库。std::is_same_v<>就是
    // https://en.cppreference.com/w/cpp/header/type_traits
    


}