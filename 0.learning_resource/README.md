# cawsome-cpp

## c++常见问题

## 待整理

- 在有继承关系的父子类中，构建和析构一个子类对象时，父子构造函数和析构函数的执行顺序分别是怎样的？
- 在有继承关系的类体系中，父类的构造函数和析构函数一定要申明为 virtual 吗？如果不申明为 virtual 会怎样？
- 什么是 C++ 多态？C++ 多态的实现原理是什么？
- 什么是虚函数？虚函数的实现原理是什么？
- 什么是虚表？虚表的内存结构布局如何？虚表的第一项（或第二项）是什么？
- 菱形继承（类 D 同时继承 B 和 C，B 和 C 又继承自 A）体系下，虚表在各个类中的布局如何？如果类B和类C同时有一个成员变了m，m如何在D对象的内存地址上分布的？是否会相互覆盖？



- 统一的类成员初始化语法与 std::initializer_list<T>
- 注解标签（attributes）
- final/override/=default/=delete 语法
- auto 关键字
- Range-based 循环语法
- 结构化绑定
- stl 容器新增的实用方法
- std::thread
- 线程局部存储 thread_local
- 线程同步原语 std::mutex、std::condition_variable 等
- 原子操作类
- 智能指针类
- std::bind/std::function



- 指针、引用、数组、内存
- 引用与指针区别
- 虚机制：虚函数、虚函数表、纯虚函数
- C 和 C++ 的一些区别，比如 new、delete 和 malloc、free 的区别
- 一些关键字的作用：static、const、volatile、extern
- 四种类型转换：static_cast, dynamic_cast, const_cast, reinterpret_cast
- STL部分容器的实现原理，如 vector、deque、map、hashmap
- 模板特化、偏特化，萃取 traits 技巧
- 继承、虚继承、菱形继承等
- 多态： 动态绑定，静态多态
- 重写、重载
- 智能指针原理：引用计数、RAII（资源获取即初始化）思想
- 智能指针使用：shared_ptr、weak_ptr、unique_ptr等
- 编译链接机制、内存布局（memory layout）、对象模型。
- C++11 部分新特性，比如右值引用、完美转发等


链接：https://www.zhihu.com/question/20410487/answer/1593246297

https://www.zhihu.com/question/65209863/answer/1870705008

Ref:
链接：https://zhuanlan.zhihu.com/p/396237325

- https://codeantenna.com/a/Hf7vakqA2T 
- https://www.jianshu.com/p/ec2a4fb21b58
- https://www.jianshu.com/p/139e85f899be
- 已处理：https://zhuanlan.zhihu.com/p/75347892

## General

### c与c++

- C++在C的基础上添加了类。
- C是面向过程的，C++是面相对象的。

## C++11

### C++11特性有哪些？

- auto类型推导
- 智能指针：参考【智能指针章节】
- 多线程
  - std::thread. join()或者detach()
  - 两种封装：std::lock_guard和std::unique_lock
  - 条件变量 std::condition_variable 是C++11引入的一种同步机制，它可以阻塞一个线程或多个线程，直到有线程通知或者超时才会唤醒正在阻塞的线程，条件变量需要和锁std::unique_lock配合使用。
  - 原子操作std::atomic 不需要用到互斥量加锁（无锁）技术的多线程并发编程方式。
- std::function, std::bind
- lambda表达式
- stl容器新增的emplace_back()方法
- for-each循环
- std::chrono库
- std::move 
- 一些关键字的用法(override、final、delete)
- 无序容器

- override和final关键字

- 右值引用

  

## 内存------------------------------

### 描述内存分配方式以及它们的区别?

- 5个区
  - 堆：new,malloc 申请的空间
  - 栈：函数参数，局部变量
  - 全局区（静态区static）：全局变量，静态变量
  - 常量存储区const：存放常量，不允许修改
  - 代码区：存放二进制代码

