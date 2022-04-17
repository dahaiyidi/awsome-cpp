#include <iostream>

struct Str2
{
    Str2() = default;
    Str2(const Str2&)
    {
        std::cout << "Str2's copy constructor is called." << std::endl;
    }
    // 如果不屑Str2的移动构造函数，则在Str中移动构造函数会调用Str的拷贝构造函数
    // 移动构造函数通常声明为不可抛出异常的函数，只是偷内存，不会出错. 使用noexcept标识
    Str2(Str2&&) noexcept
    {
        std::cout << "Str2's move constructor is called." << std::endl;
    }
};

struct Str
{
    Str() = default;  // 每个成员进行缺省初始化

    explicit Str(int input)
        : val(input)
    {

    }

    // 拷贝构造函数
    // 如果未显式提供，那么编译器会自动合成一个，合成的版本会依次对每个数据成员调用拷贝构造
    // Str(const Str& x) = default;
    Str(const Str& x)
        : val(x.val)  // 形参不能是Str x，因为在调用时，需要小调用拷贝构造，得到x，因此陷入死循环，编译不会通过。
    {
        std::cout << "copy constructor is called" << std::endl;
    }

    // 移动构造函数
    // 当某些特殊成员函数（如拷贝构造）未定义时，编译器可以合成一个， Str(Str&& x)=default;。调用每个成员的移动构造函数，对于内建数据类型就会直接copy
    // 对于内建数据类型就是copy
    // Str(Str&& x) //右值引用,表示，我们可以偷x里面的资源
    //     : val(x.val)
    //     , a(std::move(x.a)) // 偷了x的a
    //     {

    //     }
    // Str(Str&& x) noexcept = default;

    Str(Str&& x) noexcept
    {
        std::string tmp = x.a;  // 注意右值引用对象用做表达式时是左值！ 此时x是左值, x不会被偷
        // std::string tmp = std::move(x.a);  // 此时明确x会被偷

        std::cout << "注意右值引用对象用做表达式时是左值" << x.a << std::endl;
    }
    
    void fun()
    {
        std::cout << val << ' ' << a << std::endl;
    }

private:
    int val = 3;
    std::string a = "abc";
    Str2 m_str2;
};

void foo(int x)
{

}
void fun(Str m)
{

}

int main()
{
    // Str m = 3; // 隐式类型转换，将3转化为Str。但是如果加上explicit就不能隐式的进行类型转换了
    Str m = Str(3);// 显式类型转换
    Str m2 = static_cast<Str>(2);
    fun(Str(3)); // 显式类型转换

    // 拷贝构造函数
    Str m3(m);
    Str m4 = m;
    
    // 移动构造函数 c++11
    // 偷窃资源
    std::cout << "移动构造函数" << std::endl;
    Str m5;
    m5.fun(); // 3 abc
    Str m6 = std::move(m5); // 移动构造函数， 此时如果Str2中，有移动掉移动，没有移动构造函数则调用Str2的拷贝构造函数
    m5.fun();  // 3
    m6.fun();  // 3 abc    

}