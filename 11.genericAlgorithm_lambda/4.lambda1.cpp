#include <iostream>

struct Str
{
    auto fun()
    {
        int val = 3;
        // this 捕获
        // auto lam = [val, this] ()
        // *this 捕获，将复制一个对象，不用担心对局部对象的销毁
        auto lam = [val, *this] ()
        {
            return val > x;
        };
        return lam;
    }
    int x;
};

auto wrapper()
{
    Str s;
    return s.fun();
}

int main()
{
    // lambda
    // 会被翻译成一个类，可以放到cppinsights里面查看后台转换

    int y = 3; 
    int z = 4;
    // 捕获：针对函数体中使用的局部自动对象进行捕获
    // static int y = 3; //捕获y是不合法的，无需捕获，lambda内部直接就可以得到y
    // 值捕获， 内部对y的修改均无效
    auto x = [y](int val) mutable
    {
        ++y;
        return val > y;
    }; // []用来捕获,不写[y],则lambdda内部无法取到y的取值，相当于在lambda构建的类中，引入一个成员y
    // 不加mutable，提提示read-only variable ‘y’
    std::cout << x(5) << " y = " << y << std::endl;

    // 混合捕获 ， 在类的内部声明了int& y;
    auto x2 = [&y, z](int val) 
    {
        ++y;
        return val > z;
    };
    std::cout << x2(5) << " y = " << y << std::endl;

    auto x1 = [](int val) -> float
    {
        if(val > 3)
        {
            return 3.0;
        }
        else
        {
            return 2.0f;
        }
    }; // 若不写-> float,则返回值类型无法由double和float推断出来。

    // [=]自动值捕获
    // [&] 自动引用捕获
    auto x3 = [=] (int val){return val > z;}; 
    std::cout << x3(5) << std::endl;
    
    // [&, z], z是值捕获， 其余均是引用捕获
    // [=, &y], y是引用捕获，其余均是值捕获
    auto x4 = [&, z](int val) 
    {
        ++y;
        return val > z;
    };
    std::cout << x4(5) << " y = " << y << std::endl;

    // 初始化捕获
    auto x5 = [z = y](int val) mutable
    {
        return val > z;
    };
    std::cout << "初始化捕获： " << x5(10) << std::endl;

    std::string a = "hello";
    auto lam = [y = std::move(a)]()
    {
        std::cout << y << std::endl;
    };
    lam();
    std::cout << a << std::endl;

    int y1 = 1;
    int y2 = 2;
    // 捕获时计算， 提高运算的性能
    auto lam2 = [y = y1 + y2]()
    {
        std::cout << y << std::endl;
    };
    lam2();

    //  this, *this 捕获
    auto lam3 = wrapper();
    lam3();
}