- 静态存储区：内存在编译期就已经分配好，在程序整个运行期间都存在，如全局变量，static变量
- 栈：在执行函数时，函数内局部变量在栈上创建，函数执行结束时，内存被自动释放。 **从高地址向低地址增长**。
- 在堆上分配（动态内存分配）， 程序运行时，使用malloc和new申请的内存，用户自己负责何时free, delete.**从低地址向高地址增长。容量大于栈**，程序中动态分配的内存在此区域。



### 全局变量和局部变量有什么区别？是怎么实现的？操作系统和编译器是怎么知道的？

https://blog.51cto.com/u_14942403/4633972

- 生命周期不同：全局变量随主程序创建和创建，随主程序销毁而销毁；局部变量在局部函数内部，甚至局部循环体等内部存在，退出就不存在；

- 使用方式不同：通过声明后全局变量程序的各个部分都可以用到；局部变量只能在局部使用。
- 操作系统和编译器通过**内存分配的位置**来知道的，全局变量分配在**全局数据段**并且在程序开始运行的时候被加载。局部变量则分配在**堆栈**里面 。

**从作用域看**：

- 全局变量：其作用范围是“整个工程”，只需在一个源文件中定义，就可以作用于所有的源文件。当然，其他不包含全局变量定义的源文件需要用extern 关键字再次声明这个全局变量
- 静态全局变量：使用 static 关键字修饰，也具有全局作用功能，和全局变量区别在于如果该程序包含多个文件，其作用范围仅在定义的那个文件，不能作用于其它文件，这样即使两个不同的源文件都定义了相同名字的静态全局变量，它们也是不同的变量
- 局部变量：仅仅从定义的位置开始，到定义它的右花括号结束，只在函数执行期间存在，函数的一次调用执行结束后，变量被撤销，其所占用的内存也被收回
- 静态局部变量：局部作用域，它只被初始化一次，自从第一次被初始化直到程序运行结束都一直存在，和局部变量的区别在于函数执行完也还存在。虽然一直存在，但是注意作用域只再局部哦。

**从生存期看**：

- 全局变量：随进程持续性
- 静态全局变量：随进程持续性
- 局部变量：从定义开始到函数结束，函数调用后变量就被撤销，内存被回收
- 静态局部变量：随进程持续性，static 修饰的局部变量其生存期从函数变为整个进程

**从内存分配看**：

- 全局变量：全局（静态）存储区
- 静态全局变量：全局（静态）存储区
- 局部变量：存放在栈中，只有在所在函数被调用时才动态地为变量分配存储单元
- 静态局部变量：全局（静态）存储区

注：

- 全局（静态）存储区：分为DATA段和BSS段。**DATA段（全局初始化区）存放初始化的全局变量和静态变量；BSS段（全局未初始化区）存放未初始化的全局变量和静态变量**。程序运行结束时自动释放。其中BBS段在程序执行之前会被系统自动清0，所以**未初始化的全局变量和静态变量在程序执行之前已经为0**

- 静态变量会被放在程序的静态数据存储区(全局可见)中，这样可以在下一次调用的时候还可以保持原来的赋值。这一点是它与堆栈变量和堆变量的区别

- 变量用static告知编译器，自己仅仅在变量的作用范围内可见。这一点是它与全局变量的区别

- 把局部变量改变为静态变量后是改变了它的存储方式即改变了它的生存期。把全局变量改变为静态变量后是改变了它的作用域，限制了它的使用范围。因此static 这个说明符在不同的地方所起的作用是不同的

- 　A.若全局变量仅在单个C文件中访问，则可以将这个变量修改为**静态全局变量**，以降低模块间的耦合度；

- 　B.若全局变量仅由单个函数访问，则可以将这个变量改为该函数的**静态局部变量**，以降低模块间的耦合度；

- 　C.设计和使用访问动态全局变量、静态全局变量、静态局部变量的函数时，需要**考虑重入问题**（https://bbs.huaweicloud.com/blogs/260727），因为他们都放在静态数据存储区，全局可见；

