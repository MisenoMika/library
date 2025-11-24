#include <iostream>
#include <cstdlib>
#include <time.h>
#include "World.h"
using namespace std;

int main () {
    srand(time(NULL));
    World w(20);
    w.DoSimulation();
    return 0;
}
