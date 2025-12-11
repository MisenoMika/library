#ifndef __PQNODE_C__
#define __PQNODE_C__

template <class U>
class PQnode{
    U key;
    PQnode* right;
    PQnode* left;
    PQnode* parent;
    //PQnode* next;
public:
    PQnode(U k):key(k), right(nullptr), left(nullptr), parent(nullptr){};
    template <class T> friend class PQ;
};
#endif