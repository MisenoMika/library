#include "Group.h"
#include <iostream>
#include <cstddef>
using namespace std;

Group::Group(int s, size_t c) {
    count = c;
    decisions = new int[count];
    playCount = 0;
    for (size_t i = 0; i < count; i++) {
        students.Push( new Student(s+i) );
    }
}
void Group::GroupDecision(int w) {
    int d = 0;
    playCount = 0;
    for (size_t i = 0; i < count; i++) {
        d = students[i]->MakeDecision(w);
        if (d == 0) {
            decisions[playCount] = students[i]->GetID();
            playCount++;
        }
    }
    return;
}

void Group::Report() {
    cout << playCount << " play, " << count - playCount << " not play\n";
    cout << "    Play ID: ";
    for (size_t i = 0; i < playCount; i++) {
        cout << decisions[i] << " ";
    }
    cout << endl;
}
Group* Group::Split() {
    if (count < 10) return NULL;
    size_t lc = count/2;
    size_t rc = count - lc;
    count = lc;
    students.SetLen(lc);
    Group* temp = new Group(0, rc);
    for (size_t i = 0; i < rc; i++) delete temp->students[i];
    temp->students.Clear();
    for (size_t i = 0; i < rc; i++) {
	temp->students.Push(students[lc+i]);
    }

    return temp;
}

Group::~Group() {
    for (size_t i = 0; i < count; i++) {
        if (students[i] != NULL) delete students[i];
    }
    delete [] decisions;
}

Group& Group::operator+=(Group& right) {
    for (size_t i = 0; i < right.count; i++) {
        this->students.Push(right.students[i]);
    }
    right.students.Clear();
    this->count += right.count;
    right.count = 0;
    delete [] decisions; //delete old this->decision
    decisions = new int[count]; //create new this->decision
    return *this;
}
