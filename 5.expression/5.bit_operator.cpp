#include <iostream>

int main()
{
    
    signed char x = 3;
    signed char y = 5;
    auto z = x & y; // interal promotion 相当于int z = static_cast<int>(x) & static_cast<int>(y)

    // signed, 右移可以保证符号（对于负数，高位补1，对于正数，高位补0），但是左移不能保证
    // 但是unsigned 右移时，高位总是补零
    signed char x1 = -4;
    std::cout << (x1 >> 1) << std::endl; //-2  首位补1

    signed char x2 = 4;
    std::cout << (x2 >> 1) << std::endl; //2  首位补0

    //  
    char x = 0xff; // 在不同的编译环境中，char 有可能是signed 也有可能是unsigned
}