#include <iostream>

struct Str
{
    int x;
};

int x2;
int main()
{
    Str a;
    a.x;
    Str* ptr = &a;
    (*ptr).x; //等同于ptr->x;

    decltype((a.x)) y = a.x; // 类型为int&, 左操作数a是左值，a.x 返回的是左值
    decltype((Str().x)) y2 = std::move(a.x); //类型为int&&,即右值引用, Str()是右值，Str().x返回xvalue

    decltype((ptr->x)) y3 = a.x; // 类型为int&， ptr->x 返回左值

    int x = 1;
    int y1 = 2;
    true ? (++x) : (++y1); // x=2, y=2, 不符合条件的那一条语句被忽略

    // 如果表达式均是左值，那么就返回左值，否则返回右值

    std::cout << (2, 3) << std::endl; // , 保证从左到右运算，求值结果为右操作数。 因此显示3 
    // 注意和函数调用时写的,区分开，fun(x, y) 这里面的并不是,运算符，x,y计算的顺序没有规定。 x + y，求值顺序也是不一定的。
    // C++17中还有很多表达式可以确保求值顺序。

    int x2;
    sizeof(int); 
    // sizeof int; 报错，类型名必须加()
    sizeof(x2);
    sizeof x2; // 正常运行，表达式可以不用加(),不建议使用。

    int* ptr2 = nullptr;
    // *ptr; //产生未定义的行为
    sizeof(*ptr2); // 假装对*ptr2求值，事实上没有求。

    std::cout << ::x2 << std::endl; // 打印全局域的x2

}