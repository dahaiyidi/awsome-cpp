#include <iostream>
#include <fstream>

int main()
{

    // // 输入流
    // std::ifstream inFile("my_file");
    // std::string x;
    // inFile >> x;
    // std::cout << x << std::endl;

    // 常用：用{}控制outFile什么时候可以销毁
    {
        std::ofstream outFile("my_file");
        // 也可以std::ofstream outFile;
        // outFile.open("my_file");
        outFile << "Hell\n";
    }

    std::ofstream outFile2("my_file2", std::ios_base::out | std::ios_base::trunc); // 写入；截断文件即删除文件中的内容
    // std::ios_base::out | std::ios_base::trunc 与只用std::ios_base::out 甚至两者都不写，含义是一致的。
    outFile2 << "he\n";
    std::ios_base::in | std::ios_base::ate; // 读取；起始位置位于文件末尾

    // 所有模式 in,out, ate,app,trunc, binary及常见的组合可以查看资料。
}