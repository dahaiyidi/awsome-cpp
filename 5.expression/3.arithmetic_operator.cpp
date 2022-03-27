#include <iostream>

int main()
{

    7 * + 3; // 是合法的，+作为一元操作符，为第一优先级

    // +
    int a[3] = {1, 2, 3};
    const auto& x = +a; // 相当于： int *const & x = +a; 将a转化为指针 。使用的很少

    // 一元操作符产生intefral promotion
    short x1 = 3;
    auto y = -x1; // 相当于 int y = -static_cast<int>(x);

    //  %， 结果符号与第一个操作数相同。满足 (m / n) * n + m % n == m
    std::cout << -5 % 4 << std::endl; // -1
    std::cout << 5 % -4 << std::endl; // 1

}