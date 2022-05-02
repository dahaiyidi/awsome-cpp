#include <iostream>
#include <utility>

void g(int&)
{
    std::cout << "l-reference.\n";
}
void g(int&&)
{
    std::cout << "r-reference.\n";
}

template <typename... T>
void fun(T&&... args)  // T&& 是万能引用，而不是右值引用
// 当传入3时， 会翻译为void fun<int> (int && input), 但是右值的引用是左值，因此此时在调用g(input)时，会调用void g(int&)
// std::forward 可以解决该问题
// 我们希望在传递参数的时候，可以保存参数原来的lvalueness 或 rvalueness，即是说把参数转发给另一个函数。
// 当传入x,一个左值，T类型推断为int&， 形参类型为int& && ，触发引用折叠，变为int&
{
    std::cout << "hello\n";
    // g(input);
    // 完美转发
    g(std::forward<T>(args)...); // 
}
int main()
{
    // 完美转发 std::forward
    int x = 3;
    g(x); // l-reference.
    g(3);  // r-reference.

    // 完美转发
    // std::forward通常与万能引用结合使用
    // 同时处理传入参数是左值或右值的情况
    fun(x);
    fun(3);

    // lambda
    std::cout << "---------lambda" << std::endl;
    auto glambda = [] <class T>(T a, auto&& b) {return a < b;};

    auto f = []<typename...T> (T&&... args)
    {
        return g(std::forward<T>(args)...);
    };
    f(x);

}
