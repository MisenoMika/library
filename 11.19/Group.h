#ifndef _GROUP_H_
#define _GROUP_H_
#include "Student.h"
#include "StudentsVector.h"
#include <cstddef>
#include <iostream>
using namespace std;
class Group {
    StudentsVector stdvector;
    size_t count;
    int* decisions;
    size_t playCount;
    int StartingID;
public:
    Group(int s, size_t c);
    void GroupDecision(int w);
    //void Report();
    Group* Split();
    ~Group();
    //Group* Merge();
    Group& operator+=(Group& right); 
    //Group& operator[](const Group& right);
    int getstdcount();
    friend std::ostream& operator<<(std::ostream& os, Group& group);
};
#endif
