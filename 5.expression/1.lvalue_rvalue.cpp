#include <iostream>
#include <vector>
#include <utility>
#include <type_traits>

void func(int p1, int p2)
{
    std::cout << p1 << ' ' << p2 << '\n';
}

void fun(std::vector<int>&& par) // 右值引用
{

}

struct Str
{
    int x;
};

void fun2(const int& par)
{

}

int main()
{
    int x = 1;
    // 这是不安全的写法，对于不同的编译器有不同的结果，C++对于该求值顺序没有要求。
    func(x = x + 1, x = x + 1); 

    // 左值，右值
    // 在 C++ 中，左值也不一定能放在等号左边；右值也可能放在等号左边
    const int x2 = 3; // x2标志着一个独一无二的对象，是一个glvalue,不属于将亡值(xvalue),因此x2是lvalue
    // x2 = 4; 但是x2不能放置在=左边（被赋值）
    Str() = Str();  // Str()是一个rvalue,但不是xvalue,所以是一个prvalue，他也可以放置到=左边，此处是初始化

    std::vector<int> x1;
    fun(std::move(x1)); // 将x1转化为一个将亡值，代表在main后面的代码中，不会对x1包含的资源做任何处理。

    // 左值可以转化为右值
    int x3 = 3; // x3 是一个lvalue
    int x4 = x3; // x3 作为rvalue

    // Str().x  // Str()本是prvalue，但因为要取出对应Str()内存的x值, 所以此处Str()作为了一个glvalue,是一个xvalue将亡值。

    fun2(3); // 3是prvalue，在传给par时，通过temporary materialization 将3转换成xvalue将亡值，par就可以绑定。

    // decltype
    // 如果expression是xvalue, decltype 产生T&&
    // 如果expression是lvalue, 产生T&
    // 如果expression是prvlaue, 产生T
    // 如果decltype 遇到实体，则直接返回其类型
    std::cout << "decltype" << std::endl;
    // int x5;
    decltype((3)) x5; // int expression是prvlaue, 产生T
    std::cout << std::is_same_v<decltype(x5), int> << std::endl;
    int x6;
    decltype(x6) x7; // int, 实体
    decltype((x6)) x8 = x6; // int&  ， express 是lvalue
    decltype(std::move(x6)) y = std::move(x6); // int && ， y是右值引用,绑定到将亡值xvalue x6

}