#include <iostream> 

// c++11 返回类型放置到函数头的后部
// [[nodiscard]] 表示返回值很重要，必须要保留下来
[[nodiscard]]  auto fun(int a, int b) -> int
{
    return a + b;
}

// 以下两句等价
// S::MyInt S::fun2(int a, int b){}
// auto S::fun2(int a, int b){} -> MyInt {}

// from c++ 14 返回类型的自动推导 
auto fun3(int a, int b)
{
    return a + b;
}

// 使用 constexpr if 构造"具有不同返回类型"的函数, 其实在编译期就已经确定返回值类型。 
constexpr bool value = true;
auto fun4()
{
    if constexpr (value)
    {
        return 1;
    }
    else
    {
        return 3.1;
    }
}

struct Str
{
    int x;
    std::string y;
};

Str fun5()
{
    return Str{};
}

Str& fun6()
{
    static Str inst; 
    return inst;
}


int main()
{
    // 白白耗费资源却没有对系统产生任何影响，是无效调用， 需要在函数前加上[[nodiscard]]  , from c++17
    fun(1, 2); // 当写成int a = fun(1, 2); 就不会有[[nodiscard]] warning了


    // 返回类型与结构化绑定（ C++ 17 ）
    auto [v1, v2] = fun5();
    auto& [v3, v4] = fun6();
}