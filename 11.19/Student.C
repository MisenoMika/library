#include "Student.h"
#include <cstdlib>

Student::Student(int x) : ID (x) {
    decision = new Decision(0.1+rand()%90/100.0);
}

int Student::MakeDecision(int w) {
    if(decision != nullptr)return decision->MakeDecision(w);
    else return NULL;
}

Student::~Student() {
    if (decision != nullptr) {
        delete decision;
        decision = nullptr; // 置空，防止后续误操作
    }
}

int Student::GetID() {
    return ID;
}
Student::Student(const Student& other) {
    this->ID = other.ID;
    if (other.decision != nullptr) {
        this->decision = new Decision(*(other.decision));
    } 
    else {
        this->decision = new Decision(0.5); // 或根据业务逻辑初始化
    }
}