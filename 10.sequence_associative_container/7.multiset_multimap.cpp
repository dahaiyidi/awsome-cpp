#include <iostream>
#include <set>

int main()
{
    // multiset / multimap 但允许重复键,也是使用红黑树实现
    // 元素访问
    std::multiset<int> s{1, 3, 1};
    std::set<int> s2{1, 3, 1};
    auto ptr = s.find(1); // find 返回首个查找到的元素
    std::cout << *ptr << std::endl;
    std::cout << *(++ptr) << std::endl;    // ++ptr; // 找到下一个1

    // 返回元素个数
    std::cout << s.count(1) << s2.count(1) << std::endl; 

    auto b = s.lower_bound(1);
    auto e = s.upper_bound(1);
    // 等同于 auto [b, e] = s.equal_range(1);
    for(auto ptr = b; ptr != e; ++ptr)
    {
        std::cout << *ptr << std::endl;
    }

}