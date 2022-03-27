#include <iostream>
#include <vector>

int main()
{
    constexpr int grade = 20;
    if constexpr (grade < 60) // 在编译时优化选择的分支, else肯定不会执行
    {

    }
    else
    {

    }

    // switch 
    int x;
    // switch (std::cin >> x; x)
    // {
    //     case 1:
    //     {
    //         int y = 0; // 不加{}会报错
    //         break;

    //     }
    //     case 2:
    //     case 3:  // 2 与 3 共用。
    //         [[fallthrough]] // c++17

    //     case 4:
    //         break; 
    //     default:
    //         break;
    // }

    // for 
    // for(int i = 0, double y = 0.0; i < 3; i++) // 报错，不可以同时声明不同的类型
    // for(int i = 0, *ptr = &i; i < 3; ++i) // 合法 ，ptr 为int*
    for(int i = 0, y = 0; i < 3; ++i) 

    {

    }
    int* p, q; // p 为int* , q为int。应该这样写 int* p, *q;  不建议在一行声明多个变量，避免产生歧义。

    std::vector<std::string> arr{"h", "k"};
    // 使用常量左值引用读元素
    for (const auto& v : arr)
    {
        std::cout << v << '\n';
    }
    // 使用万能引用（universal reference）修改元素,确保std::vector<bool> 也可以被修改，如果采用 auto& v 则会报错。
    for(auto&& v: arr)
    {
        v = "o";
    }

    for (const auto& v : arr)
    {
        std::cout << v << '\n';
    }
}