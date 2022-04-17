#include <iostream>

class Str
{
public:
// 代理构造函数,先执行代理函数，再执行本函数
    // Str() : Str(3)
    // {
    //     std::cout << "here 1" << std::endl;
    // }

    // Str(int input)
    // {
    //     x = input;
    //     std::cout << x << std::endl;
    //     std::cout << "here 2" << std::endl;
    // }

    // Str(const std::string& val)
    // {
    //     std::cout << "before:" << x2 << std::endl;
    //     x2 = val; // 赋值, 没有初始化列表时先缺省初始化，再赋值。
    //     std::cout << "after:" << x2 << std::endl;
    // }
    
    // 列表初始化，可以避免赋值操作，提高性能,由于int& ref;的存在，必须使用列表初始化。
    //  注意元素的初始化顺序与其声明顺序相关，与初始化列表中的顺序无关
    // 因此，为了便于阅读避免差生bug，初始化列表的顺序最好要与声明的顺序相同。
    // 使用初始化列表覆盖类内成员初始化的行为
    Str(const std::string& val, int& r) 
        : x2(val)
        , x(9)
        , ref(r)
    {
        std::cout << "列表初始化" << x2 << std::endl;
        ref = 4;

    }

private:

    int x; // 缺省初始化
    std::string x2;  // 缺省初始化
    int& ref;
};

struct Str2
{
    size_t x;
    int y;
};

struct Str3
{
    Str3(const std::string& input)
        : x(input)
    {}
    Str3() = default;  // 合成缺省构造函数

    std::string x;
};

int main()
{
    // Str x;
    // Str x2(4);

    int y1 = 1;
    Str x4("hello", y1);
    std::cout << y1 << std::endl;

    Str2 m; // 使用缺省构造函数, 使用缺省初始化来初始化数据成员，int为随机值
    // 但是如果类中有int& ref;类似的语句时，则无缺省构造函数
    std::cout << m.x << ' ' << m.y << std::endl;

    Str2 m2();  // 这其实是一个函数的声明。

    Str3 m3;  //使用default关键字定义缺省构造函数

}