- D.如果我们需要一个可重入的函数，那么，我们一定要避免函数中使用static变量(这样的函数被称为：带“内部存储器”功能的的函数)

-   E.函数中必须要使用static变量情况:比如**当某函数的返回值为指针类型时，则必须是static的局部变量的地址作为返回值**，若为auto类型，则返回为错指针

  

  

## 一些符号--------------------------

### static的作用

1. 修饰局部变量：存储在静态存储区，默认初始化为0
2. 修饰全局变量或全局函数：只在本文件可见，在其他文件不可见
3. 修饰类的成员变量只能在类外初始化（如int Base::N = 10），
   - 或者用const修饰static在类内或类外初始化，
   - 使用inline static 则需要在类内定义。具体可以见3.friend_inline_static.cpp文件
4. 修饰类的成员函数。注意不能同时用const和static修饰类的成员函数，因为**类中的const修饰的函数，编译器会默认添加一个this指针**，而static函数是属于整个类的，没有this指针，两者相互矛盾。

### const的作用

1. 定义常变量
2. 修饰成员函数，表示**不可修改成员变量的值**

### new、delete、malloc、free关系

- new调用构造函数，delete调用析构函数，与new对应。
- malloc,free 是标准库函数。new，delete是c++运算符。
- 都可以用于申请动态内存和释放内存，但是malloc,free 无法满足非内部数据类型的动态对象的要求。因为对象的创建需要自动调用构造，消亡前需要自动调用析构。而malloc,free 是库函数不是运算符，不在编译期的控制权限之内，不能把执行构造函数、析构函数的任务强加给malloc，free.
- new操作符从自由存储区（free store）上为对象动态分配内存空间，malloc函数从堆上动态分配内存
- new返回指定类型，malloc返回void* 类型需要强制类型转换。
- 内存分配失败时，new返回bad_alloc异常，malloc则返回NULL
- new不需要指定内存的大小 ，malloc需要显式的指定
- new可以被重载，malloc不可以。

### delete, delete[]

- delete只会调用一次析构函数，而delete[]会调用每一个成员的析构函数。
- 当delete操作符用于数组时，它为每个数组元素调用析构函数，然后调用operator delete来释放内存。
- delete与new配套，delete []与new []配套
- 对于内建简单数据类型，delete和delete[]功能是相同的。对于自定义的复杂数据类型，delete和delete[]不能互用。

```c++
int *pInt1=new int [10];
MemTest *mTest1=new MemTest[10];
MemTest *mTest2=new MemTest;
int *pInt2=new int;
delete[]pInt1; //-1-
delete[]pInt2; //-2-
delete[]mTest1;//-3-
delete[]mTest2;//-4- 会报错
```

## 引用----------------------

### 引用&

- 引用就是某个目标变量的“别名”(alias)，对应用的操作与对变量直接操作效果完全相同。
- 申明时就必须要初始化，且不能再修改为其他变量的别名。
- 它本身不是一种数据类型，因此引用本身不占存储单元，系统也不给引用分配存储单元。
- 不能建立引用的数组，数组的元素不能是引用。

```c++
    int a[2] = {0};
    int(&b)[2] = a; // 数组的引用
int & ref[3] = { 2, 3, 5};  // 错误
```

### 引用与指针

- 引用在语言内部用指针实现，引用是操作受限了的指针。
-  指针指向一块内存，它的内容是所指内存的地址；引用是某块内存的别名。
- “sizeof 引用”得到的是所指向的变量（对象）的大小，而“sizeof 指针”得到的是指针本身（所指向的变量或对象的地址）的大小；

### 将“引用”作为函数返回值类型的格式、好处和需要遵守的规则?

- 不能返回局部变量的引用。
- 不能返回函数内部new分配的内存的引用。虽然不存在局部变量的被动销毁问题，但是如果函数返回的引用只是作为一个临时变量出现，而没有被赋予一个实际的变量，则引用所指向的空间（由new分配的）就无法被释放，造成内存泄漏。
- 可以返回类成员的引用，但最好是const。
- 流操作符重载返回值申明为“引用”的作用：流操作符<<和>>，这两个操作符常常希望被连续使用。 还有x = j = 10;
- 在另外的一些操作符中，却千万不能返回引用：+-*/ 四则运算符，会直接返回对象。
- 

