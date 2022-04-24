#include <iostream>
#include <vector>
#include <type_traits>

template <typename T>
concept IsIntOrFloat = std::is_same_v<T, int> || std::is_same_v<T, float>;

// template <typename T>
//     requires IsIntOrFloat<T>  // requires从句
// 可以直接替换掉typename
template <IsIntOrFloat T>  // 类型constraint
void fun(T input)
{

} 

template <typename T1, typename T2>
concept IsDiff = !std::is_same_v<T1, T2>;

template<typename T1, typename T2>
    requires IsDiff<T1, T2>
void fun(T1 input1, T2 input2)
{}

// 用作类型constrait时，少传递一个参数，推导出的类型作为首个参数
template <IsDiff<int> T>  // 类型constraint T 的约束是：IsDiff<T, int>
void fun2(T input)
{

} 

// 判断派生关系
// template <class T, class U>
// concept Derived = std::is_base_of<U, T>::value;

// template<Derive<Base> T>
// void f(T); // T 由Derived<T, Base> 约束

int main()
{
    // concepts  from x++20
    // 编译期谓词，基于给定的输入，返回true,false
    // IsIntOrFloat
    std::cout << IsIntOrFloat<int> << std::endl;
    std::cout << IsIntOrFloat<char> << std::endl;

    // 使用requires对模板进行限制
    fun(2);
    // fun(true);  // 编译错误constraints not satisfied

    // fun(2, 3);// 2, 3 是相同的类型，无法匹配
    fun(2, 2.1); // 匹配成功

    fun2(3.1);
}