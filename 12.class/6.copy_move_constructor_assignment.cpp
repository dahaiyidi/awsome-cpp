#include <iostream>


class Str
{
private:
    int val = 8;
    std::string a = "abc";
    int* ptr = nullptr;
    
public:
    // Str() = default; // 缺省构造函数
    Str(int* x = nullptr)
        : ptr(x)
    {
        std::cout << "constructor is called." << std::endl;
    }

    // 析构函数，无参数，无返回值
    // 内存回收在调用完析构函数后才进行
    // 通常不能抛出异常
     ~Str() noexcept
    {
        std::cout << "deconstructor is called." << std::endl;
        delete ptr;
    }

    Str(const Str&) = default; // 拷贝构造函数
     // Copy constructor -- no copying allowed!
    // Str(const Str& a) = delete;

    Str(Str&& x) noexcept = default;  // 移动构造函数

    // 拷贝赋值, 返回当前的引用，因此可以使用连等m3 = m2 = m; 
    // 在一些情况下编译器会自动合成
    Str& operator= (const Str& x)
    {
        if(&x == this)
        {
            return *this;
        }
        val = x.val;
        a = x.a;
        std::cout << "copy assignment is called." << std::endl;
        return *this;
    }

     // Copy assignment -- no copying allowed!
    // Str& operator=(const Str& a) = delete;

    // 移动赋值
    // 在一些情况下编译器会自动合成
    Str& operator=(Str&& x)
    {
        // 如果没有判等的操作，对m = std::move(m);的写法是危险的
        if(&x == this)
        {
            std::cout << "dummy move assignment." << std::endl;
            return *this;
        }

        std::cout << "real move assignment." << std::endl;
        // std::cout << *ptr << std::endl;
        delete ptr;
        ptr = x.ptr;
        x.ptr = nullptr;
        val = std::move(x.val);
        a = std::move(x.a);
        return *this;
    }


};


int main()
{
    Str m;
    Str m2;
    Str m3;

    // 拷贝赋值
    m3 = m2 = m; //调用拷贝赋值函数 其实就是m2.operator=(m);

    // 移动赋值
    std::cout << "移动赋值" << std::endl;
    m2 = std::move(m);
    // // std::cout << m.ptr << std::endl;
    
    m3 = std::move(m3);
    
    // std::cout << "***********************" << std::endl;
    
    std::cout << "测试new" << std::endl; 
    Str* m4 = new Str(); // new 的必须要显示的使用delete进行内存回收
    delete m4;
    std::cout << "程序末尾" << std::endl;
}