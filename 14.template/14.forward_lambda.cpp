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
    g(x);
    g(3);

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
