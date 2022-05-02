#include <iostream>

// 函数模板声明
template <typename T>
void fun(T);

// 函数模板定义
// 函数模板不是一个函数
template <typename T>
// 可以使用class替换掉typename
// T是模板形参，input是一个函数形参
// 在编译期，会实例化一个函数
// 在编译期，先进行语法检查，后模板实例化
// input是运行期
void fun(T input)
{
    std::cout << input << std::endl;
}

// 函数模板重载
template <typename T>
void fun(T* input)
{
    std::cout << *input << std::endl;
}

// 函数模板重载
template <typename T, typename T2>
void fun(T input, T2 input2)
{
    std::cout << input << std::endl;
    std::cout << input2 << std::endl;
}

template <typename T>
// T&& 是万能引用,可以引用左值或右值
// 如果一个变量或者参数被声明为T&&，其中T是被推导的类型，那这个变量或者参数就是一个universal reference。
// auto&& 因为auto声明的变量的类型推导规则本质上和模板是一样的，所以使用auto的时候你也可能得到一个universal references。
void fun2(T&& input)
{
    std::cout << input << std::endl;
}

template <typename T>
void fun3(T input)
{
}

template <typename T, typename T2>
void fun4(T input, T2 input2)
{
}
template <typename T>
void fun5(T input, T input2)
{
}

int main()
{
    // template
    fun<int>(3);  // 实例出了fun<int>函数
    fun(3);  // 隐式实例化

    // 模板必须在实例时可见，放松了对模板的一处定义原则的限制，变成了翻译单元的一处定义原则
    // 如果模板定义写在了一个head.h头文件中，两个cpp文件均include了该头文件，也不会报错。
    // 但是如果是一个定义在头文件中的普通函数，则会报错，此时必须在函数前添加inline， inline由程序级别一处定义原则退化为翻译单元一处定义原则

    // 函数模板重载
    int x = 4;
    fun<int>(&x);

    // 函数模板的类型推导, 与auto类似
    std::cout << "函数模板的类型推导" << std::endl;
    // 函数形参是左值引用/指针
    //   - 忽略表达式类型中的引用
    //   - 利用表达式类型与函数形参模式匹配以确定模板实参
    const int& y = x;
    fun(y);  // cosnt int& -> const int -> T为const int

    // 函数形参是万能引用
    std::cout << "函数形参是万能引用" << std::endl;

    //   - 如果实参表达式是右值,模板形参会被推导为去掉引用的基本类型
    fun2(3);  // int&& x = 3;  T : int
    //  - 如果实参表达式是左值, 模板形参会被推导为左值引用,触发引用折叠
    fun2(x);  // T :int&  ,此时函数形参类型为int& &&, 触发引用折叠(reference collapsing),变为int&

    // https://zhuanlan.zhihu.com/p/99524127 现代C++之万能引用、完美转发、引用折叠  非常好。
    // 引用折叠只有两条规则:
    // 1）一个 rvalue reference to an rvalue reference 会变成 (“折叠为”) 一个 rvalue reference.
    // 2）所有其他种类的"引用的引用" (i.e., 组合当中含有lvalue reference) 都会折叠为 lvalue reference.

    // 函数形参不包含引用
    std::cout << "函数形参不包含引用" << std::endl;
    //   - 忽略表达式类型中的引用
    //   - 忽略顶层const
    //   - 数组/函数转化成相应的指针类型
    int& ref = x;
    fun3(ref);  // T: int
    const int* const ptr = &x;  // 第二个const是顶层const,寿命ptr本身不可以修改. 第一个const是底层const,说明指向的对象不能被修改
    fun3(ptr);  // T: const int*
    int x2[3];
    fun3(x2);   // 此时T: int*
    auto x3 = x2;  // 此时类型退化为int*

    fun4<int>(3, 4); // 同时有显式和隐式, 将T2推导为int

    // fun5(3, 1.2);  无法成功推导
}