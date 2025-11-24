#ifndef _STUDENTSVECTOR_H_
#define _STUDENTSVECTOR_H_
#include <cstddef>
#include "Student.h"
using namespace std;

class StudentsVector{
    Student** stds;
    size_t size;//最大容量
    size_t len;//实际容量
public:
    StudentsVector();
    ~StudentsVector();
    void Clear();
    void Push(Student*);
    Student*& operator[](size_t);
    int getlen();
    StudentsVector& operator=(StudentsVector& other);
    StudentsVector(const StudentsVector& other);
    //const Student*& operator[](size_t index) const;
};
#endif
