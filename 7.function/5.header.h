#include <iostream>
// inline 将程序级别的一次定义原则变成了翻译单元级别的一次定义原则。 （一个cpp里面定义一次）
// 也就说原来没有inline 的时候，main.cpp和source.cpp都定义了fun，但是不能重复定义函数，就会报错。但是引入inline，并分别include 之后，
// 每个翻译单元里面就会分别有一个inline所修饰的函数，进而可以进行优化，可能会将简单的函数展开到函数调用处
//
inline void fun()
{
    std::cout << "hello" << std::endl;
}