### 左值，右值

- An *lvalue* is an expression that refers to a memory location and allows us to take the  address of that memory location via the `&` operator. 
- An *rvalue* is an expression that is not an lvalue. 将亡值，纯右值都是右值

纯右值：运算表达式产生的临时变量、不和对象关联的原始字面量、非引用返回的临时变量、lambda表达式等都是纯右值。

将亡值：通常指将要被移动的对象、T&&函数的返回值、std::move函数的返回值、转换为T&&类型转换函数的返回值，将亡值可以理解为即将要销毁的值，通过“盗取”其它变量内存空间方式获取的值，在确保其它变量不再被使用或者即将被销毁时，可以避免内存空间的释放和分配，延长变量值的生命周期，常用来完成移动构造或者移动赋值的特殊任务。

常左值引用：

```c++
int &c = 10; // error，10无法取地址，无法进行引用
const int &d = 10; // ok，因为是常引用，引用常量数字，这个常量数字会存储在内存中，可以取地址
int a = 4;
int &&b = a; // error, a是左值
int &&c = std::move(a); // ok

#include <iostream>
using namespace std;

static int b = 0;

void PrintV(int &t) {
    cout << "lvalue" << endl;
}

void PrintV(int &&t) {
    cout << "rvalue" << endl;
}

template<typename T>
void Test(T &&t) {
    PrintV(t);
    PrintV(std::forward<T>(t));

    PrintV(std::move(t));
}

int main() {
    Test(1); // lvalue rvalue rvalue
    int a = 1;
    Test(a); // lvalue lvalue rvalue
    Test(std::forward<int>(a)); // lvalue rvalue rvalue
    Test(std::forward<int&>(a)); // lvalue lvalue rvalue
    Test(std::forward<int&&>(a)); // lvalue rvalue rvalue
    return 0;
}

```

### 重载overload和重写override，有的书也叫做“覆盖”）的区别？

- 重载：是指允许存在多个同名函数，而这些函数的参数表不同（或许参数个数不同，或许参数类型不同，或许两者都不同）。在编译期，根据同名函数不同的函数表，对同名函数的名称做了修饰，成为不同的函数。函数的地址在编译期就绑定了。
- 重写：是指子类重新定义父类虚函数的方法。函数地址是运行期绑定。

### 哪几种情况只能用intialization list 而不能用assignment

- 初始化列表允许在创建数据成员的同时为之提供初始值，这比以后再赋值效率更高。
- 当初始化一个reference member时；    
- 当初始化一个const member时；    
- 当调用一个base class的constructor，而它拥有一组参数时；  
- 当调用一个member class的constructor，而它拥有一组参数时；    

initialization list 的 member 初始化顺序是由类中 member 的声明顺序决定的。

### C++是不是类型安全的

不是。两个不同类型的指针之间可以强制转换（用reinterpret cast)

- 

### 给出BOOL，int，float，指针变量 与“零值”比较的 if 语句

```c++
BOOL : 	if ( !a ) or if(a)

int : 	if ( a == 0) // 建议if ( 0 == a), 避免a==0写错为a=0

float :	 const float EXP = 0.000001

			if ( a < EXP && a >-EXP)

pointer : if ( a != NULL) or if(a == NULL)
```

### const 与 #define

- const用于：定义常量，修饰函数参数，修饰函数范围值，被const修饰的东西收到强制保护。有数据类型，编译器可以对其进行类型安全检查
- define只是进行简单的字符替换。

## 指针--------------------------------

### 智能指针

- unique_ptr，只允许基础指针的一个所有者，
- shared_ptr允许有多个所有者，通过计数的方式进行管理，最好是使用make_shared标准库函数。



### 数组与指针的区别

