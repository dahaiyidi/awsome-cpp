#include <iostream>
#include <type_traits>


template <int x>
constexpr auto fun = (x % 2) + fun<x / 2>;

template <>
constexpr auto fun<0> = 0;

constexpr auto x = fun<99>;

// 数组
template <typename...> class Cont;
using Input = Cont<int, char, double, bool, void>;

// 使用循环处理数组：获取数组中 id=0,2,4,6... 的元素
// Imp声明
template <typename Res, typename Rem>
struct Imp;
// 特化, 这是循环主体逻辑
template <typename... Processed, typename T1, typename T2, typename... TRemain>
struct Imp<Cont<Processed...>, Cont<T1, T2, TRemain...>>
{
    using type1 = Cont<Processed..., T1>;
    using type = Imp<type1, Cont<TRemain...>>::type;
};
// 特化,这是终止条件
template <typename... Processed, typename T1>
struct Imp<Cont<Processed...>, Cont<T1>>
{
    using type = Cont<Processed..., T1>;
};
// 特化,这是终止条件
template <typename... Processed>
struct Imp<Cont<Processed...>, Cont<>>
{
    using type = Cont<Processed...>;
};

using Output = Imp<Cont<>, Input>::type;


// 获取数组中最后3个元素
// Imp2
template <typename Res, typename Rem>
struct Imp2
{
    using type = Res; // 当其他条件不满足，则直接使用这个
};
// 特化, 这是循环主体逻辑
template <typename U1, typename U2, typename U3, typename T, typename... TRemain>
struct Imp2<Cont<U1, U2, U3>, Cont<T, TRemain...>>  // 第一个参数 有3个元素，且第二个参数不为空
{
    using type1 = Cont<U2, U3, T>;
    using type = Imp2<type1, Cont<TRemain...>>::type;
};

template <typename U1, typename U2, typename T, typename... TRemain>
struct Imp2<Cont<U1, U2>, Cont<T, TRemain...>>// 第 一个参数 有2个元素，且第二个参数不为空
{
    using type1 = Cont<U1, U2, T>;
    using type = Imp2<type1, Cont<TRemain...>>::type;
};

template <typename U1, typename T, typename... TRemain>
struct Imp2<Cont<U1>, Cont<T, TRemain...>>// 第 一个参数 有1个元素，且第二个参数不为空
{
    using type1 = Cont<U1, T>;
    using type = Imp2<type1, Cont<TRemain...>>::type;
};

template <typename T, typename... TRemain>
struct Imp2<Cont<>, Cont<T, TRemain...>>// 第 一个参数 有0个元素，且第二个参数不为空
{
    using type1 = Cont<T>;
    using type = Imp2<type1, Cont<TRemain...>>::type;
};

using Output2 = Imp2<Cont<>, Input>::type;

int main()
{
    // 循环
    // 使用递归实现
    // 计算二进制中1的个数
    std::cout << x << std::endl;

    // 使用循环处理数组：获取数组中 id=0,2,4,6... 的元素
    std::cout << std::is_same_v<Output, Cont<int, double, void>> << std::endl;

    // 获取数组中最后三个元素
    std::cout << std::is_same_v<Output2, Cont<double, bool, void>> << std::endl;

}