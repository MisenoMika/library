#include "StudentVector.h"
#include "Student.h"
#include <iostream>
using namespace std;

StudentVector::StudentVector() {size = 10; len = 0; p = new Student*[size];}

void StudentVector::Clear() {
    for (size_t i = 0; i < len; i++) p[i] = NULL;
    len = 0;
}
StudentVector::~StudentVector() {delete [] p;}

void StudentVector::Push(Student* x) {
    if (len == size -1) {
        size *= 2;
        Student** temp = new Student*[size];
        for (size_t i = 0; i < len; i++) temp[i] = p[i];
        delete [] p;
        p = temp;
    }
    p[len++] = x;
}

Student*& StudentVector::operator[](int i) {
    return p[i];
}
