#include <iostream>

template<typename T, T a>
int fun(int x)
{
    return x + a;
}

// from c++17  可以使用auto
template <auto a>
void fun2()
{}

// from c++20,可以接受浮点数作为模板参数，但是有时还是不能编译通过
// template <float x>
// void fun3()
// {}

template <typename T>
class C{};

template <typename T, typename T2 = int>  // 缺省模板实参
class C2{};

// 模板作为模板参数
// template < template<typename T> class T2>
// T在这里是没有用的，则可以直接删除
// template < template<typename> class T2>
// from c++17, class 换为typename
template < template<typename> typename T2>
void fun()
{
    std::cout << "000" << std::endl;
}

int main()
{
    // 模板可以接收（编译期常量）数值作为模板参数
    //使用数值作为模板参数
    fun<int, 3>(5);
    fun2<3>();
    fun2<true>();

    // fun3<3.14f>();
    // 模板作为模板参数
    fun<C>();

    // 缺省模板实参
    // 即便C2有两个模板实参，但是第二个有缺省的模板实参，则可以这样写
    fun<C2>();
}