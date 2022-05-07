#include <iostream>
#include <string>

union Str
{
    int x;
    int y;
};


struct S
{   

    enum Type
    {
        Char,
        Int
    };

    // union Str2
    union // 匿名联合, 将x,y 作为S的数据成员，因此在S中不可以再重复定义新的具有相同名字的成员。 起到x,y 共享内存的作用。同时简化代码的编写
    {
        char x;
        int y;
    };
    
    Type t;
    // Str2 obj; 
};

union Str3
{
    std::string x;
    int y;
};

int main()
{
    // union:将多个类型合并到一起以节省空间
    std::cout << sizeof(Str) << std::endl;
    Str obj;
    obj.x = 100;
    std::cout << obj.y << std::endl;

    // S::Str2 obj2;
    // obj2.x = 'c';
    // std::cout << sizeof(S::Str2) << std::endl;
    // std::cout << obj2.y << std::endl;  // 未定义的行为

    // 通常与枚举一起使用
    // S s;
    // s.t = S::Char;  // 通过s的t成员标记union对象的当前类型
    // s.obj.x = 'c';


    // 匿名联合
    S s;
    s.t = S::Char;
    s.x = 'c';  // 书写形式比s.obj.x = 'c';更简洁

    // 在联合中包含非内建类型 from C++11 , union代码更复杂
}