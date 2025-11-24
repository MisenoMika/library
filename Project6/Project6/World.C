#include <iostream>
#include <cstdlib>
#include "World.h"
using namespace std;

World::World(size_t c) {
    count = size = c;
    groups = new Group*[count];
    for (size_t i = 0; i < count; i++) {
        groups[i] = new Group(30*i, 30);
    }
    weather = new Weather();
}

void World::DoSimulation() {
    for (int j = 0; j < 30; j++) {
        weather->UpdateWeather();
        int wx = weather->GetWeather();
        int dice = rand()%5;
        if (dice == 0) HandleGroupSplit();
        else if (dice == 1) HandleGroupMerge();
        cout << "Day " << j+1<< ":\n";
        for (size_t i = 0; i < count; i++) {
            groups[i]->GroupDecision(wx);
            cout << "Groups " << i+1 << ": ";
            groups[i]->Report();
        }
    }
}

World::~World() {
    for (size_t i = 0; i < count; i++) {
        delete groups[i];
    }
    delete [] groups;
    delete weather;
}

void World::HandleGroupSplit() {
    int dice = rand() % count;
    Group* temp = groups[dice]->Split();
    if (temp == NULL) return;

    if (count == size) {
	size *= 2;
        Group** temp = new Group*[size];
	for (size_t i = 0; i < count; i++) temp[i] = groups[i];
	delete [] groups;
	groups = temp;
    }
    groups[count++] = temp;    
}

void World::HandleGroupMerge() {
    return;
    if (count <= 2) return;
    int first = rand() % count;
    int second = rand() % count;
    while(second == first) second = rand() % count;
    Group* firstGroup = groups[first];
    Group* secondGroup = groups[second];
    (*firstGroup) += (*secondGroup);
    groups[second] = groups[count-1];
    delete secondGroup;
    count--;
}

