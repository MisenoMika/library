#include "World.h"
#include "Weather.h"
#include "Group.h"
#include <cstdlib>
using namespace std;
World::World(size_t initial): count(initial){//count是指小组数量
    w =new Weather();
    group=new Group*[count];
    for(int i=0; i<count; i++){
        int StartID=1+i*30;
        group[i]=new Group(StartID, 30);
    }
}
  

World::~World(){
    for(int i=0; i<count; i++){
        delete group[i];
    }
    delete[] group;
    delete w;
}

void World::DoSimulation(){
for(int day=1; day<=30; day++){
        cout<<"=-=-=-=-=--=-=--=-=-=-=-=-=-=DAY "<<day<<"-=-=-=-=-=-=-=-=-=-=-"<<endl;
        if(day==15)cout<<"It is so hard that it costs me hours:("<<endl;
        if (rand() % 100 <= 40 && count > 0) {
            size_t randgrp = rand() % count; // 随机选组
            Group* newGrp = group[randgrp]->Split();
            if (newGrp != nullptr) {
                Group** tempGroups = new Group*[count + 1];//存放总组数的指针扩容
                for (size_t i = 0; i < count; i++) {
                    tempGroups[i] = group[i];
                }
                tempGroups[count] = newGrp; // 加入新组
                delete[] group;
                group = tempGroups;
                count++; // 更新组数量（+1）
                cout << "  [Split] Group " << randgrp + 1 << " split. Total groups: " << count << endl;
            }
        }
        w->updateWeather();
        int todayw=w->getWeather();
        cout<<"Today's Weather: "<<todayw<<endl;
        for(size_t i=0; i<count; i++){
            group[i]->GroupDecision(todayw);
            cout<<"Group "<<i<<endl;
            group[i]->Report();
        }
    cout<<endl;
    }

}