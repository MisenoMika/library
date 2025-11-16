#include "World.h"
#include <ctime>
#include <iostream>
#include <cstddef>
using namespace std;
int main(){
    srand(time(NULL));
    //srand(static_cast<unsigned int>(time(NULL)));
    World initial(20);
    initial.DoSimulation();
    system("Pause");
    return 0;
}