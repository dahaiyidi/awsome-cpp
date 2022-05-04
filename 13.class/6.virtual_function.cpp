#include <iostream>

struct Base2{};

struct Derive2 : Base2 {};

struct Base
{
    virtual Base2& baseMethod() // virtual 不是函数签名
    {
        std::cout << "Base::baseMethod() is called." << std::endl; 
        static Base2 b;
        return b;
    }
    int baseMember;
};

struct Derive : Base
{
    // – 函数签名保持不变（返回类型可以是原始返回指针 / 引用类型的派生指针 / 引用类型）, virtual不属于签名的一部分.
    // – 虚函数特性保持不变
    // 对基类中的virtual函数进行修改,只能进行类似的修改: 可以将返回的类型由Base2&改为Derive2&  
    // 但是返回值类型不可能由void 转化为double等操作,会被认为不match
    // 也不能修改形参,否则会被认作是不同的函数,也即构成了重载的关系,overloading
    // 通过override可以限定所写的函数是对虚函数的重写,如果不对,则直接给出报错信息,而不是将错就错.因此更有利于程序检查.
    Derive2& baseMethod() override // 虽然没有写virtual, 但还是虚函数
    {
        std::cout << "Derive::baseMethod() is called." << std::endl; 
        static Derive2 inst;
        return inst;
    }
    
};

struct myClassDerived: public Base
{
    virtual void derivedMethod() {}
    int derivedMember;
};

struct myClassDerived2: public myClassDerived
{
    virtual void derivedMethod2() {}
    int derivedMember2;
};

void proc(Base& b)
{
    b.baseMethod();
}

struct Base3
{
    // 纯虚函数, 作为一个接口, 类为抽象基类
    // 不能声明抽象基类的对象,但是可以是指针,引用
    virtual void fun() = 0;

    // 只能在类外部引入纯虚函数的定义, 使用场景非常少.
    // 并不能改变Base3是一个抽象基类的本质, 还是不能实例化
    // 其派生类依然要override纯虚函数才能实例化
};

// 纯虚函数的类外定义,使用的情况非常少.
// 如何调用纯虚函数呢?在Derive3中写Base3::fun()
void Base3::fun()
{
    std::cout << "Base3::fun() is called" << std::endl;    
}

struct Derive3: Base3
{
    // 只有重写了所有纯虚函数,才不会是抽象类,才能实例化.
    void fun()
    {
        Base3::fun();
        std::cout << "Derive3::fun() is called" << std::endl;
    }
};

struct Derive3_d: Derive3
{

};

void proc3(Base3& b)
{
    b.fun();
}

int main()
{
    // ● 通过虚函数与引用（指针）实现动态绑定
    // – 使用关键字 virtual 引入
    // – 非静态、非构造函数可声明为虚函数
    // – 虚函数会引入vtable结构
    myClassDerived2 d;
    Base& b = d;
    Base* ptr = &d; // ptr的静态类型是Base*, 动态类型是myClassDerived2*

    // 如果将Base的virtual注释掉,则下面程序会出错
    // 只要Base中有virtual,程序也可以正常
    // ● dynamic_cast, 在运行期发生, static_cast, const_cast 在编译期进行
    // 高性能程序要慎用dunamic_cast, 耗费时间.
    myClassDerived2& b2 = dynamic_cast<myClassDerived2&>(b);
    myClassDerived2* ptr2 = dynamic_cast<myClassDerived2*>(ptr);

    myClassDerived& b3 = dynamic_cast<myClassDerived&>(b);    
    myClassDerived* ptr3 = dynamic_cast<myClassDerived*>(ptr);


    // ● 虚函数在基类中的定义
    // – 引入缺省逻辑
    Derive d2;
    // ● 虚函数在派生类中的重写（ override ）
    d2.baseMethod(); // 调用Derive::baseMethod(), 如果在Derive中没有覆盖,则调用Base的函数
    Base& b4= d2;
    b4.baseMethod(); // 还是调用Derive::baseMethod(), 如果将Base中的virtual删除,则调用Base::baseMethod()
    // 若没有了vtable,所有类型均在编译期绑定, 也就是静态类型.而有了virtual之后,就可以进行动态绑定,也就是发动态类型.

    //动态多态: 使用动态类型实现运行期的多态. 通过基类和派生类的virtual实现. 
    // 虚表在编译阶段就可以构造出来, 调用速度低于普通函数
    //虚表， C++ 虚函数表剖析 https://zhuanlan.zhihu.com/p/75172640 非常好！！！！！！！
    // 每个包含了虚函数的类都包含一个虚表。 多继承有多个虚表
    // 虚表是一个指针数组，其元素是虚函数的指针，每个元素对应一个虚函数的函数指针。需要指出的是，普通的函数即非虚函数，其调用并不需要经过虚表
    // 虚表是属于类的，而不是属于某个具体的对象，一个类只需要一个虚表即可。同一个类的所有对象都使用同一个虚表。
    // 编译器在类中添加了一个指针__vptr，*__vptr，用来指向虚表。
    // “对象的虚表指针用来指向自己所属类的虚表，虚表中的指针会指向其继承的最近的一个类的虚函数”
    // 指向Derived对象的Base的指针p, 虽然p是基类的指针只能指向基类的部分，但是虚表指针__vptr亦属于基类部分，所以p可以访问到Derived对象的虚表指针，因此p可以访问到B vtbl。
    // 经过虚表调用虚函数的过程称为动态绑定，其表现出来的现象称为运行时多态。动态绑定区别于传统的函数调用，传统的函数调用我们称之为静态绑定，即函数的调用在编译阶段就可以确定下来了。
    // 什么时候会执行函数的动态绑定？这需要符合以下三个条件：
    // -通过指针来调用函数
    // -调用的是虚函数
    // -指针upcast向上转型（继承类向基类的转换称为upcast）
    // https://zhuanlan.zhihu.com/p/41309205 虚函数与虚基类的深入探讨（内存模型）

    // proc的参数根据动态绑定,就可以实现不同的效果.
    std::cout << "proc函数测试" << std::endl; 
    proc(d2);
    Base b5; // b5的静态类型和动态类型均是Base
    proc(b5);


    // – 可以通过 = 0 声明纯虚函数，相应地构造抽象基类
    std::cout << "纯虚函数,抽象基类" << std::endl; 
    // Base3 b31; 错误
    Base3* b3_ptr;
    Derive3 d31;
    Base3& ref31 = d31;
    Derive3_d d3_1;
    proc3(ref31);

    // – override 关键字  from c++
}