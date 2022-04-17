#include <iostream>
#include <map>
#include <functional> 

auto fun(int x)
{
    return x + 1;
}

auto fun(double x)
{
    return x + 1;
}
int main()
{
    int y = 3;
    // constexpr 表示可以在编译期进行调用， 也可以在运行期调用
    // consteval 表示只能在编译期调用
    // 可以在https://godbolt.org/ 中查看对应的汇编
    auto lam = [] (int val) constexpr
    {
        return val + 1;
    };

    constexpr int val = lam(100);

    auto lam2 = []<typename T> (T val) 
    {
        return val + 1;
    };


    // 即调用函数表达式（ Immediately-Invoked Function Expression, IIFE ）
    int x1 = 1;
    int x2 = 2;
    const auto val2 = [z = x1 + x2] ()
    {
        return z;
    }(); // 此处立即调用
    std::cout << val2 << std::endl;

    // 使用 auto 避免复制（ C++14 ）
    std::map<int, int> m{{2, 3}};
    // auto lam3 = [] (const std::pair<int, int>& p) 此时会引起复制，因为*m.begin()的类型为std::pair<const int, int>
    // auto lam3 = [] (const std::pair<const int, int>& p)  此时不会引起复制，但是不如直接使用auto
    auto lam3 = [] (const auto& p) 
    {
        return p.first + p.second;
    };
    std::cout << lam3(*m.begin()) << std::endl;

    // Lifting （ C++14 ）
    // auto b = std::bind(fun, 3);  // #include <functional>  报错。
    auto lam4 = [] (auto x)
    {
        return fun(x);
    };
    std::cout << lam4(3) << std::endl;
    std::cout << lam4(3.5) << std::endl;
    
    // 递归调用（ C++14 ）
    auto factorial = [] (int n)
    {
        // 递归时，要显式的写明返回类型
        auto f_impl = [] (int n, const auto& impl) -> int
        {
            return n > 1 ? n * impl(n - 1, impl) : 1;
        };

        return f_impl(n, f_impl); // 此处是递归的开始
    };

    std::cout << factorial(5) << std::endl;
}