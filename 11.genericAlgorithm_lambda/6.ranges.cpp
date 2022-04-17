#include <iostream>
#include <algorithm>
#include <map>

auto fun()
{
    return std::vector<int> {1, 2, 3};
}
int main()
{
    // ranges
    std::vector<int> x{1, 2, 3, 4, 5};
    // 可以直接使用容器
    auto it = std::ranges::find(x, 3);
    // auto it = std::ranges::find(fun(), 3); // fun()内部使用了返回了局部变量，此时it的类型为std::ranges::dangling,报错
    std::cout << *it << std::endl;

    // 引入映射的概念
    std::map<int, int> m{{2, 3}};
    auto it2 = std::ranges::find(m, 3, &std::pair<const int, int>::second); // 寻找value为3的元素
    std::cout << it2->first << ' ' << it2->second << std::endl; 

    // view,灵活组织程序逻辑
    
}