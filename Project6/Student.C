#include "Student.h"
#include <cstdlib>

Student::Student(int x) : ID (x) {
    decision = new Decision(rand()%100/100.0);
}

int Student::MakeDecision(int w) {
    return decision->MakeDecision(w);
}

Student::~Student() {
    delete decision;
}

int Student::GetID() {return ID;}
