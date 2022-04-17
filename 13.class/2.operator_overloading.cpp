#include <iostream>
#include <string>

class Str
{
public:

    Str(int x)
        : val(x)
    {}

    Str& operator= (const Str& input)
    {
        val = input.val;
        return *this;
    }

    Str& operator= (const std::string& input)
    {
        val = static_cast<int>(input.size());
        return *this;
    }

    friend auto operator + ( Str input1, Str input2)  
    {
        std::cout << "operator + is called." << std::endl;
        return Str(input1.val + input2.val);
    }

    friend auto& operator << (std::ostream& ostr, Str input)
    {
        ostr << input.val;
        return ostr;
    }

    int& operator[] (int id)
    {
        return val;
    }

    int operator[] (int id) const
    {
        return val;
    }
    Str& operator++ ()  //前缀++, ++i
    {
        ++val;
        return *this;
    }

    Str operator++ (int) //后缀++,, i++
    {
        Str tmp(*this);  // 后缀涉及到拷贝,性能差,甚至有时还不支持拷贝构造.
        ++val;
        return tmp; 
    }

private:
    int val = 1;
};

struct Str3
{
    Str3* operator -> ()
    {
        return this;
    }

    int bla = 123;
};

struct Str2
{
    Str2(int* p)
        : ptr(p)
        {}

    int& operator * ()  // 返回引用,因此可以执行*ptr = 101;
    {
        return *ptr;
    }

    int operator * () const // 只读
    {
        return *ptr;
    }

    // Str2* operator -> ()  // 返回一个指针
    // {
    //     return this;
    // }

    Str3 operator -> ()// 返回一个结构体
    {
        return Str3{};
    }
    int val = 5;
private:
    int * ptr;
};

int main()
{
    // ● 对称运算符通常定义为非成员函数以支持首个操作数的类型转换
    Str x = 3;
    Str y = 4;
    Str z = x + 4; // 4 会隐式转化为Str
    // Str z = 4 + x; 如果operator定义为成员函数,则不能这样写,找不到Str内部的+.如果重载的operator+ 为非成员函数,则可以调用. 但是使用了Str的private 数据成员,则需要使用friend.
    // 比较好的方式是将friend函数的声明定义均放置在类的内部, i.e. 隐藏友元.
    Str z2 = 4 + x;  // 在解析时, 遇到x,会将类内部的定义的friend函数纳入考虑的范围.

    // ● 移位运算符一定要定义为非成员函数，因为其首个操作数类型为流类型
    std::cout << x << y << std::endl;

    // ● 赋值运算符也可以接收一般参数
    std::cout << "赋值运算符也可以接收一般参数" << std::endl;
    Str z3(1);
    z3 = "111";
    std::cout << z3 << std::endl;

    // ● operator [] 通常返回引用
    std::cout << "operator []" << std::endl;
    z3[0] = 4;
    std::cout << z3[0] << std::endl;   // 调用int& operator[] (int id)

    const Str z4 = 3; // 重载int operator[] (int id) const
    std::cout << z4[0] << std::endl;  // 调用int operator[] (int id) const


    // ● 自增、自减运算符的前缀、后缀重载方法
    std::cout << "operator++" << std::endl;
    Str z5(3);
    std::cout << ++++z5 << std::endl;
    z5++;
    std::cout << z5 << std::endl;

    // ● 使用解引用运算符（ * ）
    // – 注意“ .” 运算符不能重载
    std::cout << "operator *" << std::endl;
    int x2 = 100;
    Str2 ptr(&x2);
    std::cout << *ptr << std::endl; // 调用 int& operator * ()
    *ptr = 101;   

    const Str2 ptr2(&x2);  
    *ptr2; // 调用int operator * () const 

    // 与成员访问运算符（ -> ）模拟指针行为
    // – “→” 会递归调用 操作 “→”
    std::cout << "operator ->" << std::endl;
    int x3 = 10;
    Str2 ptr3(&x3);
    // std::cout << ptr3->val << std::endl;  //调用 Str2* operator -> (), 将ptr-> 翻译为ptr.operator->(), 发现返回的是指针,则然后相当于 ptr.operator->()->val
    std::cout << ptr3->bla << std::endl;  // 将ptr-> 翻译为ptr.operator->(), 发现返回的不是指针而是一个struct,则继续递归调用,直到发现Str3种重载了->且返回指针,则可以取到Str3的bla

}