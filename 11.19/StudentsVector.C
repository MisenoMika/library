#include "StudentsVector.h"
#include "Student.h"
#include "Group.h"
StudentsVector::StudentsVector():size(20), len(0)
{
    stds = new Student*[size];
}

StudentsVector::~StudentsVector(){
    for (size_t i = 0; i < len; i++) {
        if (stds[i] != nullptr) {
            delete stds[i];
        }
    }
    delete[] stds;
}

void StudentsVector::Push(Student* student){
    if(len >= size) size*=2;
    
    Student** newStds = new Student*[size];
    for (size_t i = 0; i < len; i++) {//构造新的vector来容纳更多学生
            newStds[i] = stds[i];
    }
    delete[] stds; 
    stds = newStds; 
    stds[len++]=student;
} 

void StudentsVector::Clear() {
    for(size_t i = 0; i<len; i++){
        delete stds[i]; // 释放学生对象
        stds[i] = nullptr;
    }
    len = 0; // 重置实际长度
}

Student*& StudentsVector::operator[](size_t val){
    if(val >= len){
        throw "error";
    }
    return stds[val];
}

int StudentsVector::getlen(){
    return len;
}

StudentsVector& StudentsVector::operator=(StudentsVector& right) {
    if (this == &right) return *this;

    // 释放当前资源
    for (size_t i = 0; i < len; i++) {
        delete stds[i]; // 深拷贝：删除旧对象
    }
    delete[] stds;

    // 深拷贝右对象
    this->size = right.size;
    this->len = right.len;
    this->stds = new Student*[size];

    for (size_t i = 0; i < len; i++) {
        if (right.stds[i] != nullptr) {
            this->stds[i] = new Student(*(right.stds[i])); // 深拷贝学生
        } else {
            this->stds[i] = nullptr;
        }
    }
    return *this;
}

StudentsVector::StudentsVector(const StudentsVector& other) {
    size = other.size;
    len = other.len;
    stds = new Student*[size];
    
    for (size_t i = 0; i < len; i++) {
        if (other.stds[i] != nullptr) {
            stds[i] = new Student(*(other.stds[i])); // 深拷贝
        } else {
            stds[i] = nullptr;
        }
    }
}