#include <iostream>

// 字面值类：可以构造编译期常量的类型
class Str
{
public:
    // constexpr: 可以在编译期和运行期使用
    // consteval: 可在编译期使用
    // consteval Str(int val)  // 函数返回一个编译期的常量
    constexpr Str(int val)
        : x(val)
    {}

    Str(double f)
        : x(f)
    {}

    constexpr void inc()
    {
        x = x + 1;
    }

    constexpr int read() const // 在c++11, 函数类型位int fun() const, 但在之后的版本中,则默认无const,需要手动加上.
    {
        return x;
    }

    // ~Str() {}
private:
    int x = 3;
    // std::string a;
};

// 编译期常量
// 要求Str数据成员是字面值类型. 在类中无法含有数据成员std::string a;
// 需要使用一个平凡的析构函数, 也不能 ~Str() {}.因为析构函数会在运行期调用,编译器无法知晓运行期的事情.
constexpr Str a(4); 

constexpr int MyFun()
{
    Str y(10);
    y.inc();    
    return y.read();
}


int main()
{

    // 字面值类,使用的较少.
    
    int x =5;
    // Str b(x); // 出错 the value of ‘x’ is not usable in a constant expression

    Str a2(3.0);
    a.read();
    std::cout << MyFun() << std::endl;
}