#include <iostream>

template <int x> struct Imp;

// 基于（偏）特化引入分支，常见分支引入方式但书写麻烦
template <int x>
    requires (x < 100)
struct Imp<x>
{
    constexpr static int value = x * 2;
    using type = int;
};

template<int x>
    requires (x >= 100)
struct Imp<x>
{
    constexpr static int value = x -3;
    using type = double;
};

constexpr int x = Imp<97>::value;  //97*2
constexpr int x2 = Imp<100>::value;  //100-3
using x4 = Imp<100>::type;


constexpr int fun(int x)
{
    if(x > 3)
    {
        return x * 2;
    }
    else
    {
        return x - 100;
    }
}
// 在编译期就会直接将200给x
constexpr int x3 = fun(100);

template <int x>
int fun()
{
    if constexpr (x > 3)
    {
        return x * 2;
    }
    else
    {
        return x - 100;
    }
}

// 对于fun<100>();会在编译期生成如下:
// template <>
// int fun<100>()
// {
//     return 200;
// }

// 基于 std::enable_if 引入分支
// 基于函数的
// 当x=99时，(x < 100)为false, std::enable_if_t<(x < 100)>*对应void*
// 
template <int x, std::enable_if_t<(x < 100)>* = nullptr>
constexpr auto fun2()
{
    return x * 2;
}

// 当x=99时，(x >= 100)为false, 此时enable_if<B,T>里面不存在type成员，无法匹配上。
// 匹配失败并非错误
template <int x, std::enable_if_t<(x >= 100)>* = nullptr>
constexpr auto fun2()
{
    return x - 3;
}

constexpr auto x5 = fun2<99>();

// 在类中使用也可以std::enable_if
// 函数模板支持重载，但是类模板不支持重载
template <int x, typename = void> struct Imp2;
// 基于特化
template <int x>
struct Imp2<x, std::enable_if_t<(x < 100)>>
// 不可以这样写 struct Imp2<x, typename = std::enable_if_t<(x < 100)>>, 而且，当x=1111时， std::enable_if_t<(x < 100)>这个缺省值是无意义的，会报错。
{
    constexpr static int value = x * 2;
    using type = int;
};

template<int x>
struct Imp2<x, std::enable_if_t<(x >= 100)>>
// 不可以这样写struct Imp2<x, typename = std::enable_if_t<(x >= 100)>>， 这样就会导致Imp2的重定义
{
    constexpr static int value = x -3;
    using type = double;
};

constexpr auto x6 = Imp2<101>::value;

template <int x>
constexpr auto fun3 = (x < 100) ? x * 2 : x - 3;

int main()
{
    // if constexpr 便于理解只能处理数值
    std::cout << fun<100>() << std::endl;

    // 基于（偏）特化引入分支，常见分支引入方式但书写麻烦
    std::cout << Imp<100>::value << std::endl;

    // 基于 std::conditional 引入分支：语法简单但应用场景受限
    typedef std::conditional<sizeof(int) >= sizeof(double), int, double>::type Type;
    std::cout << typeid(Type).name() << std::endl;

    // 基于 SFINAE(匹配失败并非错误) 引入分支
    // 基于 std::enable_if 引入分支：语法不易懂但功能强大
    // – 注意用做缺省模板实参不能引入分支！
    std::cout << "SFINAE..." << std::endl;
    std::cout << x5 << std::endl;
    std::cout << x6 << std::endl;

    // 基于 std::void_t 引入分支： C++17 中的新方法，通过 无效语句 触发分支

    // 基于 concept 引入分支： C++20 中的方法
    // ● 可用于替换 enable_if

    // 基于三元运算符引入分支： std::conditional 的数值版本
    std::cout << fun3<2> << std::endl;

}