#ifndef _STUDENT_VECTOR_H_
#define _STUDENT_VECTOR_H_
#include "Student.h"
#include <cstddef>
using namespace std;

class StudentVector{
    Student** p;
    size_t size;
    size_t len;
public:
    StudentVector();
    ~StudentVector();
    void Clear();
    void Push(Student*);
    size_t GetLen() {return len;}
    void SetLen(size_t l) {len = l;}
    Student*& operator[] (int i);
};
#endif

