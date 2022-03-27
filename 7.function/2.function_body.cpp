#include <iostream> 

int fun(){}

// 危险行为
int& fun2()
{
    int x = 3;
    return x;
}

// 危险行为
int* fun3()
{
    int x = 3;
    return &x;
}


int& fun4()
{
    static int x = 3;
    return x;
}

struct Str
{
    Str() = default;
    Str(const Str&)
    {
        std::cout << "copy constructor is called.\n";
    }
};

Str fun5()
{
    Str x;
    return x;
}


int main()
{
    int x = fun();
    std::cout << x << std::endl; // 隐式返回，返回一个无意义的数
    // 但是main的隐式返回为0

    // 小心返回自动对象的引用或指针
    int& ref = fun2(); // 危险行为
    int* ptr = fun3();  // 危险行为
    int& ref2 = fun4(); // 但是返回局部静态对象，则可以使用

    Str a;
    Str b = a; // 此时会调用拷贝构造

    Str res = fun5(); // 返回值优化（ RVO ）—— C++17 对返回临时对象的强制优化, 不会调用拷贝构造

}