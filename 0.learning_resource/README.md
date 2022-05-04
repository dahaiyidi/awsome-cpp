# awsome-cpp

## c++面试

- https://codeantenna.com/a/Hf7vakqA2T 
- https://www.jianshu.com/p/ec2a4fb21b58
- https://www.jianshu.com/p/139e85f899be

### static

作用

    修饰普通变量，修改变量的存储区域和生命周期，使变量存储在静态区，在 main 函数运行前就分配了空间，如果有初始值就用初始值初始化它，如果没有初始值系统用默认值初始化它。

    修饰普通函数，表明函数的作用范围，仅在定义该函数的文件内才能使用。在多人开发项目时，为了防止与他人命令函数重名，可以将函数定位为 static。

    修饰成员变量，修饰成员变量使所有的对象只保存一个该变量，而且不需要生成对象就可以访问该成员。

    修饰成员函数，修饰成员函数使得不需要生成对象就可以访问该函数，但是在 static 函数内不能访问非静态成员。

### inline 内联函数
```

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


## 在线编程

https://cppinsights.io/

https://godbolt.org/