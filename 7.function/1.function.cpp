#include <iostream>
#include <vector>
#include <initializer_list>

// extern "C" Add(){} 将c++的函数转化为c形式的函数，不再支持重载，在待链接的文件里面nm main.o | grep c++filt -t 的函数名字直接为Add。
// extern "C" int Add(int x, int y)
// {
//     return x + y;
// }

struct Str
{
    Str() = default;
    Str(const Str&)
    {
        std::cout << "copy constructor is called. \n";
    }
};

void fun(Str){}

// 数组作为形参
void fun1(int* par){}
// 一下3种形式均等同于上一行，也就说说传递数组时，退化为int*
// void fun1(int par[]){}
// void fun1(int par[111]){} // 建议不要写数字，以防出现误导。
// void fun1(int par[1]){}

// 防止类型退化
void fun3(int (&par) [3]){} //类型为int (&) [3]

void fun2(int (*par) [4]){} 
// 以下两行退等同于会转化为上面的一行
// void fun2(int par[][4]){} 
// void fun2(int par[100][4]){}  不要写第一个数字，而第二个数字是必须要写的。

void fun4(std::initializer_list<int> par){}

// 以下是错误的行为，std::initializer_list只包含begin，end两个指针，而{1, 2}在函数结束时就不存在，返回两个指针是没有用处的。
// std::initializer_list<int> fun5()
// {
//     return {1, 2};
// }

// 在一个翻译单元中，每个形参的缺省实参只能定义一次
// 以下是合法的。 但是如果第一和第二行交换则会报错，也就是说缺省实参必须要从右向左
// 也可以在头文件中定义缺省z，在其他文件中定义缺省y。
void fun5(int x, int y, int z = 3);
void fun5(int x, int y = 2, int z);
void fun5(int x, int y, int z){}

int aa = 3;
void fun6(int x = aa)
{
    std::cout << x << std::endl;
}



int main2()
{
    // 复制
    Str val;
    fun(val);
    fun(Str{});// C++17 强制省略复制临时对象

    // 传参过程的类型退化，及避免
    int a[3];
    fun1(a); // a 退化成int*

    int a1[3][4];
    fun2(a1);  // a 退化成int (*)[4]

    fun3(a);

    // 变长参数
    fun4({1, 2, 3}); 
    fun4({1, 2});
    // fun4({1, "hello"});  报错，必须要同样的类型
    // 此外还有可变长度模板参数
    // 使用...表示形式参数， 在c++中不建议使用，不安全。


    // 缺省实参为对象时，实参的缺省值会随对象值的变化而变化. 但是不建议使用，因为容易混淆
    aa = 4;
    fun6(); // 打印4
}

int main(int argc, char* argv[])
{
    std::cout << "argc=" << argc << std::endl;
    // 运行可执行文件，并传入参数./main 1 2
    // argc 为3
    // argv[0]为 ./main, argv[1] 为1...
    for (int i = 0; i < argc; ++i)
    {
        std::cout << argv[i] << std::endl;
    }
}