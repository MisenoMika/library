#ifndef _STUDENT_H_
#define _STUDENT_H_
#include "Decision.h"

class Student{
    int ID;
    Decision* decision;
public:
    Student(int x);
    int MakeDecision(int w);
    int GetID();
    ~Student();
};
#endif
