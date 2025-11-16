#ifndef __GROUP_H__
#define __GROUP_H__
#include "Student.h"
class Group//Group中有每组的StartingID和学生数量
{
    Student** students;//行为学生数量，每行存储每个学生的指针
    size_t count;
    int* decisions;//一组所有学生的decisions
    int StartingID;
public:
    Group(int StartingID, size_t c);
    ~Group();
    void GroupDecision(int weather);
    void Report();
    Group* Split();
};
#endif