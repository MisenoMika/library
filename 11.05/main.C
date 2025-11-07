#include "Experiment.h"
#include "Computing.h"
#include <iostream>
#include <ctime>
using namespace std;
int main () {
    /*int *W, *D, weather, count=-1;
    W = new int[20]; D = new int[20];
    srand(time(NULL));
    while (count < 19) {
        cout << "Input the weather (1-5), -1 quit\n";
        cin >> weather;
        if (weather < 0 || weather > 5) break;
        count++; //add count of days
        W[count] = weather;
        D[count] = MakeDecision(W[count]);
    }   //end while
    cout << "Percent of Play = " << CompPlayPercentage(D, count) << "%\n";*/
    //srand(time(NULL));
    srand(static_cast<unsigned int>(time(NULL)));
    DoExperiment(1000);
    //delete [] W; delete [] D;记得删内存
    system("Pause");
    return 0;
}
