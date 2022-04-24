#include <iostream>

// 为类模板的成员引入别名
template <typename T>
struct B
{
    using TP = T*;
};

// 别名模板
template <typename T>
using AddPointer = typename B<T>::TP;

template <typename T>
struct B2
{
    using type = T*;
};

// 特化
template <>
struct B2<int>
{
    using type = int&;
};

template <typename T>
using MyPointer = typename B2<T>::type;

template <typename T>
struct B3
{
    using type = T*;
};
template <typename T>
using M = T*;
// using M = typename B3<T>::type; // 此时无法进行实参推导, fun(typename B3<T>::type input), 无法实现类型推导

template<typename T>
void fun(M<T> input)  // 等价于fun(T* input)
{}

int main()
{
    // 别名模板
    // AddPointer<int> x;
    MyPointer<float> x2;

    int x;
    fun(&x);

}