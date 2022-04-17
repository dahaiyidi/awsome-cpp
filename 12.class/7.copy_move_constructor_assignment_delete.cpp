#include <iostream>

class Str
{
public:
    Str()
        : ptr(new int())
    {}

    ~Str()
    {
        delete ptr;
    }

    // 拷贝构造
    Str(const Str& val)
        : ptr(new int())
    {
        *ptr = *(val.ptr);
    }

    // 移动构造
    Str(Str&& val) noexcept
        : ptr(val.ptr)
    {
        val.ptr = nullptr;
    }

    // 拷贝赋值
    Str& operator= (const Str& val)
    {
        *ptr = *(val.ptr);
        return *this;
    }


    int& Data()
    {
        return *ptr;
    }
private:
    int* ptr;
};

// void fun(int) = delete;
void fun(double a)
{
    std::cout << "fun(double) is called." << std::endl;
}

class Str2
{
public:
    Str2() = default;
    Str2(const Str2& val) = default;
    Str2(Str2&& val) noexcept = delete;
};

void fun2(Str2 val)
{

}

int main()
{
    // 通常来说，一个类：
    // – 如果需要定义析构函数，那么也需要定义拷贝构造与拷贝赋值函数
    // – 如果需要定义拷贝构造函数，那么也需要定义拷贝赋值函数
    // – 如果需要定义拷贝构造（赋值）函数，那么也要考虑定义移动构造（赋值）函数
    Str a;
    a.Data() = 3;
    std::cout << a.Data() << std::endl;

    Str b(a);  // 如果不定义拷贝构造函数,则会报 double free 错误
    b = a;  // 如果不定义拷贝赋值函数,则会报 double free 错误

    Str b2 = std::move(a);

    // delete 代表函数不可调用,与未声明是有区别的, delete 函数的名称可以被查找到,函数是存在的,只是无法调用而已.如果未声明,下面的语句则会调用fun(double).
    fun(3);

    // 注意不要为移动构造（移动赋值）函数引入 delete 限定符
    fun2(Str2{}); // 该语句在c++11中会出错,因为会调用Str2的移动构造函数.但是在c++17和20对该语句进行了优化提升性能,不会调用移动构造函数,也就不会报错,与delete相违背.

    
}