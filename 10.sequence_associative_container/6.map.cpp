#include <iostream>
#include <map>

void fun(const std::map<int, bool>& m)
{
    // m[3]; // 此处会报错，const map对象不能使用[]
}

int main()
{
    // map
    // 每个节点是std::pair
    std::map<int, bool> m{{3, true}, {4, false}, {1, true}};

    for(auto& [k, v]: m)
    {
        // p:  std::pair<const int, bool>
        std::cout << k << ' ' << v << std::endl;
    }

    // 可以采用自定义的比较函数引入大小关系
    m.insert(std::pair<int, bool>(5, false));
    m.erase(5);
    // 其他一些用法与set 类似find, contains
    
    // 访问元素
    std::cout << "访问元素" << std::endl;
    // at 当key不在map中，会抛出异常
    // [] 由于背后是红黑树实现，则如果key不在当前map中，则会添加一个新的节点。 []不能用于常量对象。
    m[6]; // 添加节点，值为缺省初始化，也就是添加了{6, false}

    for(auto& [k, v]: m)
    {
        // p:  std::pair<const int, bool>
        std::cout << k << ' ' << v << std::endl;
    }
    
    fun(m);


}