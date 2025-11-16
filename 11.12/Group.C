#include "Group.h"
#include <iostream>
#include <cstddef>
#include "Student.h"
using namespace std;

Group::Group(int StartingID, size_t initial):count(initial), StartingID(StartingID)
{
    students = new Student*[initial];
    decisions=new int[count];
    for(int i=0; i<initial; i++){
        students[i]=new Student(StartingID+i);
        decisions[i] = 1;  // 初始默认学生不参与
    }
}
Group::~Group(){
    for(size_t i=0; i<count; i++){
        delete students[i];//note: students[i]是单个Student对象，用delete[]释放
    }
    delete[] students;
    delete[] decisions;
}
void Group::GroupDecision(int weather){
    //cout<<"current groups "<<count<<endl;
    for (size_t i=0; i<count; i++){
        decisions[i]=students[i]->MakeDecision(weather);//代码中用Student::MakeDecision强制限定成员函数作用域,语法上虽合法，但冗余的作用域限定可能干扰编译器对this指针的解析（尤其在多继承或重载场景下），
    }//间接导致students[i]的this指针指向非法内存，触发段错误（参考摘要 5 “虚函数表破坏” 的类似内存访问风险）。by DOUBAO
}
void Group::Report() {
    int play = 0;
    for (size_t i = 0; i < count; i++) {  
        if (decisions[i] == 0) {
            play++;
        }
    }
    cout << "(Start ID: " << StartingID << "): " << count << " students, " << play << " play, " << (count - play) << " not play" << endl;
    // 输出参与学生的ID
    cout << "  ID to Play: ";
    for (size_t i = 0; i < count; i++) {  
        if (decisions[i] == 0) {
            cout << students[i]->getID() << " ";
        }
    }
    cout << endl;
}

Group* Group::Split(){
    if(count < 10) return nullptr;
    size_t split=count/2;
    size_t newcount=count-split;
    int newStartID= StartingID+count;
    Group*newgrp=new Group(StartingID, newcount);
    for(int i=0; i<newcount; i++){
        //newgrp->students[i];//切分出来的前面学号的组复制到新组
        students[i]=students[split+i];   
        newgrp->students[i];//=students[split+i];
    }

    count=split;//记得改原组的学生数量
    return newgrp;
}
