#include <iostream>

template <typename T>
void fun(T x)
{
    std::cout << x << std::endl;
}

// 对于T为int时，程序员要求有特殊的实现，则可以选择特化
// 注意与函数模板重载的差别
template <>
void fun(int x)
{
    std::cout << x << std::endl;
}


// 放在此处则特化template <typename T>  void fun(T x)
// template <>
// void fun(int* x)
// {
//     std::cout << x << std::endl;
// }


template <typename T>
void fun(T* x)
{
}


// 放在此处则特化template <typename T>  void fun(T* x)
template <>
void fun(int* x)
{
    std::cout << x << std::endl;
}


int main()
{
    // 函数模板的（完全）特化， 完全代表函数模板形参都需要被指定，不可以指定部分。
    // 如果需要实现部分特化的效果，可以借助于type_traits模块的std::is_same_v<,> 判断函数形参的类型，以实现针对不同的（部分）函数形参类型，有不同的实现逻辑。 
}