- 用运算符sizeof 可以计算出数组的容量（字节数）。 而sizeof(指针)返回指针本身的字节数。
- 意当数组作为函数的参数进行传递时，该数组自动**退化**为同类型的指针。
- 

### C++ 性质

封装，继承和多态。

## 多态，虚函数，纯虚函数，抽象类，虚表--------------------------------

### 多态，虚函数，纯虚函数

多态：是对于不同对象接收相同消息时产生不同的动作。C++的多态性具体体现在运行和编译两个方面：

- 在程序运行时的多态性通过继承和虚函数来体现；
- 在程序编译时多态性体现在函数和运算符的重载上；

虚函数：在基类中冠以关键字 virtual 的成员函数。  它提供了一种接口界面。

纯虚函数（在函数声明后面加“=0”，不写函数体）的作用：作为接口而存在 纯虚函数不具备函数的功能，一般不能直接被调用。

抽象类（abstract class）：一个类中至少有一个纯虚函数。不能用于直接创建对象实例。但仍可使用指向抽象类的指针支持运行时多态性。

### 多态中的内存布局

 https://blog.csdn.net/dxpqxb/article/details/102794132

```c++

class Person
{
    public:
        Person():mId(0), mAge(20){ ++sCount; }
        static int personCount()
        {
            return sCount;
        }
 
        virtual void print()
        {
            cout << "id: " << mId
                 << ", age: " << mAge << endl;
        }
        virtual void job()
        {
            cout << "Person" << endl;
        }
        virtual ~Person()
        {
            // --sCount;
            cout << "~Person" << endl;
        }
 
    protected:
        inline static int sCount = 0;
        int mId;
        int mAge;
};

typedef void (*FuncPtr)();  // 定义函数指针

int main()
{
    // 加上虚函数后，person的大小增加了8Byte, 正是增加了一个指针的大小，而
    // Person person;
    // cout << "sizeof(person): " << sizeof(person) << endl;
    // cout << "sizeof(int): " << sizeof(int) << endl;
    // cout << "sizeof(int*): " << sizeof(int*) << endl;
    // int *p = (int*)&person;
    // cout << "----" << endl;
    // for (int i = 0; i < sizeof(person) / sizeof(int); ++i, ++p)
    // {
    //     cout << *p << endl;
    // }
    // 以上输出结果为：
    // sizeof(person): 16
    // sizeof(int): 4
    // sizeof(int*): 8
    // ----
    // -1027320336
    // 32759
    // 0
    // 20

    
    Person person;
    int **vtbl = (int**)*(int**)&person;
    for (int i = 0; i < 3 && *vtbl != nullptr; ++i)
    {
        FuncPtr func = (FuncPtr)*vtbl;
        // func();
        ++vtbl;
    }
 
    while (*vtbl)
    {
        cout << "*vtbl = " << *vtbl << endl;
        ++vtbl;
    }
    return 0;
} 
```



### 原子操作的原理？





### 什么函数不能是虚函数？

可以声明成虚函数：普通的成员函数，析构函数

- 普通函数（非成员函数）；普通函数在编译期就绑定了地址。
- 静态成员函数：只有一份大家共享
- 内联成员函数：inline编译期间展开，虚函数是在运行期间绑定。 矛盾！
- 构造函数：语义上就不支持。 因为构造函数是为了构造对象的，而virtual的目的是能根据不同的对象产生不同的动作，前提是必须要有对象。矛盾！
- 友元函数：可以声明成虚函数的就行！（普通的成员函数或析构函数）



### 基类的析构函数不是虚函数，会带来什么问题？

- 在继承层次中，基类的析构函数一般建议声明为虚函数。

- 派生类的析构函数用不上，会造成资源的泄漏。

- ```c++
  base *pBase = new derived;
  delete pBase; // 如果基类中的析构函数不是virtual,则 派生类的析构函数不会调用。
  ```

  

### static

作用

