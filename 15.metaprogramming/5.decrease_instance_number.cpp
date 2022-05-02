#include <iostream>
#include <vector>
#include <type_traits>

template <size_t ID, typename TDummy = void>
struct imp
{
    constexpr static size_t value = ID + imp<ID - 1>::value;
};

template <typename TDummy>
struct imp<0, TDummy>
{
    constexpr static size_t value = 0;
};

template <size_t A>
struct Wrap_
{
    // c++标准规定，不能为嵌套类模板引入完全特化，使用TDummy辅助完成，部分特化
    // template <size_t ID, typename TDummy = void>
    // struct imp
    // {
    //     constexpr static size_t value = ID + imp<ID - 1>::value;
    // };

    // template <typename TDummy>
    // struct imp<0, TDummy>
    // {
    //     constexpr static size_t value = 0;
    // };

    template <size_t ID>
    constexpr static size_t value = imp<A + ID>::value;
};

// 避免实例化
template <typename T>
struct Identity
{
    using type = T;
};
// std::remove_reference_t<int &> 对应于std::remove_reference<int &>::type, 由于需要获取type成员，两者都需要实例化，但是只用到第二个
using Res = std::conditional_t<false, std::remove_reference_t<int &>, std::remove_reference_t<double &>>;
// 可以将实例化的过程放到外面
using Res2 = std::conditional_t<false, std::remove_reference<int &>, std::remove_reference<double &>>::type;

using Res3 = std::conditional_t<true, Identity<double&>, std::remove_reference<double &>>::type;

// 使用 std::conjunction / std::disjunction 引入短路逻辑
template <typename T>
constexpr bool intORdouble = std::disjunction<std::is_same_v<T, int>, std::is_same_v<T, double>>;


int main()
{
    std::vector<int> a;
    std::vector<int> b; // 低二次使用相同的类型，所需要的时间要少一些。

    // 提取重复逻辑以减少实例个数
    // 构造了很多实例 
    std::cout << Wrap_<3>::value<2> << std::endl; // A:3, ID:2
    //构造的实例 Wrap_<3>::imp<5>, Wrap_<3>::imp<4>...Wrap_<3>::imp<0>

    std::cout << Wrap_<10>::value<2> << std::endl; // A:10, ID:2
    //构造的实例 Wrap_<10>::imp<12>, Wrap_<10>::imp<11>...Wrap_<10>::imp<0>

    // 如果将imp放置到Wrap_外，则可以减少构造很多实例
    // 构造的实例为imp<12>， imp<11>， imp<10>... imp<0>

    // conditional 使用时避免实例化
    std::cout << "std::conditional..." << std::endl;
    std::cout <<  std::is_same_v<Res2, double> << std::endl;
    std::cout <<  std::is_same_v<Res3, double&> << std::endl;

    // 使用 std::conjunction / std::disjunction 在编译期引入短路逻辑 from c++17
    // 在编译期，使用&& 或 || 则没有短路逻辑

    // 减少分摊复杂度的数组元素访问操作


}