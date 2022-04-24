#include <iostream>


template <typename... T>
void fun(T... )  // 包展开，fun(int, double)
{

}

template <typename... >
struct Tuple {};

template<class... Args1> struct zip{
    template<class... Args2> struct with{
        typedef Tuple<Tuple<Args1..., Args2>...> type;
    }; 
};

typedef zip<short, int>::with<unsigned short, unsigned>::type T1;

// T1 类型是Tuple<Tuple<shor, int, unsigned short>, Tuple<short, int, unsigned>>

void fun2(){}

// template<typename U, typename... T>
// void fun2(U u, T... args)
// {
//     std::cout << u << std::endl;
//     fun2(args...);
// }
// 更加简洁的形式
template <typename... T>
void fun2(T... args)
{
    // 基于,的折叠表达式
    ((std::cout << args << std::endl), ...);
}

template<typename ... Args>
int sum(Args&&... args)
{
    return (... + args);
}

int main()
{
    // 包展开
    fun<int, double>(2, 2.1);

    // 折叠表达式 fromc++17
    // 包展开应用
    fun2(1, 2, "hello", 'c'); // 依次打印出各元素

    // 折叠表达式用于表达式求值，无法畜栏里输入（输出）是类型和模板的情况
    std::cout << sum(1, 2, 3, 4) << std::endl;


}