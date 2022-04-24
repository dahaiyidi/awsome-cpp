#include <iostream>
#include <vector>
#include <type_traits>

//   - 简单表达式：表明可以接收的操作
template <typename T>
concept Addable =
requires (T a, T b) 
{
    a + b;
};  // requires 表达式

template <Addable T>
auto fun(T x, T y)
{
    return x + y;
}

template <typename T>
concept Avail =
requires{
    typename T::inter;  //T 内部要有inner类型的定义
};  // requires 表达式

template < Avail T>
auto fun2(T x)
{
}

struct Str
{
    using inter = int;
};

template <typename T>
concept Avail2 =
requires (T x) {
    {x + 1} -> std::same_as<int>;// 要求x+1必须合法，并且std::Same<decltype((x + 1)), int>必须被满足 
}; 


template <Avail2 T>
auto fun3(T x){}

// 相当于
// template <typename T>
//     requires Avail2<T>
// auto fun3(T x){}

// 相当于
// template <typename T>
//     // 第1个requires是requires从句，第2个requires是表达式
//     requires requires (T x) {
//     {x + 1} -> std::same_as<int>;// 要求x+1必须合法，并且std::Same<decltype((x + 1)), int>必须被满足 
// }
// auto fun3(T x){}

template <typename T>
    requires std::is_same_v<T, double>
void fun4(T){std::cout << "1\n";}

template <typename T>
    requires std::is_same_v<T, int>
void fun4(T){std::cout << "2\n";}


template <typename T>
concept C1 = std::is_same_v<T, int>;

template <typename T>
concept C2 = std::is_same_v<T, int> || std::is_same_v<T, double>;

template <C1 T>
void fun5(T){std::cout << "3\n";}

template <C2 T>
void fun5(T){std::cout << "4\n";}

template <typename T>
    requires std::is_same_v<T, int> || std::is_same_v<T, float>
class B;

// 特化
template <>
class B<int> {};
// 特化
template <>
class B<float> {};

int main()
{
    // requires 表达式
    //   - 简单表达式：表明可以接收的操作
    fun(2, 3);
    //   - 类型表达式： 表明是一个有效的类型
    fun2(Str{});
    //   - 复合表达式： 表明操作的有效性，以及操作返回类型的特性
    fun3(2);
    //   - 嵌套表达式： 包含其他的限定表达式

    // 只有requires从句有效且返回为true时，相应的模板才会被考虑
    fun4(1);
    fun4(1.2);

    // requires 从句所引入的限定具有偏序特性，系统会选择限制最严格的版本
    // 也就是应该选择template <C1 T> void fun5(T){std::cout << "3\n";}
    // 但是实践表明，报错：call of overloaded 'fun5(int)' is ambiguous
    // fun5(1);

    // 特化技巧： 在声明中引入 A||B进行限制，之后分别针对A与B引入特化
    B<int> x;
    // B<double> x;  报错
}