#include <iostream>
#include <compare>

struct Str
{
    explicit Str(int p)
        : val(p)
    {}

    explicit operator int() const  // 类型转化运算符, 没有返回类型, 因为在函数名中已经体现出来了.
    {
        return val;
    }

    friend auto operator+ (Str a, Str b)
    {
        return Str(a.val + b.val);
    }

    explicit operator bool() const  // 类型转化运算符, 没有返回类型, 因为在函数名中已经体现出来了.
    {
        return val == 0;
    }

    friend bool operator == (Str obj, Str obj2)
    {
        return obj.val == obj2.val;
    }

    friend bool operator == (Str obj, int x)
    {
        return obj.val == x;
    }

    auto operator <=> (int x)
    {
        return val <=> x;
    }

private:
    int val;
};

int main()
{
    // ● 类型转换运算符
    // – 与单参数构造函数一样，都引入了一种类型转换方式
    static_cast<Str>(100); // 是合法的,因为类中有单参数的构造函数,    Str(int p): val(p){} 引入了从int到Str的转换关系.

    // – 函数声明为 operator type() const
    Str obj(1);
    static_cast<int>(obj); // 是合法的, 因为引入了operator int() const
    // int v = obj; // 如果operator int() const没有explicit,则可以进行隐式转化
    // std::cout << v << std::endl;

    // – 注意避免引入歧义性与意料之外的行为
    // ● 通过 explicit 引入显式类型转换

    // obj + 3; // 如果不加explicit, 则产生歧义.两者只有一个添加explicit,则可以按照两外一个进行隐式类型转换.
    // 若两者均加上了explicit,则可以直接显式的进行类型转换
    static_cast<int>(obj) + 3;


    // – explicit bool 的特殊性：用于条件表达式时会进行隐式类型转换
    // 虽然已经添加了explitcit
    auto var = obj ? 1: 0; 
    std::cout << var << std::endl;


    // ● C++ 20 中对 == 与 <=> 的重载
    // – 通过 == 定义 !=   c++20可以自动从==定义!=, 当然也可以两者都自己定义.
    std::cout << "==的重载" << std::endl;
    Str x1(1);
    Str x2(1);
    std::cout << (x1 == x2) << std::endl;
    std::cout << (x1 != x2) << std::endl;
    std::cout << (x1 == 2) << std::endl;
    std::cout << (2 == x1) << std::endl;// 在c++20中无错误, 在c++17中则报错, 在20中,可以先尝试operator == (int, Str), 再尝试operator == (Str, int)
    
    std::cout << " <=> 的重载" << std::endl;
    // – 通过 <=> 定义多种比较逻辑
    // – 隐式交换操作数
    std::cout << (1 >= x1) << std::endl;
    // – 注意 <=> 可返回的类型： strong_ordering, week_ordering, partial_ordering
}