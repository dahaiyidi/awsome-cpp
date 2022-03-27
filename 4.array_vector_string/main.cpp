#include <iostream>
#include <type_traits>
#include <typeinfo>
extern int* array;  // 应该改为：extern int array[]; 将array作为数组，叫做Unknown Bounded Array 声明
// extern int array[]; 但是已经失去了数组大小的信息，std::begin(array) 会报错。因此可以修改为extern int array[3];

void fun();

int main()
{
    fun(); // 0x60105c
    // 在fun中可以打印出正常array 第一个元素
    // 1 十六进制-> 00 00 00 01  实际保存-> 01 00 00 00，  4个字节
    // 2 十六进制-> 00 00 00 02  实际保存-> 02 00 00 00，  4个字节
    // 数组中存储 01 00 00 00 02 00 00 00
    // 本文件中将array看成一个指针，在64位机中，指针是8Byte, 因此，会从内存中拿出地址01 00 00 00 02 00 00 00
    // 因此cout输出00 00 00 02 00 00 00 01
    std::cout << array << std::endl;  // 0x200000001

}
// 输入 g++ -g -Wall -std=c++11 main.cpp -o main && ./main | c++filt -t， 就会获得std::initializer_list<int>