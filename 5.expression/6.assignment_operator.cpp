#include <iostream>

int main()
{
    int x;
    int y;

    (x = 4) = 2; // 最终x=2, 因为x=4返回左操作数x
    ((x = 4) = 2) = 1; // x = 1
    // (x = 4) = 2 = 1; // 报错

    short x1;
    x1 = 0x80000001; // 发生收缩转换，此时x=1,因为（本机器中）int为4字节，x只需要2字节
    std::cout << x1 << std::endl;

    // x = {0x80000001}; // 可以在编译时、报错，放置收缩转换

    short x0;
    constexpr int x2 = 3;
    x0 = {x2};
    std::cout << x0 << std::endl;


    // int x3 = 3;
    // x0 = {x3};

    int a = 2;
    int b = 3;
    a ^= b ^= a ^= b; // 右结合
    std::cout << a << std::endl; // 3
    std::cout << b << std::endl; // 2
    
}