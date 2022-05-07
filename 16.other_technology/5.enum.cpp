#include <iostream>

enum Color2 : int;  // 必须指定底层类型

enum class Color3; // 对于有作用域的枚举，此时有缺省的底层类型：int

// enum Color : char //可以为枚举指定底层类型
enum Color  // : char   // 无作用域枚举
// enum class Color    // 有作用域枚举,避免名称污染 from c++11
// – 枚举项缺省使用 0 初始化，依次递增，可以使用常量表达式来修改缺省值
// 可以为枚举指定底层类型，表明了枚举项的尺寸
{
    Red,
    Green = 100,
    Yellow  // 101
};

class A
{
public:
    // 可以借用枚举，生命编译期的常量(在constexpr出现之前)
    enum{x = 3};
};

int main()
{
    Color x = Red;

    //无作用域枚举项可隐式转换为整数值；也可用 static_cast 在枚举项与整数值间转换
    Color x1 = static_cast<Color>(100);
    // Color x2 = 100;   报错
    std::cout << Red << std::endl;
    std::cout << x1 << std::endl;

    // 枚举是翻译单元的一处定义原则，但是在非常特殊的情况下，需要在本文件中声明枚举，而在其他的文件中定义
    // 注意区分枚举的定义与声明
    Color2 x2;
    Color3 x3;
}