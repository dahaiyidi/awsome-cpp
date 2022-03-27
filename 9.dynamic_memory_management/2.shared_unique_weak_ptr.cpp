#include <iostream>
#include <memory>
#include <functional>

std::shared_ptr<int> fun()
{
    std::shared_ptr<int> res(new int(100));
    return res;
}

void dummy(int*){}

std::shared_ptr<int> fun3()
{
    static int res = 3;
    return std::shared_ptr<int>(&res, dummy); // 什么都不做
}

void fun2(int* ptr)
{
    std::cout << "fun2 is called." << std::endl;
    delete ptr;
}

std::unique_ptr<int> fun4()
{
    auto res = std::make_unique<int>(3);
    return res; // 采用std::move的方式
}

struct Str
{
    std::weak_ptr<Str> m_nei; // 不会增加用于初始化m_nei的对象的引用计数
    // std::shared_ptr<Str> m_nei;
    ~Str()
    {
        std::cout << "~Str() is called. \n";
    }
};

int main()
{
    // 智能指针
    // auto_ptr 从c++17中删除

    // shared_ptr  #include <memory>
    std::shared_ptr<int> x(new int(4));  // 不用担心内存泄漏, 类中包含引用计数，此时为1,当计数为0时，就会自动delete
    std::cout << *x << std::endl; // 对智能指针解引用，但是std::shared_ptr<int> 不等同于int*
    {
        std::shared_ptr<int> y = x; // 类中包含引用计数，此时为2
        std::cout << x.use_count() << ' ' << y.use_count() << std::endl;
    }
    std::cout << x.use_count() << std::endl;

    auto y2 = fun(); // 此时就是比较安全的方式
    std::cout << *(y2.get()) << std::endl;  // get() 返回 int*， 对int* 进行解引用

    y2.reset(new int(3)); // reset 将原始的资源释放，关联一个新的资源
    y2.reset(); // 释放资源，但不关联新的资源 

    // 修改内存回收逻辑
    {
        std::shared_ptr<int> x1(new int(3), fun2); // 自定义销毁函数
    }
    auto x2 = fun3(); // 此时，x2 销毁时，引用计数为0，调用deleter dummy, 但是dummy什么都不做，因此其内部的static int res得以保留，直到程序结束才销毁。
    // 可以借助修改内存回收逻辑，实现内存池的功能。

    // std::make_shared
    std::shared_ptr<int> ptr(new int(3));
    auto ptr2 = std::make_shared<int>(3); // 效果等同于上一行，但是性能更好，建议使用。

    // 对对象数组的支持。  C++17 支持 shared_ptr<T[]> ； C++20 支持 make_shared 分配数组
    // g++ -Wall -std=c++2a main.cpp -o main && ./main
    auto ptr3 = std::make_shared<int[]>(5);

    //  shared_ptr 管理的对象不要调用 delete 销毁
    // delete ptr.get();  //造成二次释放
    // std::shared_ptr<int> ptr4(ptr.get()); //也是不可以的，会错认为，ptr4拥有这块内存。//造成二次释放

    int* ptr4 = new int(3);
    std::shared_ptr<int> ptr5(ptr4);
    // std::shared_ptr<int> ptr6(ptr4);// 造成二次释放

    // unique_ptr
    std::cout << "unique_ptr" << std::endl;
    std::unique_ptr<int> x3(new int(3));
    std::cout << x3 << std::endl;
    // std::unique_ptr<int> x4(x3); 不能共享，只能被x3独占。
    std::unique_ptr<int> x5 = std::move(x3); // 构造一个将亡值，将x3的资源转移给x5
    std::cout << x3.get() << std::endl;  // 0
    std::cout << x5.get() << std::endl;

    std::unique_ptr<int> x6 = fun4(); 

    // 为unique_ptr 指定内存回收逻辑
    {
        std::unique_ptr<int, decltype(&fun2)> x7(new int(3), fun2);
        
        // 使用lambda
        std::unique_ptr<int, std::function<void(int*)>> p(new int, [](int* ptr)
            {
                std::cout << "destroying from a custom deleter...\n";
                delete ptr;
            });  // p 占有 D

    }

    // weak_ptr  防止循环引用而引入的智能指针
    std::cout << "weak_ptr" << std::endl; 
    // 如果Str内部的m_nei不是weak_ptr，以下循环引用导致Str的析构函数不会被调用
    std::shared_ptr<Str> x8(new Str{});
    std::shared_ptr<Str> x9(new Str{});
    x8->m_nei = x9;  // m_nei是weak_ptr,不会增加x9的引用计数
    x9->m_nei = x8;  // m_nei是weak_ptr,不会增加x8的引用计数

    // 将weak_ptr 转化为shared_ptr
    if (auto ptr = x8->m_nei.lock(); ptr)
    {
        std::cout << "can access pointer\n";
    }
    else
    {
        std::cout << "cannot access pointer\n";
    }
}