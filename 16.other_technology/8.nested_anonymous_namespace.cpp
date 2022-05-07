#include <iostream>

namespace Out
{
    int x;
}

//     // – 注意同样的名字空间定义可以出现在程序多处，以向同一个名字空间中增加声明或定义

namespace Out::In
{
    int y;
}

// 匿名名字空间  用于构造仅翻译单元可见的对象
// 此时对全局域是可见的
// 可用 static 代替
// static int y;
namespace
{
    int y;
}

namespace MyNs
{
    // 此时匿名名字空间  也是用于构造仅翻译单元可见的对象
    // 如果去掉该匿名空间，则在其他翻译单元中可以被看到。
    namespace
    {
        int y;
    }
}

int main()
{
    // 嵌套名字空间
    // – 名字空间可以嵌套，嵌套名字空间形成嵌套域

    // – C++17 开始可以简化嵌套名字空间的定义
    Out::In::y;

    // 匿名名字空间
    // – 用于构造仅翻译单元可见的对象
    // – 可用 static 代替

    // 匿名名字空间的变量对全局域可见
    y = 3;

    // 匿名名字空间可作为嵌套名字空间
    MyNs::y = 4;
}