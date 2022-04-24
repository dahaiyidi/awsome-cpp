#include <iostream>

// 声明
template <typename T>
class B;


template <typename T2>
void fun4();

template <typename T>
class B
{
public:
    auto fun()
    {
        return B{}; // 在B 内部，相当于B<T>{};
    }
    void fun2(); // 是一声明，在B 外定义

    // 类模板的成员函数模板
    template <typename T2>
    void fun3();

    // 使用的非常少
    template <typename T2>
    friend void fun4();

    //  此时不是成员函数模板
    friend void fun5(B input)  // B 在内部，实际上相当于B<T> 是一个类型
    {
        std::cout << input.x << std::endl;
    }
    friend auto operator + (B input1, B input2)  // B 在内部，实际上相当于B<T> 是一个类型
    {
        B res;
        res.x = input1.x + input2.x;
        std::cout << res.x << std::endl;
        return res;
    }

    friend T;

    int x;
};

// 定义fun2
template <typename T>
void B<T>::fun2()
{

}

// 定义fun3
template <typename T>  // 对应类模板形参
template <typename T2>  // 对应类模板的成员函数模板形参
void B<T>::fun3()
{

}

// fun4 友元
template <typename T2>
void fun4()
{
    B<int> tmp1;
    tmp1.x;

    B<char> tmp2;
    tmp2.x;
}

class C
{
public:
    // 类的成员函数模板 
    template <typename T>
    void fun();
};

// 类的成员函数模板定义
template <typename T>
void C::fun(){}

int main()
{
    //  类模板， 很多特性与函数模板类似
    // 只有在调用时，才会实例化类模板
    B<int> x{6};
    x.fun();
    // 类模板的成员函数模板
    x.fun3<int>();

    // 类的成员函数模板 
    C x2;
    x2.fun<int>();

    fun5(x);

    // c++支持声明模板参数为友元。。
    B<int> x3{7};
    B<int> res = x + x3;

}