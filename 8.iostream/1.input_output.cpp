#include <iostream>
#include <iomanip>

int main()
{
    union
    {
        int x;
        double y;
    };

    x = 4;
    std::cout << x << std::endl;
    std::cout << y << std::endl;

    // int x1;
    // std::cin.read(reinterpret_cast<char*>(&x1), sizeof(x1)); // reinterpret_cast 重新解释
    // std::cout << x1 << std::endl; // 对人类阅读不友好。

    // 格式控制
    char x2 = '1';
    // std::cout.setf(std::ios_base::showpos); // 为数值加上正负号
    // std::cout.width(10); // 为数值加上正负号
    // std::cout.fill('.');
    // std::cout << x2 << ' ' << static_cast<int>(x2) << std::endl; //  static_cast<int>(x2)结果为+49
    // 注意 width 方法的特殊性：触发后被重置因此在输出static_cast<int>(x2)时已经不会满足width格式化要求了

    // 操纵符， 方便格式化
    std::cout << std::showpos << std::setw(10) << std::setfill('.') << x << '\n' << std::setw(10) << static_cast<int>(x2) << '\n';

    //  提取会放松对格式的限制

    // 提取 C 风格字符串时要小心内存越界
    // char x3[3]; // 可以使用std::string
    // std::cin >> std::setw(3) >> x3;  // 限制最多3个char
    // std::cout << x3 << std::endl;
}