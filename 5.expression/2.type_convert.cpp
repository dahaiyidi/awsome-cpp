#include <iostream>
void fun(void* par, int t)
{
    // 这是c语言的形式，不建议使用。
    if(t == 1)
    {
        int* ptr = static_cast<int*>(par);
        // ...
    }
    else if(t == 2)
    {
        double* ptr = static_cast<double*>(par);
        // ...
        
    }
}

int main()
{
    // 少用显示类型转换，因为有风险。

    // static_cast 是在编译器进行
    static_cast<double>(3) + 0.5;
    int* ptr;
    double* ptr2;
    void* v = ptr;
    // int* ptr2 = static_cast<int*>(v);
    fun(ptr, 1);

    // dynamic_cast 在运行期进行

    // const_cast
    int x = 3;
    const int& ref = x;
    int& ref2 = const_cast<int&>(ref); // 这是非常危险的行为
    ref2 = 4;
    std::cout << x <<std::endl; // 4

    const int x1 = 3;
    const int& ref3 = x1;
    int& ref4 = const_cast<int&>(ref3); // 这是非常危险的行为
    ref4 = 4;
    std::cout << x1 <<std::endl; // 本编译器结果是：3,由于x1是const int， 在编译时，编译器直接将x1替换为3，虽然可以编译通过，但是已经违反意图。但是不同编译器可能有不同的结果。

    // reinterpret_cast重新解释
    int x2 = 3;
    // double y = reinterpret_cast<double>(x2);  报错
    int* ptr3 = &x2;
    double* ptr4 = reinterpret_cast<double*>(ptr3);
    std::cout << *ptr4 <<std::endl; // 但是结果不是3，是一个诡异的值。因为int强行解析成double。

    // C形式的类型转换(在c++中不建议使用)
    // 它会尝试使用各种转换方式，只要有一个转换成功就成功，则结果不受控。
    (double) 3;
}