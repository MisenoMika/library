#ifndef _STUDENT_H
#define _STUDENT_H
#include "Decision.h"
#include <cstddef>
class Student
{
    int ID;//学生id
   Decision* decision;//学生想玩的倾向（为什么要写成decision）
public:
    Student(int k);
    ~Student();
    int MakeDecision(int weather);
    int getID();
    
};

#endif