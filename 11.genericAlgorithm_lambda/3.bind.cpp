#include <iostream>
#include <vector>
#include <functional>
#include <memory>

bool MyPredict(int val)
{
    return val > 3;
}
bool MyPredict2(int val1, int val2)
{
    return val1 > val2;
}
bool MyAnd(bool val1, bool val2)
{
    return val1 && val2;
}
void MyProc(std::shared_ptr<int> ptr)
{

}
auto fun()
{
    std::shared_ptr<int> x(new int());// 如果不是std::shared_ptr则会出错，因为如果使用局部变量的地址，则退出函数时，指针则指向了无效的内存
    return std::bind(MyProc, x); 
}
void fun2(int& x)
{
    ++x;
}
int main()
{
    using namespace std::placeholders;
    std::vector<int> x {1, 2, 3, 4, 5, 6};
    std::vector<int> y;
    // bind1st, bind2nd 功能受限
    // std::copy_if(x.begin(), x.end(), std::back_inserter(y), MyPredict); // 4 5 6 
    // std::copy_if(x.begin(), x.end(), std::back_inserter(y), std::bind2nd(std::greater<int>(), 3));  // std::bind2nd，第二个参数固定为3 // 4 5 6 
    // std::copy_if(x.begin(), x.end(), std::back_inserter(y), std::bind1st(std::greater<int>(), 3));  // std::bind2nd，第1个参数固定为3 // 12
    // 可以使用std::bind, std::bin
    std::copy_if(x.begin(), x.end(), std::back_inserter(y), std::bind(MyPredict2, _1, 3));  // std::bind2nd，第1个参数固定为3 // 12

    for (auto p : y)
    {
        std::cout << p << ' ';
    }
    std::cout << std::endl;

    // bind 通过绑定的方式修改可调用对象的调用方式
    auto x1 = std::bind(MyPredict2, _1, 3); // std::placeholders_1代表调用x时的第一个参数，即50，相当于MyPredict2(50, 3)
    std::cout << x1(50) << std::endl;;
    auto x2 = std::bind(MyPredict2, 3, _1); // 调用x时的第一个参数50放置到_1位置，相当于MyPredict2(3, 50), 
    std::cout << x2(50) << std::endl;
    auto x4 = std::bind(MyPredict2, _3, _2); 
    std::cout << x4("hello", 2, 3) << std::endl;// 相当于MyPredict2(3, 2) 
    
    auto x8 = std::bind(MyPredict2, _2, _2); 
    std::cout << "一个元素使用多次:" << x8("hello", 2, 3) << std::endl;// 0, 相当于MyPredict2(3, 2) 

    auto x5 = std::bind(MyPredict2, _1, 3);
    auto x6 = std::bind(MyPredict2, 10, _1);
    auto x7 = std::bind(MyAnd, x5, x6);  // 可以进行组合
    std::cout << "bind组合:" << x7(5) << std::endl; // 5 会放置到x5中的_1和x6中的_1位置，完成的效果时判断输入的元素是否介于3和10之间

    // 调用 std::bind 时，传入的参数会被复制，这可能会产生一些调用风险
    auto ptr = fun();
    int x9 = 0;
    auto b = std::bind(fun2, x9);
    // 可以这样
    // auto b = std::bind(fun2, std::ref(x9)); 这样调用b之后，x9就会变为1
    b();
    std::cout << x9 << std::endl; // 还是0，因为是拷贝，而无法传x8引用
    
    // std::bind_front 
    auto y1 = std::bind_front(MyPredict2, 3);  // 直接从MyPredict2前面开始绑定
    std::cout << y1(2) << std::endl;

    // bind 的使用形式比较复杂

}