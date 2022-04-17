#include <iostream>

struct Str
{
    
public:  //struct缺省的权限是public
    inline static int x = 9;
    // int Str::x = 8; // 如果在类内部不写inline， 则无法在类内初始化，必须在类外初始化
    // 可以这样理解，由于这个是类共享的，不同的对象具有同一个x，因此无法在类内部定义，而只能在类内声明，类外定义
    // 有了inline, 我们就可以直接在类内进行定义初始化了。联想inline 修饰函数时的效果，在不同的文件中可以有相应的定义，但是最终只会保留一份。
    int y;
};

int main();  // 本行可以省略,在类内可以首次声明友元类或友元函数。
class S2;    // 本行可以省略
//class 缺省的访问权限是private
class S
{
    // 友元，打破封装，可以是一个函数，也可以是一个类
    // 不要滥用。
    // friend放置到private，protected，public都是无所谓的。
    friend int main();
    friend class S2;
    // friend int ::main() 在使用限定符时，就要求在类之前必须有main的声明，此处无法被看作一个声明。

    // 隐藏友元，常规的名称无法查找到该函数
    // 减轻编译期负担
    friend void fun2() // 可以在类内定义，fun()的作用域时全局域，但是通过常规的名称查找是无法找到的。
    {
        std::cout << "隐藏友元fun2" << std::endl;        
        std::cout << S::x << std::endl;        
    }

    friend void fun3(const S& val) // 可以在类内定义，fun()的作用域时全局域，但是通过常规的名称查找是无法找到的。
    {
        std::cout << "隐藏友元fun3" << std::endl;        
        std::cout <<val.y << std::endl;        
    }

    inline static int x = 888;
    int y = 7;
};

class S2
{
public:
    void fun()
    {
        // 由于使用了S，所以不可能将S2的定义放置到S的上面
        std::cout << S::x << std::endl;
    }
};

int main()
{
    std::cout << Str::x << std::endl;
    std::cout << S::x << std::endl;
    S2 y;
    y.fun();

    // 隐藏友元
    // fun2();// 无法通过编译，因为通过常规的名称查找是无法找到的。
    S y2;
    fun3(y2); // 此时是可以调用的。因为，他会尝试在类S中查找
}