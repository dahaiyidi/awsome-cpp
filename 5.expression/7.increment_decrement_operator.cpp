#include <iostream>

int main()
{
    int x = 3;
    ++(++x); // 值为5，++前缀返回左值，
    // (x++)++; //报错，++后缀返回右值

    // 建议使用前缀形式
    ++x;  // 实现更高效
}