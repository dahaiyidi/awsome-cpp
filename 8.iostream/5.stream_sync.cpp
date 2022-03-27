#include <iostream>

int main()
{
    std::cout << "whats your name.\n" << std::flush; // 如果不写flush, 则该字符串可能不会及时打印出来。 \n 和flush可以合并为std::end()
    std::cerr << "whats your name.\n" << std::flush;  // cerr缺省是std::unitbuf,去报错误可以及时报出来。
    std::string name;
    std::cin >> name;

    // std::cout << std::unitbuf; // 设置每次输出后自动同步，但是影响性能

    // 绑定tie
    // cin 绑定到了 cout 上，意味着cin之前，肯定会刷新cout的缓冲区。

}