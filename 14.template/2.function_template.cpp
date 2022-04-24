#include <iostream>

template <typename T = int>
void fun(typename std::remove_reference<T>::type input)
{
}

template <typename T = int>
void fun(T , T)
{
    std::cout << "template" << std::endl;
}

template <typename T, typename T2>
void fun(T , T2)
{
}


template <typename Res = double, typename T>   //  而函数的缺省实参只能放置在后部, 建议向函数一样,将缺省的放置在后部,以简化程序.
Res fun2(T , T)
{
}

template <typename T, typename T2>
void fun3(T , T2)
{
    std::cout << "template <typename T, typename T2> fun(3)" << std::endl;
}

void fun3(int, double)
{
    std::cout << "fun3(int, double)" << std::endl;
}

template <typename T>
void fun3(T , char)
{
    std::cout << "template <typename T> void fun3(T , char)" << std::endl;
}

int main()
{
    // 当无法模板实参推导成功,则使用缺省模板实参
    fun(3);
    // 报错,此时T可以推导(因此到不了使用缺省模板实参的步骤),但是推导后有歧义,则没有一个函数模板/函数与之匹配, SFINAE(替换失败并非错误)
    // 如果定义了,template <typename T, typename T2>
    // void fun(T , T2)则会与之匹配成功
    fun(3, 4.2);
    fun2(2, 3); 

    //  如果显式指定的模板实参,必须从左到右依次给出

    fun3(3, 4.2);  // 都是完美匹配的情况下,且匹配等级相等,则会选择非模板
    fun3(3, 4.2f);  // 此时函数不是完美匹配,则使用函数模板
    fun3(3, 'a');   // 当匹配多个函数模板完美匹配,则会选择比较特殊的函数模板
}