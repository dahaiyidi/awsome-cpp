#include <iostream>
#include <string>
#include <memory>

struct Base
{
    Base()
    {
        fun();
    }
    virtual void fun(int x = 3)
    {
        std::cout << "Base: " << x << std::endl;
    }
    virtual ~Base() 
    //将基类的析构设定为virtual,派生类的析构也是virtual. 如果不加virtual,当Base* 指向一个派生类时,在delete 该基类指针时,可能不会调用派生类的析构
    {
        std::cout << "Base deconstructor " << std::endl;

    }
protected:
    virtual void fun2()
    {
        std::cout << "Base::fun2 " << std::endl;
    }
};

// struct Derive final : Base  //不会被继承
struct Derive : Base
{
public:
    
    void fun2() override
    {
        std::cout << "Derive::fun2 "<< std::endl;
    }

    Derive()
        : Base() // 可以不用写这行,因为会默认先调用基类的构造函数
    {
        fun();
    }
    void fun(int x = 4) override final
    // final : 派生自Derive的类不会再对fun override
    // 如果类里面所有的虚函数都是final,则可以再类定义中加入final, struct Derive final: Base
    {
        std::cout << "Derive: " << x << std::endl;
    }

    ~Derive()
    {
        std::cout << "Derive deconstructor " << std::endl;

    }
};


void proc(Base& b)
{
    b.fun();
}


int main()
{
    // 由虚函数所引入的动态绑定属于运行期的行为,与编译期行为有所区别.
    // 虚函数的缺省实参只会考虑静态类型
    Derive d;  // 显式Base: 3 Derive: 4, 这是在构造Derive对象时(运行期)的行为. 先构造基类,再构造派生类
    proc(d);   //Derive: 3 , 在[编译期]就已经将proc函数内部翻译成b.fun(3),编译期只知道proc的形参的静态类型为Base,因此虚函数缺省实参就是fun(3).

    // 虚函数的调用成本高于非虚函数,因为由指针的跳转

    // final

    // 使用指针或引用引入动态绑定,不能直接使用Base的对象,也就是说不能是proc(Base b)
    // 使用指针或引用,背后都只是传入指针,而不是实例化一个Base对象(况且还不能实例化抽象类),然后根据vtable来确定调用哪个函数.

    // 析构
    std::cout << "------deconstructor start " << std::endl;
    Derive* d2 = new Derive();
    delete d2; // 先析构派生类,再析构基类
    std::cout << "------ " << std::endl;

    // 要在基类的析构中添加virtual
    Derive* d3 = new Derive();
    Base* b = d3;
    delete b; // 如果在基类中析构函数没有写virtual, 这样的操作是未定义的,不同编译器不一样. 大概率只调用Base的析构函数
    // delete d3; // 如果直接delete派生类的指针,则肯定会调用基类的析构函数,则可以不定义析构为virtual
    std::cout << "------deconstructor end " << std::endl;

    // 在派生类中修改虚函数的访问权限
    std::cout << "在派生类中修改虚函数的访问权限" << std::endl;
    d.fun2();
    Base& b2 = d;
    // b2.fun2(); //在编译期,b2的静态类型为Base,确定fun2为protected,无外部访问权限.报错.

    std::cout << "------ end " << std::endl;
}