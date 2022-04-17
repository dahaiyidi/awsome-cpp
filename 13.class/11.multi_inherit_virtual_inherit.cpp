#include <iostream>
#include <vector>
#include <memory>

struct Base
{
    virtual double GetValue() = 0;
    virtual ~Base() = default;
    int x;
};

struct Derive : public Base
{
    Derive(int x)
        : val(x){}
    double GetValue() override  // 此处返回值类型要与基类中相同.
    {
        return val;
    }
    int val;
};

struct Derive2 : public Base
{
    Derive2(double x)
        : val(x){}
    double GetValue() override
    {
        return val;
    }
    double val;
};

struct Base0
{
    virtual ~Base0() = default;
    int x;
};
struct Base2: virtual Base0 // 虚继承
{
    virtual ~Base2() = default;
};

struct Base3: virtual Base0  // 虚继承
{
    virtual ~Base3() = default;
};

// 多重继承
struct Derive3: public Base2, public Base3
{

};

int main()
{
    // 通过基类指针实现在容器中保存不同类型对象
    std::vector<std::shared_ptr<Base>> vec;
    vec.emplace_back(new Derive{1});
    vec.emplace_back(new Derive2{3.14});
    std::cout << vec[0]->GetValue() << std::endl;
    std::cout << vec[1]->GetValue() << std::endl;

    Derive3 d;
    d.x;  // 由于多重继承,导致有两个x, 错误:request for member ‘x’ is ambiguous, 使用虚继承可以解决.
}