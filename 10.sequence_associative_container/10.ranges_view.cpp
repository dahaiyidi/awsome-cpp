#include <iostream>
#include <vector>
#include <ranges>

bool isEven(int i)
{
    return i % 2 == 0;
}

int Square(int i)
{
    return i * i;
}

int main()
{
    // 数值适配器 from c++20
    std::cout << "数值适配器" << std::endl;

    std::vector<int> v{1, 2, 3, 4, 5};
    // 将v中的偶数filt出来
    for(auto p: std::ranges::filter_view(v, isEven))  // std::views::filter(v, isEven) 效果一致
    {
        std::cout << p << ' ';
    }
    std::cout << std::endl;

    // 对元素进行统一的操作
    for(auto p: std::ranges::transform_view(v, Square))  
    {
        std::cout << p << ' ';
    }
    std::cout << std::endl;

    // 与linux pipe类似的写法
    auto x = std::views::filter(isEven);
    auto y = std::views::transform(Square);
    // for (auto p : v | x) // 与x(v)的效果一致,   v | x 的写法与linux中的pipe类似
    for (auto p : v | x | y) // 也就是对v中所有的偶数进行square， 
    // 也相当于    auto z = std::views::filter(isEven) | std::views::transform(Square); 然后 v | z
    {
        std::cout << p << ' ';
    }
    std::cout << std::endl;

    // 生成器 c++20
    // std::ranges::itoa_view, std::ranges::views::itoa, std::views::itoa
    for(int i : std::ranges::iota_view{1, 10}) //生成1, 2...9
    {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    for(int i : std::views::iota(1) | std::views::take(9))  //生成无限长的序列，只取前9位
    {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

}