#include <iostream>

// 可以在编译期执行，也可以在运行期执行
constexpr int fun(int x)
{
    return x + 1;
}

// 只能在编译期执行，提高运行时的效率。
consteval int fun2(int x)
{
    return x + 1;
}

// constexpr consteval 由于需要在编译期可以计算，所以是翻译单元的一处定义原则
// inline也是翻译单元的一处定义原则，是因为可能需要在编译期进行展开。

int main()
{
    constexpr int x = fun(3); // x的值在编译期就确定, fun函数必须包含constexpr

    int y;
    // std::cin >> y;
    // fun2(y); // 报错

    constexpr int x1 = 3;
    int y1 = fun2(x1);
        
}