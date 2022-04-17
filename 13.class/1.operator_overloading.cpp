#include <iostream>

class Str
{
public:
    int val = 1;

    // 实现为成员函数会以 *this 作为第一个操作数
    auto operator () (int y)  // – 除 operator() 外其它运算符不能有缺省参数
    {
        return val + y;
    }

    auto operator + ( Str y)  
    {
        Str z;
        z.val = val + y.val;
        return z;
    }
};

// 重载不能发明新的运算，不能改变运算的优先级与结合性，通常不改变运算含义
// – 函数参数个数与运算操作数个数相同,也就是对于+来说,只有两个形参. 参数至少一个为类类型
// – 除 operator() 外其它运算符不能有缺省参数
// – 可以选择实现为成员函数与非成员函数
// ● 通常来说，实现为成员函数会以 *this 作为第一个操作数（注意 == 与 <=> 的重载

// auto operator + (Str x, Str y)  
// {
//     Str z;
//     z.val = x.val + y.val;
//     return z;
// }

int main()
{

    // 运算符重载
    Str x;
    Str y;

    Str z = x + y;
    std::cout << z.val << std::endl;
    std::cout << y(10) << std::endl;

    //根据重载特性，可以将运算符进一步划分（参考资料）：
    // – 可重载且必须实现为成员函数的运算符（ =,[],(),-> 与转型运算符）
    // – 可重载且可以实现为非成员函数的运算符
    // – 可重载但不建议重载的运算符（ &&, ||, 逗号运算符）
    //   ● C++17 中规定了这三个符号的形参相应的求值顺序,但没有方式实现短路逻辑
    // – 不可重载的运算符（如 ? ：运算符）
}