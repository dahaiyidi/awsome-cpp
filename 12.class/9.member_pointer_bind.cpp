#include <iostream>
#include <type_traits>
#include <functional>

class Str
{
public:
    int x = 888;
    int y;
    inline static int z;
    void fun(double x) 
    {
        std::cout << x << std::endl;
    }
};

int main()
{
    // 使用的较少

    // 成员指针
    // 数据成员指针
    int Str::* ptr = &Str::x; //ptr类型为:  int Str::*, 指向Str:: 域内的成员, 成员类型是int
    std::cout << std::is_same_v<decltype(ptr), int Str::*> << std::endl;
    // int Str::* ptr4 = &(Str::z);  // 注意域操作符子表达式不能加小括号, &(Str::z)的类型为int* , z的类型是int
    auto ptr3 =  &Str::x;
    int Str::* ptr2 = &Str::y;
    // ptr2 - ptr1; 不能运算

    // 解引用 需要给出相应的对象.
    Str obj;
    obj.x = 3;
    std::cout << obj.*ptr << std::endl;

    Str* ptr_obj = &obj; // 对象指针
    std::cout << ptr_obj->*ptr << std::endl;


    // 成员函数指针
    void (Str::* ptr_fun)();  // ptr_fun 指向Str::域内的成员函数,该成员函数类型是void()

    void (Str::* ptr_fun2)(double) = &Str::fun;

    // bind
    auto ptr4 = &Str::fun;
    Str obj2;
    (obj2.*ptr4)(10.1);

    // 基于成员函数指针
    std::cout << "基于成员函数指针的bind" << std::endl;
    auto x = std::bind(ptr4, obj2, 10.2);
    x();

    // 基于数据成员指针构造可调用对象
    std::cout << "基于数据成员指针的bind" << std::endl;
    auto x2 = std::bind(ptr, obj2);
    std::cout << x2() << std::endl;

}