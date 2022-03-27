#include <iostream>
#include <vector>
#include <string>

int main()
{
    // 比较时，两个vector的元素数量不要求相等。
    // 为了提高性能,若元素数量已知，则 reserve() 函数可用于消除重分配。 
    std::vector<int> a;
    a.reserve(1024);
    std::cout << a.capacity() << std::endl;  //1024
    for(int i = 0; i < 1024; ++i)
    {
        a.push_back(i);
    }

    // 通过释放未使用的内存减少内存的使用
    a.push_back(1);
    std::cout << a.capacity() << std::endl; //2048
    a.shrink_to_fit();    
    std::cout << a.capacity() << std::endl;  //1025
    a.push_back(2);
    std::cout << a.capacity() << std::endl;  //2050

    // emplace_back
    sts::vector<std::string> a1;
    a1.push_back("hello");  // 向C字符串先转化为std::string,然后调用push_back, 需要将构造的std::string copy到vector相应位置
    a1.emplace_back("hello");  // 在容器末尾就地构造元素 ：直接在vector内存中利用hello构造std::string.更加高效。在容器末尾就地构造元素 

    // 元素插入接口，性能差，需要进行元素的依次移动
    // insert, emplace

    // 元素删除
    // pop_back, erase, clear
    // swap 效率高
    // 写操作可能会导致迭代器失效，因为添加元素的过程中可能会开辟新的内存，地址已经发生改变。

}