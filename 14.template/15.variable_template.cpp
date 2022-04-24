#include <iostream>


struct Str
{
    using internal = int;
    template <typename T>
    static void internal2()
    {}
};

template <typename T>
void fun()
{
    // T::internal* p; // * 被视为乘法，与预期的定义指针行为不一致
    typename T::internal* p; // 可以使用typename消除歧义
    // T::internal2<int>(); // T::internal < int > ()  变成了小于号大于号，与与其行为不一致
    T::template internal2<int>();  // 使用template消除歧义

    // 或者
    Str obj;
    obj.template internal2<int>(); 
}

template <typename T>
T pi = (T) 3.1415926;

template <typename T, unsigned v>
unsigned MySize = (sizeof(T) == v);

int main()
{
    // 使用typename表示一个依赖名称是类型而非静态数据成员
    fun<Str>();

    // 使用template表示一个依赖名称是模板
    
    // 变量模板
    // std::is_same_v就是利用变量模板实现的。
    std::cout << pi<float> << std::endl;
    std::cout << pi<int> << std::endl;
    std::cout << MySize<int, 4> << std::endl;
}