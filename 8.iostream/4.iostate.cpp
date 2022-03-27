#include <iostream>
#include <fstream>

int main()
{
    // std::ofstream outFile;
    // outFile << 10; //异常状态badbit， 不可恢复的错误

    // int x;
    // std::cin >> x; // 如果键盘输入hell, 是failbit, 是可以恢复的错误

    // std::ofstream outFile2;
    // outFile2.close(); // failbit.

    // int x1;
    // //输入序列达到文件末尾。eofbit. 在输入框中不输入，只是按ctrl+d，则会触发该异常。
    // if(std::cin >> x1) // 其实本句话相当于static_cast<bool>(std::cin) 这也是获取输入的常用方式
    // {
    //     // ...如果输入了
    // }

    // std::cout << std::cin.good()
    //           << std::cin.fail()
    //           << std::cin.bad()
    //           << std::cin.eof()
    //           << static_cast<bool>(std::cin) << std::endl; // 输出为01010, cppreference 中有各种状态结果的组合


    // // 先输入一个a,按两次ctrl + d 退出
    // char x2;
    // std::cin >> x2;
    // std::cout << std::cin.fail() << " " << std::cin.eof() << std::endl; // 0,0
    // std::cin >> x2;
    // std::cout << std::cin.fail() << " " << std::cin.eof() << std::endl; // 1, 2

    // 输入8，按两次ctrl + d 退出
    int x3;
    std::cin >> x3;
    std::cout << std::cin.fail() << " " << std::cin.eof() << std::endl; // 0,1
    // 为什么这一次是01，而对于上面的char来说是00？因为，对于char来说，每次只需要读一个字符，
    // 对于char的例子，a的字符已经读完了，所以eof是false
    // 对于int的例子，因为需要读取很多位，以回车结束，但是在没有回车之前，就两次ctrl+d退出了，则eof为true

    // 设置流的状态为具体的值（缺省为 goodbit ）
    std::cin.clear();

    // setstate ：将某个状态附加到现有的流状态上
}