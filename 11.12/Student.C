#include <iostream>
#include "Student.h"
#include "Group.h"
using namespace std;

Student::Student(int k):ID(k)
{
    double dice=(rand()%90+1)/100.0;
    decision=new Decision(dice);
}
Student::~Student() {
    delete decision;
}
int Student::MakeDecision(int weather){
    return decision->Decision::MakeDecision(weather);

}
int Student::getID(){
    return ID;
}