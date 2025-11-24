#include <iostream>
#include <cstdlib>
#include "World.h"
//#include 
using namespace std;

World::World(size_t c) {
    count = size = c;
    groups = new Group*[count];
    for (int i = 0; i < count; i++) {
        groups[i] = new Group(30*i, 30);
    }
    weather = new Weather();
}

World::~World() {
    if(groups == nullptr) return;
    for (int i = 0; i < count; i++) {
        delete groups[i];
    }
    delete [] groups;
    delete weather;
}


void World::DoSimulation() {
    for (int j = 0; j < 30; j++) {
        cout<<"=-=-=-=-=-=-=-=-=-=-=-=-=- DAY "<<j+1<<" =-=-=-=-=-=-=-=-=-=-=-=-="<<endl;
        weather->UpdateWeather();
        int w = weather->GetWeather();
        HandleGroupSplit();
        HandleGroupMerge();
        cout << "Day " << j+1<< ":\n";
        for (int i = 0; i < count; i++) {
            groups[i]->GroupDecision(w);
            cout << "Groups " << i+1 << ": ";
            //groups[i]->Report();
            cout<<*groups[i];
        }
    }
}

void World::HandleGroupSplit() {
    if (rand()%5 > 0) return;
    int dice = rand() % count;
    Group* temp = groups[dice]->Split();
    if (temp == nullptr) return;

    if (count == size) {
        size++;
        Group** temp = new Group*[size];
        for (size_t i = 0; i < count; i++) temp[i] = groups[i];
        delete [] groups;
        groups = temp;
    }

    groups[count++] = temp;
    std::cout << "[Split] Group " << dice + 1 << " split. "<<endl;//Total groups: " << count << "\n";
}

void World::HandleGroupMerge(){
    if (count <= 1) return; // 只有1个分组时不合并，避免无限循环
    int dice=rand()%5;
    if (dice == 0) {
        int dice1 = rand() % count;
        int dice2 = rand() % count;
        while(dice2 == dice1){
            dice2=rand()% count;
        }
        
        *groups[dice1] += *groups[dice2]; 
        delete groups[dice2];

        for (size_t i = dice2; i < count - 1; i++) {
            groups[i] = groups[i + 1]; // 后续组向前移位
        }

        count--;//别忘了组-1
        cout<<"[Merge] Group "<<dice1<<" and Group"<<dice2<<"has merged."<<endl;
    }
}