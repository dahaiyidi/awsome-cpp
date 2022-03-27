#include <iostream>
#include <new>

int* fun()
{
	int* res = new int(2); // in heap
	// int res = 2; // very dangerous, res in in stack.
	return res;
}
int* fun2()
{
    char ch[sizeof(int)]; // 如果不是sizeof(int), 则对于下一句来说，程序是非常危险的
    int* y4 = new (ch) int(4); //跳过分配内存的步骤直接在已经存在的内存上构造对象
    return y4;
}

struct alignas(256) Str{}; // 256字节对齐

int main()
{
	int x = 3; // in stack, memory is released automatically.
	int * y = fun(); // in heap, get the address of the the memory
	std::cout << *y << std::endl;
	delete y;

	int* y1 = new int; // 分配了一段内存，用于存放int，进行缺省初始化，而在stack上的变量会是随机值
    std::cout << *y1 << std::endl;  // 0

    int* y2 = new (std::nothrow) int[5]{1, 2, 3}; // 如果不写{}，则进行缺省初始化, std::nothrow 表明，如果分配内存不成功则返回nullptr
    if(y2 == nullptr)
    {
        std::cout << "y2 is nullptr" << std::endl;
        // ...
    }
    std::cout << y2[2] << std::endl;  // 0

    int* y6 = (y2 + 1);
    // delete[] y6; //错误
    delete[] y2;  // 表示删除一个数组


    // placement new
    std::cout << "placement new" << std::endl;  // 0
    char ch[sizeof(int)]; // 如果不是sizeof(int), 则对于下一句来说，程序是非常危险的
    int* y3 = new (ch) int(4); //跳过分配内存的步骤直接在已经存在的内存上构造对象
    // 传入的指针可以指向heap或者stack
    std::cout << *y3 << std::endl;  // 

    int* y4 = fun2(); // 非常危险，指向了已经被销毁的内存
    // std::cout << *y4 << std::endl;  // 

    //auto
    int* y5 = new auto(3); // auto 自动推导为int， 但是不能int* y5 = new auto； 此时auto不知道从哪里推导类型

    // new与内存对齐
    Str* ptr = new Str();
    std::cout << ptr << std::endl;  // 内存的地址一定以00结尾，因为内存是256字节对齐的

    // delete
    int* x1 = 0; // nullptr
    // if(...)
    // {
    //     x1 = new int(3);
    // }
    delete x1; //如果x1是nulllptr, 则什么都不做
    // delete x1; //不能delete两次

    // 
    int x2;
    // delete &x; //不能delete 非new的内存
    // C语言的形式：malloc 使用free释放内存

    // 调整系统自身的 new / delete 行为.不要轻易使用

}