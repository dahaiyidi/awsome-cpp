#include <iostream>
#include <list>
#include <forward_list>

std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)
{
    for (auto &i : list) {
        ostr << " " << i;
    }
    return ostr;
}
int main()
{
    // splice 整段插入操作
    std::list<int> list1 = { 1, 2, 3, 4, 5 };
    list1.size();
    std::list<int> list2 = { 10, 20 };
 
    auto it = list1.begin();
    std::advance(it, 2);
    list1.splice(it, list2);
    std::cout << "list1: " << list1 << "\n";
    std::cout << "list2: " << list2 << "\n";
    list2.splice(list2.begin(), list1, it, list1.end());
    std::cout << "list1: " << list1 << "\n";
    std::cout << "list2: " << list2 << "\n";

    // forward_list 一个成本较低的线性表实现，不支持size()， pop_back / push_back
    // 


}