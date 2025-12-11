#include "PQ.h"
#include <iostream>
#include <ctime>
//#include <cstdlib>
//我的二叉树是从右向左增加节点的，检查的时候需十分注意这一点
int main() {
    srand(static_cast<unsigned int>(time(0)));

    std::cout << "Testing PQ<int>:\n";
    PQ<int> pqInt;
    for (int i = 0; i < 1000; i++) {
        pqInt.Push(rand()); 
    }
    while (!pqInt.isEmpty()) {
        std::cout << pqInt.pop() << " ";
    }
    std::cout << "\n\n";

    std::cout << "Testing PQ<double>:\n";
    PQ<double> pqDouble;
    for (int i = 0; i < 1000; i++) {
        double val = rand()+ rand() / static_cast<double>(RAND_MAX);
        pqDouble.Push(val);
    }
    while (!pqDouble.isEmpty()) {
        std::cout << pqDouble.pop() << " ";
    }
    std::cout << "\n";
    system("Pause");
    return 0;
}