```c++
修饰普通变量，修改变量的存储区域和生命周期，使变量存储在静态区，在 main 函数运行前就分配了空间，如果有初始值就用初始值初始化它，如果没有初始值系统用默认值初始化它。

修饰普通函数，表明函数的作用范围，仅在定义该函数的文件内才能使用。在多人开发项目时，为了防止与他人命令函数重名，可以将函数定位为 static。

修饰成员变量，修饰成员变量使所有的对象只保存一个该变量，而且不需要生成对象就可以访问该成员。

修饰成员函数，修饰成员函数使得不需要生成对象就可以访问该函数，但是在 static 函数内不能访问非静态成员。
```

### inline 内联函数
```c++

    相当于把内联函数里面的内容写在调用内联函数处；

    相当于不用执行进入函数的步骤，直接执行函数体；

    相当于宏，却比宏多了类型检查，真正具有函数特性；

    不能包含循环、递归、switch 等复杂操作；

    在类声明中定义的函数，除了虚函数的其他函数都会自动隐式地当成内联函数。
```

使用
```c++

// 声明1（加 inline，建议使用）
inline int functionName(int first, int secend,...);

// 声明2（不加 inline）
int functionName(int first, int secend,...);

// 定义
inline int functionName(int first, int secend,...) {/****/};

// 类内定义，隐式内联
class A {
    int doA() { return 0; }         // 隐式内联
}

// 类外定义，需要显式内联
class A {
    int doA();
}
inline int A::doA() { return 0; }   // 需要显式内联
编译器对 inline 函数的处理步骤
```



## 函数----------------

### 将程序跳转到指定内存地址

```c++
*((void (*)( ))0x100000 ) ( );
// 先转换为函数指针，再调用
```



## STL

### vector

- 下标访问，for each访问，at()访问。at()加了越界判断，效率会低一点。
- reserve: 提前申请一定数量的空间，避免总是重新分配空间，但不能降低capacity,。
- resize：如果resize<当前size，则capacity不变，size直接降低到指定值，超出size范围的元素均不存在了。如果resize>当前size，capacity 设置到指定值，新的元素用参数（或0）代替。
- clear: size为0， capacity不变
- shrink_to_fit: Requests the removal of unused capacity.



## 程序分析



```c++
int (*s[10])(int) // 函数指针数组，每个指针指向一个int func(int param)的函数。
```



```c++
char str1[] = "abc";
char str2[] = "abc";
const char str3[] = "abc";
const char str4[] = "abc";
const char *str5 = "abc";
const char *str6 = "abc";
char *str7 = "abc";
char *str8 = "abc";
cout << ( str1 == str2 ) << endl;//0 分别指向各自的栈内存
cout << ( str3 == str4 ) << endl;//0 分别指向各自的栈内存
cout << ( str5 == str6 ) << endl;//1指向文字常量区地址相同
cout << ( str7 == str8 ) << endl;//1指向文字常量区地址相同
// str1,str2,str3,str4是数组变量，它们有各自的内存空间；而str5,str6,str7,str8是指针，它们指向相同的常量区域。
```





```c++
int id[sizeof(unsigned long)] // 正确，这个 sizeof是编译时运算符，编译时就确定了 ,可以看成和机器有关的常量。
```



```c++
// 什么含义
void * ( * (*fp1)(int) )[10];
// fp1是一个指针，指向一个函数，这个函数的参数为int型，函数的返回值是一个指针，这个指针指向一个数组，这个数组有10个元素，每个元素是一个void*型指针。

float ( *(* fp2)(int,int,int) )(int);
// fp2是一个指针，指向一个函数，这个函数的参数为3个int型，函数的返回值是一个指针，这个指针指向一个函数，这个函数的参数为int型，函数的返回值是float型。

int (* ( *fp3)() )[10]();
// fp3 是一个指针，指向一个函数，函数的参数为空，返回值为一个指针，指针指向一个数组，数组中有10各元素，每个元素是一个指针，指向参数为空，返回值为int的函数。
```







## 在线编程

https://cppinsights.io/

https://godbolt.org/