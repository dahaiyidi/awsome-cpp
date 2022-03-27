#include <iostream>
#include <cmath>

int main()
{
    // a && b; 先对a求值，再对b求值
    // a + b; 没有规定a和b的求值顺序
    // a && b || c; // && 的优先级高于||
    // (a || (b && c))

    // 不要串联：
    int a = 3;
    int b = 4;
    int c = 5;
    std::cout << (c > b > a) << std::endl; // 返回0 因为c>b 的比较结果需要再与a比较，此时会将true转化为1

    a == true; // 相当于a == 1, 因此，不要使用。

    // <=> Spaceship operator from c++20
    // a <=> b 返回 strong_ordering, weak_ordering, partial_ordering
    auto res = (a <=> b);// 将res 代表ab的关系，只需要比较一次，而如果使用if， elseif ... 则需要比较很多次
    if(res > 0){}
    else if(res < 0){}
    else if(res == 0){}

    if(res == std::strong_ordering::greater){}
    else if(res == std::strong_ordering::less){}
    else if(res == std::strong_ordering::equal){}

    auto res2 = (sqrt(-1) <=> 1.0); // 值为std::partial_ordering::unordered

}