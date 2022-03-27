#include <iostream>
#include <vector>
#include <algorithm>

using K = int(int);
K fun;// 相当于声明了这样的函数： int fun(int);
// int(int) fun2; 报错， int(int) 不能单独作为一个类型
// K fun2 = {return 0;} // 报错， 只声明函数，不能定义函数， 这一点，和数组不一样

int inc(int x)
{
    return x + 1;
}
int dec(int x)
{
    return x - 1;
}

using M = int[3];
M a = {1, 2, 3}; // 相当于int a[3] = {}
M* b; // 相当于int (*b) [3];  数组指针

// 高阶函数
int Twice(K* f, int  x)
{
    int tmp = (*f)(x);
    return tmp * 2;
}

void Demo(K* input){} // input 为函数指针，与数组类似
// void Demo(K input){} 同上

void fun3(int) {}
void fun3(int, int) {}

auto fun4(bool input)
{
    if (input)
        return inc;
    else
        return dec; // 返回函数指针
}

int main()
{
    // 函数指针并不常用，后面可以使用lambda，功能更好，更高效。 

    K* f = &inc; // 定义了函数指针,相当于int (*f)(int),可以与数组相类比
    std::cout << (*f)(100) << std::endl;
    // 有了函数指针，可以让一个函数接收一个函数，或者返回一个函数。
    std::cout << Twice(&inc, 100) << std::endl;

    // transform 高阶函数
    std::vector<int> a{1, 2, 3};
    std::transform(a.begin(), a.end(), a.begin(), &inc);  // 变成了2， 3，4 
    for (int i = 0; i < a.size(); ++i)
    {
        std::cout << a[i] << std::endl;
    }

    // 类型退化
    auto f2 = inc; // 为函数指针: int (*)(int)

    Demo(inc); // 相当于Demo(&inc)

    // 函数重载
    using K2 = void(int);
    K2* f3 = fun3;

    // 使用一个高阶函数fun4
    std::cout << (*fun4(true))(100) << std::endl;
}