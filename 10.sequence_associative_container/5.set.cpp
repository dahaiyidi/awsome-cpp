#include <iostream>
#include <set>

struct Str
{
    int x;
};

bool MyComp(const Str& val1, const Str& val2)
{
    return val1.x < val2.x;
}

int main()
{
    // set 用红黑树实现
    // 元素需要支持< 比较大小
    std::set<int> s{100, 3, 56, 7}; // 默认是使用std::less()进行比较
    // 遍历是中序遍历
    for (auto ptr = s.begin(); ptr != s.end(); ++ptr)
    {
        std::cout << *ptr << std::endl;
    }

    std::set<int, std::greater<int>> s2{100, 3, 56, 7}; // 此时遍历就会从大到小输出

    //自定义比较函数
    std::set<Str, decltype(&MyComp)> s3({Str{3}, Str{5}, Str{6}}, MyComp);  
    s3.insert(Str{100});
    s3.emplace(100); //效果和上一句一样

    // emplace_hint 结合hint,可以提高性能。如果提供错误的，则会降低性能
    s3.erase(s3.begin());

    // find
    auto ptr = s.find(3);
    if(ptr != s.end())
    {
        std::cout << *ptr << std::endl;
    }

    // contains
    std::cout << s.contains(3) << std::endl;

    // extract 修改元素
    // 注意： set 迭代器所指向的对象是 const 的，不能通过其修改元素。这是因为是用红黑树实现的，则破坏了它的结构
    // 要修改元素，使用erase的性能要逊于extract。

}