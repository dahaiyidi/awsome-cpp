#include <iostream>

struct Str
{
    Str(int p)
        : val(p)
    {}
    int operator() ()
    {
        return val;
    }
    int operator() (int x, int y)
    {
        return val + x + y;
    }
    bool operator() (int x)
    {
        return val++ < x;
    }
private:
    int val;
};

int main()
{
    // 使用函数调用运算符构造可调用对象
    // lambda 就是对此进行的简化
    Str obj(1);
    std::cout << obj() << std::endl;
    std::cout << obj(1, 2) << std::endl;
    std::cout << obj(2) << std::endl;

}