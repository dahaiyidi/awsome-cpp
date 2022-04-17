#include <iostream> 
#include <algorithm>
#include <list>
#include <sstream>
#include <iterator>
#include <numeric>

int main()
{
    // 内建数据类型不支持方法，计算逻辑存在相似性，因此引入泛型算法。
    // 迭代器作为算法和数据的桥梁
    std::vector<int> x(100);
    std::sort(std::begin(x), std::end(x));
    int x1[100];
    std::sort(std::begin(x1), std::end(x1));

    // 如果有与反省算法同名的方法时，具有类型的功能，则建议调用方法
    // 如std::find 是顺序查找，而std::map::find 使用红黑树，速度更快

    // 插入迭代器
    std::vector<int> x2;
    // std::fill_n(std::begin(x2), 10, 3); 错误，因为x2的空间不足够，无法逐个fill
    // 通过std::back_insert_iterator,可以不停地在x2末尾添加元素
    // std::fill_n(std::back_insert_iterator<std::vector<int>>(x2), 10, 3);  // 后面会调用push_back
    // 可以简写为：
    std::fill_n(std::back_inserter(x2), 10, 3); 
    std::list<int> x3;
    std::fill_n(std::front_inserter(x3), 10, 3);// 后面会调用push_front

    // 流迭代器
    std::cout << "流迭代器" << std::endl;
    std::istringstream str("1 2 3 4 5");
    std::istream_iterator<int> x4(str);
    std::istream_iterator<int> x5{}; // 可以用来表示迭代器的结尾位置
    // int res = std::accumulate(x4, x5, 0); // 用输入流迭代器表示一个区间，进行accumulate
    // std::cout << res << std::endl;
    for(; x4 != x5; ++x4)
    {
        std::cout << *x4 << std::endl;
    }

    std::ostream_iterator<int> x6 {std::cout, ","};
    std::fill_n(x6, 3, -1);

    //反向迭代器
    std::cout << "反向迭代器" << std::endl;
    std::vector<int> y{1, 2, 3, 4, 5};
    std::copy(y.rbegin(), y.rend(), std::ostream_iterator<int>(std::cout , ";"));

    //移动迭代器
    std::cout << "move_iterator" << std::endl;

    // 迭代器与哨兵
}