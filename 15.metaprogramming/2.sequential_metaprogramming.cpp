#include <iostream>

// 类型转换元函数
// 这就是元函数，只不过通过struct扩展起来
template <typename T, int S>
struct Fun_
{
private:
    using RemRef = typename std::remove_reference<T>::type;  // 去引用
public:
    using type = typename std::add_const<RemRef>::type;  // 加const
    constexpr static int value = (sizeof(T) - S);
};

template <typename T, int S>
constexpr auto Fun = Fun_<T, S>::value;

int main()
{

    // 代码通常放到模板中，以头文件的形式提供
    // 顺序代码，这是在编译期完成的
    constexpr int res = Fun<int&, 4>;  // const int x = 3;
    std::cout << res << std::endl;

}