#include <iostream>

class Out
{
    // 如果将下面的程序放置在In class后，则不可以。
    using MyInt = int;
    inline static MyInt val2 = 3;
    int vvv = 100;

public:
    class In
    {
    public:
        inline static MyInt val = val2;
        // int xxx = vvv;  // 错误. int vvv = 100;是声明不是定义，vvv的定义是在创建Out对象时才进行的。
    };
};

void fun()
{
    using MyInt = int;
    int vvv = 5;
    struct Helper
    {
        // 可以访问外围函数中定义的类型声明、静态对象与枚举
        MyInt x;
        int y;
        // int xxx = vvv; 错误
        // 局部类不能定义静态数据成员
        // inline static int val = 100; 错误
        // 局部类可以定义成员函数，但成员函数的定义必须位于类内部
        int inc()
        {
            return x++;
        }
    }; 
    
    Helper h;
    h.inc();
};

int main()
{
    // 嵌套类
    Out::In ojb;

    //  嵌套类中的名称查找失败时会在其外围类中继续查找， 前提是必须将需要的东西定义在嵌套类上面
    Out::In::val;

    // 嵌套类与外围类单独拥有各自的成员

    // 局部类：可以在函数内部定义的类

}