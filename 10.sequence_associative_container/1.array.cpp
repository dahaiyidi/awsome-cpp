#include <iostream>
#include <array>
#include <type_traits>

int main()
{
    // array 容器模板：具有固定长度的容器，其内部维护了一个内建数组，与内建数组相比提供了复制操作
    std::array<int, 3> a = {1}; // 如果不写{}， 则内部的元素是乱的。
    
    std::array<int, 3> b = a;  // copy

    std::cout << std::is_same_v<std::array<int, 3>::value_type, int> << std::endl;

    // 访问
    // std::cout << a.at(100) << std::endl; // at相比[]的特点是，它可以判断是否超出range，std::out_of_range
    // a.front, a.back
    a.data();  // 返回指向array第一个元素的指针

    // 容量相关，平凡实现
    // a.empty(), a.size(), a.max_size

    // a.swap(b);
    // a.fill(6);

    // 比较操作,需要类型相同。std::array<int, 3> 与std::array<int, 4>是不同的类型
    
}