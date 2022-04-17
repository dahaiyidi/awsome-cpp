#include <iostream>
#include "header.h"  // 在类的内部声明相同类型的静态数据成员

// 结构体（以及类）的一处定义原则：翻译单元级别.在不同的cpp中可以有相同名字的结构体
// 结构体内不能使用auto
struct Str
{
    mutable int x = 3; // 声明
    int z = 33;
    int y = 333;
};

// 静态数据成员 多个对象之间共享的数据成员
struct Str2
{
    inline static int x = 3; // 声明
};

int main()
{
    Str m_str{.x=4, .y=6};  // 聚合初始化：从初始化列表到指派初始化器
    std::cout << m_str.x << m_str.y << std::endl;
    
    // mutable
    const Str m_str2;
    m_str2.x = 9; //虽然时const的结构体，但是还可以修改成员x
    std::cout << m_str2.x << std::endl;

// 静态数据成员 多个对象之间共享的数据成员
    Str2 m_str3;
    Str2 m_str4;
    m_str3.x = 8;
    std::cout << m_str4.x << ' ' << Str2::x << std::endl;
}