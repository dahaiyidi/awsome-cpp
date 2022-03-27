#include <iostream>
#include <type_traits>

int main()
{
    // 多维数组
    int x1[3];

    int x2[3][4] = {1, 2, 3, 4, 5};
    int x3[3][4] = {{1, 2, 3}, {5, 6, 7, 8}}; // 其余元素填充为0
    int x[][3] = {1, 2, 3,4}; //
    std::cout << std::size(x2) << std::endl; // 3
    std::cout << std::size(x2[0]) << std::endl; //4
    std::cout << std::is_same_v<decltype(x2[0]), int(&)[4]> << std::endl;
    std::cout << std::is_same_v<decltype(x), int[2][3]> << std::endl;

    // 多维数组遍历 
    for (auto& p: x2)
    {
        for(auto q: p)
        {
            // std::cout << q << std::endl;
        }
    }

    // 指针与多维数组
    int x4[3][4][5];
    auto ptr = x4; // int(*)[4][5]  隐式转换为指针，当前最高维度信息失去，其他维度信息被保留
    auto ptr2 = x4[0];  // int(*)[5]
    std::cout << std::is_same_v<decltype(ptr), int(*)[4][5]> << std::endl;
    std::cout << std::is_same_v<decltype(ptr2), int(*)[5]> << std::endl;

    using A = int[4][5];
    A* ptr3 = x4;

    // 另一种定义多维数组的方式
    std::cout << "另一种定义多维数组的方式" << std::endl;
    using B = int[4];
    B x5[3]; // 相当于int x5[3][4]
    std::cout << std::size(x5) << std::endl;
    std::cout << std::size(x5[0]) << std::endl;

    // 用指针遍历
    std::cout << "遍历" << std::endl;

    auto ptr5 = std::cbegin(x2);
    while(ptr5 != std::cend(x2))
    {
        auto ptr4 = std::cbegin(*ptr5);
        while(ptr4 != std::cend(*ptr5))
        {
            std::cout << *ptr4 << std::endl;   
            ptr4 += 1;
        }
        ptr5 += 1;
    }
}