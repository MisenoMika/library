#include "Group.h"
#include <iostream>
using namespace std;
Group::Group(int startid, size_t c) {
    count = c;
    StartingID = startid;
    decisions = new int[count]();
    playCount = 0;
    
    // 只有在c>0时才创建学生
    for (int i = 0; i < count; i++) {
        Student* student = new Student(startid + i);
        stdvector.Push(student);
    }
}


/*void Group::GroupDecision(int w) {
    int d = 0;
    playCount = 0;
    for (int i = 0; i < count; i++) {
        d = stdvector[i]->MakeDecision(w);
        if (d == 0) {
            decisions[playCount] = stdvector[i]->GetID();
            playCount++;
        }
    }
    return;
}*/
void Group::GroupDecision(int weather) {
    playCount = 0;
    size_t total = stdvector.getlen();// 确保decisions数组长度与学生数量一致(to aoid memory leak)
    
    if (decisions != nullptr) {
        delete[] decisions;
        decisions = nullptr;
    }
    decisions = new int[total]();
    for (size_t i = 0; i < stdvector.getlen(); i++) {
        decisions[i] = stdvector[i]->MakeDecision(weather);
        // 统计参与人数
        if (decisions[i] == 0) {
            playCount++;
        }
    }
}


/*void Group::Report() {
    cout << playCount << " play, " << count - playCount << " not play\n";
    cout << "    Play ID: ";
    for (int i = 0; i < playCount; i++) {
        cout << decisions[i] << " "; }
    cout << endl;
}*/
ostream& operator << (ostream& os, Group& group) {
    size_t total = group.stdvector.getlen();
    // 输出基础信息：初始ID、总人数、参与/不参与人数
    os << "Group (Start ID: " << group.StartingID << "): " 
       << total << " students, " 
       << group.playCount << " play, " 
       << (total - group.playCount) << " not play\n";

    // 输出参与学生ID
    os << "  Play IDs: ";
    for (size_t i = 0; i < total; i++) {
        if (group.decisions[i] == 0) {
            os << group.stdvector[i]->GetID() << " ";
        }
    }
    os << "\n";
    return os;
}


/*Group* Group::Split() {
    if (count < 10) return NULL;
    size_t lc = count/2;  size_t rc = count - lc;
    count = lc; 
    Group* temp = new Group(0, rc);
    for (int i = 0; i < rc; i++) {
        delete temp->stdvector[i];
        temp->stdvector[i] = stdvector[lc+i];
    }
    return temp;

}*/
Group* Group::Split() {
    size_t total = stdvector.getlen();
    if (total < 10) {
        return nullptr;
    }
    
    size_t leftLen = total / 2;
    size_t rightLen = total - leftLen;
    int newStartID = StartingID + leftLen;
    
    // 创建新组（但不自动创建学生）
    Group* newGroup = new Group(newStartID, 0); // 传入0，不自动创建学生
    
    // 清理新组的默认分配
    newGroup->stdvector.Clear();
    if (newGroup->decisions != nullptr) {
        delete[] newGroup->decisions;
    }
    
    // 分配新组的决策数组
    newGroup->decisions = new int[rightLen]();
    newGroup->count = rightLen;
    
    // 迁移右侧学生到新组
    StudentsVector rightStudents;
    for (size_t i = 0; i < rightLen; i++) {
        size_t srcIndex = leftLen + i;
        rightStudents.Push(stdvector[srcIndex]);
        newGroup->decisions[i] = this->decisions[srcIndex];
        stdvector[srcIndex] = nullptr; // 原组放弃所有权
    }
    
    // 更新原组
    // 创建左侧学生的临时vector
    StudentsVector leftStudents;
    int* leftDecisions = new int[leftLen]();
    
    for (size_t i = 0; i < leftLen; i++) {
        leftStudents.Push(stdvector[i]);
        leftDecisions[i] = this->decisions[i];
        stdvector[i] = nullptr; // 原vector放弃所有权
    }
    
    // 更新原组
    this->stdvector = leftStudents;
    delete[] this->decisions;
    this->decisions = leftDecisions;
    this->count = leftLen;
    
    // 设置新组的学生vector
    newGroup->stdvector = rightStudents;
    
    return newGroup;
}

Group::~Group() {
   if (decisions != nullptr) {
        delete[] decisions;
        decisions = nullptr; // 置空，防止后续误操作
    }
}



Group& Group::operator+=( Group&right){
    size_t leftcount=this->getstdcount();
    size_t rightcount=right.stdvector.getlen();
    size_t newcount= leftcount + rightcount;
    int* newdecisions= new int[newcount];
    //Group newgrp=(0, newcount);
    for(size_t i=0 ; i<leftcount; i++){
        newdecisions[i]=this->decisions[i];
    }
    
    // 补充右侧组的决策（长度rightcount）
    for (size_t i = 0; i < rightcount; i++) {
        newdecisions[leftcount + i] = right.decisions[i];
    }
    delete[] decisions;
    decisions = newdecisions;
    
    delete[] right.decisions;
    right.decisions = nullptr;
    right.count = 0;
    
    for(size_t i=0 ; i<rightcount; i++){
        stdvector.Push(right.stdvector[i]);
        right.stdvector[i] = nullptr;
    }
    //right.~Group(); 
    count= newcount;
    return *this;
}

int Group::getstdcount(){
    return stdvector.getlen();
}