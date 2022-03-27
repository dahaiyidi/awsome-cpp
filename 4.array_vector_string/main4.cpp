#include <iostream>
#include <vector>

int main()
{
    // vector
    std::vector<int> x(3, 1);
    std::vector<int> y;
    y = x; // 支持复制

    std::vector<int> z(3); // z里面全是0

    // 比较
    std::vector<int> x1 = {1, 2, 3};
    std::vector<int> x2 = {1, 3, 2};
    std::cout << (x1 < x2) << std::endl;

    std:: cout << x1[20] << std::endl;
    // std:: cout << x1.at(20) << std::endl; 当vector越界会报错。

    // 两种方式： 函数std::begin(x1)  方法x1.begin() 不再是指针，而是iterator， 模仿指针的行为

    std::vector<int>* ptr = &x1;
    ptr->size();
}