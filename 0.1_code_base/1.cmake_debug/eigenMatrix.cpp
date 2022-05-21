#include <iostream>
using namespace std;

/****************************
 * 可以直接在linux下运行，但是在windows上还需要调整。
0. 自行创建build文件夹
1.首先按ctrl+shift+B（或者状态栏中的build按钮，或者手动去cmake.. && make）， 进行build ,此时就会在build文件夹下有build好的可执行文件 。执行的操作在tasks.json中定义，且label必须为"build"，否则找不到build的任务。
2.按f5开始调试， 执行的操作在launch.json中定义，在调试前自动进行"preLaunchTask": "build"。
注：
- 在CMakeLists.txt文件中按ctrl+s时，vscode会自己build，但是有问题，需要此时需要删除build文件夹下的所有东西。
- 必须先手动build一次，才能按f5，后面就不tasks.json用再次手动build了，不知为什么。
- ctrl+shift+B 所寻找的build任务是tasks.json中label为"build"的任务。
- 调试，需要保证CMakeLists.txt中含有set( CMAKE_BUILD_TYPE "Debug" )，否则需要在cmake命令中添加"-DCMAKE_BUILD_TYPE=Debug"：
       {
          "label": "cmake",
          "command":"cmake",
          "args": ["-DCMAKE_BUILD_TYPE=Debug", ".."], // "-DCMAKE_BUILD_TYPE=Debug", 
       },
- 在windows中调试还是有些奇怪。
- 若在windows选择的是vs 编译，则似乎可以通过vs调试
- 选择的gcc 进行build，则可以直接按f5在vscode中调试？
https://blog.csdn.net/qq_30111427/article/details/122862758?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-0-122862758-blog-83097457.pc_relevant_default&spm=1001.2101.3001.4242.1&utm_relevant_index=3
****************************/

int main( int argc, char** argv )
{
    cout <<"hahahahahahahahaha" << endl;
    return 0;
}
