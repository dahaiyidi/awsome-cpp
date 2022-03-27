#include <iostream>
#include <vector>

void fun()
{
    int* ptr = new int(3);
    // 若这里出现异常，则内存不会被释放掉，不是异常安全的代码
    delete ptr;

    // 异常安全的代码，可以这样写：
    // std::shared_ptr<int> ptr(new int(3));
}

int main()
{
    int* ptr = new int[3]; // ptr 是地址，用sizeof(ptr)返回int* 指针的大小。
    // sizeof 在编译期确定，而动态分配内存是在运行期完成了，当然也不会
    // std::vector<int> tmp(100);
    // std::cout << sizeof(tmp) << std::endl; // 24

    // allocator  c++的， 建议使用allocator
    std::cout << "allocator" << std::endl;
    std::allocator<int> al;
    int* ptr2 = al.allocate(3); // 分配了一块内存，内存可以包含3个int，不包括int的初始化
    // [[nodiscard]]
    al.deallocate(ptr2, 3);

    // malloc 是要分配多少字节

    // aligned_alloc 分配对齐内存

    // 动态内存与异常安全

    // 垃圾回收， 支持极其有限。与c++高性能、对对象的精确控制的初衷相违背。

}