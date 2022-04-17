#include <iostream>

struct Base
{

private:
    void fun() {}

};

struct Base2 : Base
{


};

// – 注意：继承部分不是类的声明
// struct Derice : public Base;  // 不是类的声明
struct Derive;

class Derive : public Base2
{

    void fun2();

};

class Derive2 : public Base2
{
public:
    Derive2() : Derive2(3){};
    Derive2(int)
    {
        std::cout << "Derive2 constructor is called." << std::endl;
    }
};

class Derive22 : public Derive2
{
public:
    Derive22(int a)
        : Derive2(a)
    {
        std::cout << "Derive22 constructor is called." << std::endl;
    }
};


int main()
{

    // ● 通过类的继承（派生）来引入 是一个 的关系（ “ ” 参考图片来源）
    // – 通常采用 public 继承（ struct V.S. class ） //struct 缺省是public继承,class缺省是private继承
    // – 使用基类的指针或引用可以指向派生类对象
    Derive d;
    Base& ref = d;
    Base* ptr = &d;

    // – 静态类型 V.S. 动态类型
    // 动态类型在运行期制造的,可以在运行期发生改变. 静态类型在编译期制造的.
    Derive2 d2;
    Base& ref2 = d; 
    // ref2.fun2(); // 错误,编译期看静态类型.
    Base* ptr2 = &d; // ptr2静态类型是Base*
    ptr2 = &d2;

    // – protected 限定符：派生类可访问

    // ● 类的派生会形成嵌套域
    // – 派生类所在域位于基类内部
    // – 派生类中的名称定义会覆盖基类
    // – 使用域操作符显式访问基类成员
    // – 在派生类中调用基类的构造函数, 使用初始化列表的形式,先调用基类的构造函数
    Derive22 x(8);
}