#include <iostream>
#include <string>
#include <string_view>
#include <span>
#include <vector>
#include <stack>
#include <queue>
#include <list>

void fun(std::string_view str)
{
    // 类型适配器，既可以接受c字符串，也可以接收std::string
    // 非常便宜，只包含了开始和结束位置，因此传递的时候也不需要传引用。
    // 但是不能写操作，只能view
    std::cout << sizeof(std::string_view) << std::endl; 
    if(!str.empty())
    {
        std::cout << str[0] << std::endl;
    }
}

std::string_view fun2(std::string_view input)
{
    // 尽量不要将std::string_view作为返回值，因为指向的对象可能被销毁。除非有把握。
    return input.substr(0, 2);
}

void fun3(std::span<int> input)
{
    // 轻量级，只包含两个指针，指向了input的第一个元素和input最后一个元素的下一个位置
    // 可读写。
    input[0] = 8;
    for(auto p: input)
    {
        std::cout << p << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    // 类型适配器
    // std::string_view from c++17
    fun("123");
    std::string s("123");
    fun(s);
    fun(std::string_view(s.begin(), s.begin() + 2));  // 只包含两位字符

    std::cout << "std::string_view作为返回值" << std::endl;
    auto res = fun2(s); // 但是auto res = fun2(std::string("123")); 是不合法的，因为临时对象在这句代码后会被销毁 
    std::cout << res << std::endl;

    // span from c++20
    std::cout << "std::span" << std::endl;
    int a[3] = {1, 2, 3};
    std::vector<int> a2{1, 2,3};
    fun3(a);
    fun3(a2);

    // 接口适配器
    // stack / queue / priority_queue
    // stack 缺省由std::deque实现， 可以修改
    std::stack<int, std::vector<int>> p; // p 底层由std::vector 实现，也可以为std::list
    p.push(3);
    p.top();

    // queue 缺省由std::deque实现， 可以修改为std::list, vector
    std::queue<int, std::list<int>> p2; // p 底层由std::vector 实现
    p2.push(3);

    // priority_queue
    
}