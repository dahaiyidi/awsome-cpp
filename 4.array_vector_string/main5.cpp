#include <iostream>
#include <vector>

int main()
{
    // string
    std::string x(3, 'a');
    std::string y = x;
    // std::string y(x);
    y += " !";
    std::cout << (x < y) << std::endl;
    y = "new";

    // y = "aaa" + "bbb"; 报错

    // 转换为C字符串——使用'\n'结束
    auto ptr = y.c_str(); // 返回一个指针，指向一个C 字符串
    std::cout << ptr << std::endl;
}