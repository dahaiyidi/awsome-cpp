#include <iostream>

// 接受数值, 0个或多个
template <int... a>
void fun()
{
}

// 接收类型
template <typename... T>
void fun2(T... args) // 带可选名字的函数形参包
{
    std::cout << sizeof...(T) << ' ' << sizeof...(args) << std::endl;  // sizeof... 获取args, T的个数
}

// 接收模板
template <template<typename> class... a>
void fun3()
{
}

template <typename... T> class C;

template <typename T1, typename T2>
class B;

// 特化
template <typename... T, typename T2>
class B<C<T...>, T2>
{};


int main()
{
    fun<1, 2, 2>();
    fun2<int, double>(1, 1,2);
    fun2<>(1, 1,2);  // 模板实参推导

    // sizeof...
}