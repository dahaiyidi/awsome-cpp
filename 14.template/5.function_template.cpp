#include <iostream>
#include <type_traits>

template <typename T>
void fun(T x)
{
    std::cout << '1' << std::endl;
}

template <typename T>
void fun(T* x)
{
    std::cout << '2' << std::endl;
}

template <>
void fun(int* x)
{
    std::cout << '3' << std::endl;
}

// 可以使用if constexpr, 实现特化效果
template <typename Res, typename T>
Res fun2(T x)
{
    if constexpr(std::is_same_v<Res, int>)
    {
        std::cout << "1\n";
    }
    else
    {
        std::cout << "2\n";
    }
    return Res{};
}


// 使用虚假形参，实现特化效果
template <typename Res, typename T>
Res fun3(T x, const Res&)
{
    std::cout << "2\n";
    return Res{};
}

template <typename T>
int fun3(T x, const int&)
{
    std::cout << "1\n";
    return int{};
}

void fun4(auto x)
{}

int main()
{
    // 应该避免使用特化，会导致稍微写错，就会使用到了错误的函数
    // 通常用重载代替
    int x;
    fun(&x);  //3

    // 不便于使用重载的情况（无法建立模板形参与函数形参的关联）
    //   - 可以使用if constexpr
    std::cout << "使用if constexpr\n";
    fun2<int>(5);  // 1
    fun2<float>(5);  // 2

    //   - 使用假函数形参
    std::cout << "使用假函数形参\n";
    fun3(5, int{});
    // fun3(5, )
    //   - 通过类模板特化解决

    // from c++20， 使用auto定义模板参数类型
    fun4(5);

}