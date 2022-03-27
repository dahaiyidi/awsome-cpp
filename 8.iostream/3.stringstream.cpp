#include <iostream>
#include <sstream>
#include <iomanip>


int main()
{
    // 内存流
    std::ostringstream obj1;
    // obj1 << std::setw(10) << std::setfill('.') << 1234; //操纵符
    obj1 << 1234;
    std::string res = obj1.str(); // 调用obj1的内存以字符串呈现
    std::cout << res << std::endl;

    std::istringstream obj2(res);
    int x;
    obj2 >> x;
    std::cout << x << std::endl;

    // 打开模式： in, out, ate, app
    std::ostringstream buf2("test", std::ios_base::ate);
    buf2 << '1';
    std::cout << buf2.str() << '\n'; // test1, 如果不加入 std::ios_base::ate， 则结果是为1est

    // 小心避免使用 str().c_str() 的形式获取 C 风格字符串
    std::string res2 = buf2.str();
    auto c_res = res2.c_str(); // 正确
    auto c_res2 = buf2.str().c_str(); // 错误，结果不可控。 buf2.str() 是一个右值，在执行完改行之后，所在内存被释放
    std::cout << c_res << ' ' << c_res2 << std::endl;

    // 字符串拼接优化
    // 以下代码性能差
    std::string x1; // 在内存中操作， 不断进行内存开辟，拷贝，释放
    x1 += "hello";
    x1 += "hello";
    x1 += "hello";
    x1 += "hello";
    std::cout << x1 << std::endl;

    std::ostringstream obj; // 在缓冲区内操作
    obj << "hello";
    obj << "hello";
    obj << "hello";
    obj << "hello";
    std::cout << obj.str() << std::endl;
}