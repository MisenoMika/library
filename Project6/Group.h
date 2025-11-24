#ifndef _GROUP_H_
#define _GROUP_H_
#include "Student.h"
#include "StudentVector.h"
#include <cstddef>
using namespace std;
class Group {
    StudentVector students;
    size_t count;
    int* decisions;
    size_t playCount;
public:
    Group(int s, size_t c);
    void GroupDecision(int w);
    void Report();
    Group* Split();
    ~Group();    
    Group& operator+=(Group& right);
};
#endif
