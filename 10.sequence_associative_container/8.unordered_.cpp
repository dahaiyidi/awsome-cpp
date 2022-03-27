#include <iostream>
#include <unordered_set>
#include <set>


struct Str
{
    int x;
};

size_t MyHash(const Str& val)
{
    return val.x;
}

bool MyEqual(const Str& val1, const Str& val2)
{
    return val1.x == val2.x;
}

struct Str2
{
    int x;
    bool operator==(const Str2& t) const
    {
        return (this->x == t.x);
    }
};

class MyHashFunciton
{
public:
    size_t operator()(const Str2& t) const
    {
        return t.x;
    }
};
    
int main()
{
    std::unordered_set<int> s{3, 1, 5, 4, 1};
    for (auto p : s)
    {
        std::cout << p << std::endl;
    }

    // 适用的场景： 不进行插入，需要快速查找。

    // 由于unordered 的key只需要满足：可以转化为hash， 判等。
    // 除 == ， != 外，不支持容器级的关系运算。但是对于set，map，是支持各种容器级别的关系运算的。
    // (但 ==, != 速度较慢,这是因为bucket list中需要重新排列（使用了std::is_permutation），才能判断两个set是否相等
    // 如 std::set<int> s{3, 1, 5, 4} > std::set<int> s{3, 1, 5, 4, 0}; ,它是用过用中序遍历的结果进行比较的
    std::set<int> s2{3, 1, 5, 4};
    std::set<int> s3{3, 1, 5, 4, 0}; 
    std::cout << (s2 > s3) << std::endl;

    // 自定义hash,判等函数
    std::unordered_set<Str, decltype(&MyHash), decltype(&MyEqual)> s4(1, MyHash, MyEqual); // decltype(&MyHash)就是函数指针size_t (*)(const Str& val)
    s4.insert(Str{1});

    // 方法2，使用class
    std::unordered_set<Str2, MyHashFunciton> s5; // 里面的hash则使用了MyHashFunciton的(), 判等则使用了Str2的==
    s5.insert(Str2{1});

}