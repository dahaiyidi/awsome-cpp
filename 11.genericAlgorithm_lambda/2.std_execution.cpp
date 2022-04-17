#include <iostream>
#include <vector>
#include <random>
#include <ratio>
#include <execution>
#include <algorithm>
#include <chrono>

int main()
{
    std::random_device rd;
    std::vector<double> vals(1000000);
    for (auto& d: vals)
    {
        d = static_cast<double> (rd());
    }

    for(int i = 0; i < 5; ++i)
    {
        using namespace std::chrono;
        std::vector<double> sorted(vals);
        const auto startTime = high_resolution_clock::now();
        std::sort(sorted.begin(), sorted.end());
        // std::sort(std::execution::unseq, sorted.begin(), sorted.end()); //速度等上
        //  g++ -Wall -O3 --std=c++2a main.cpp -o main && ./main 需要加上-O3，速度会提高，也有可能需要在连接时加入-ltbb
        // std::sort(std::execution::par, sorted.begin(), sorted.end()); 
        // 但是经过实验证明，g++加上-O3之后，三者的速度差不多。不加也差不多。
        const auto endTime = high_resolution_clock::now();
        std::cout << "Latency: " << duration_cast<duration<double, std::milli>>(endTime - startTime).count() << std::endl;
    }

}