#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <cstring>
extern int* array;  // 应该改为：extern int array[]; 将array作为数组，叫做Unknown Bounded Array 声明


int main()
{
    // 数组与指针
    std::cout << "数组与指针" << std::endl;

    int a[3] = {1, 2, 3};
    auto b = a; // b的类型位int*,已经损失信息, std::begin(b)会报错
    auto& b2 = a;
    std::cout << a << ' ' << &a[0] << ' ' << std::begin(a) << ' ' << std::cbegin(a) << ' ' << std::begin(b2) << std::endl;  // begin 获得int*， cbegin 获得const int *
    std::cout << a + 3 << ' ' << &a[3] << ' ' << std::end(a) << ' ' << std::cend(a) << std::endl;

    auto ptr = a; // ptr 为int*
    ptr = ptr + 1;
    std::cout << *ptr << ' ' << ptr[1] <<  ' ' << 1[ptr] << std::endl; 
    auto ptr2 = a + 2;
    std::cout << (ptr < ptr2) << std::endl; //不要在不同数组之间比较，因为在内存中的位置不确定。
    std::cout << (ptr2 - ptr) << std::endl; 

    // 求数组元素个数
    std::cout << "求数组元素个数" << std::endl;
    std::cout << sizeof(a) / sizeof(int) << std::endl; // 不推荐，由于需要使用int,如果后面修改的数组的类型，则这种写法不便于维护
    std::cout << std::size(a) << std::endl;  // 推荐使用
    std::cout << std::cend(a) - std::cbegin(a) << std::endl; // 在运行期才能获得数组大小,不推荐

    // 数组遍历
    std::cout << "数据遍历" << std::endl;
    size_t index = 0;
    while (index < std::size(a))
    {
        std::cout << a[index] << std::endl;
        index++;
    }
    // 也可以使用for(auto x: a), cgbegin(), cend()

    // C字符串与数组
    std::cout << "C字符串与数组" << std::endl;
    char str[] = "hello"; // 字符串的本质是数组
    auto ptr3 = str; // char*
    // 如果char str[] = {'h', 'e','l','l','o'};,再使strlen,则有可能不会返回真实的数值，因为strlen需要找到'\n'结束
    // 建议char str[] = {'h', 'e','l','l','o','\n'};,那还不如直接用字符串
    std::cout << strlen(str) << std::endl;
    std::cout << strlen(ptr3) << std::endl;
}