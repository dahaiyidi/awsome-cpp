#include <iostream>
#include "header2.h"
#include <vector>

struct Str2
{
    static auto& fun() 
    {
        static std::vector<int> x;
        return x;
    }
};

class some_type
{
public:
    // 基于引用限定符的重载, 但是不能与基于const 的成员函数重载同时使用
    void foo() & ; // 左值引用,描述的是调用对象的性质
    void foo() && ; // 右值引用
    void foo() const & ; 
    void foo() const && ;
};

int main()
{
    Str y;
    y.x = 8;
    y.fun(3);

    some_type t;

    t.foo();  // 调用 void foo() & ;
    some_type().foo(); // 调用void foo() && ;
}