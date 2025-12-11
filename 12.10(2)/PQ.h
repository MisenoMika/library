#ifndef _PQ_H__
#define _PQ_H__
#include "PQnode.h"
#include "Queue.h"

template <class T>
class PQ{
    PQnode<T>* head;
    PQnode<T>* tail;
    Queue<PQnode<T>*> parentlist;
    int line;
public:
    PQ();
    ~PQ();
    void Push(T k);
    T pop();
    void shiftup(PQnode<T>* node);
    void shiftdown(PQnode<T>* node);
    void swap(PQnode<T>* node1, PQnode<T>* node2);
    bool isEmpty();
};
template <class T>
PQ<T>::PQ():head(nullptr), tail(nullptr),line(0){};

template <class T>
PQ<T>::~PQ(){
    Queue<PQnode<T>*> q;
    if (head != nullptr) {
        q.push(head);
    }

    while (!q.empty()) {
        PQnode<T>* tmp = q.front();
        q.pop();
        if (tmp->right != nullptr) q.push(tmp->right);
        if (tmp->left != nullptr) q.push(tmp->left);
        delete tmp; 
    }

    head = tail = nullptr;
    line = 0;
    while (!parentlist.empty()) parentlist.pop();

}
template <class T>
void PQ<T>:: Push(T k){
        line++;
        PQnode<T>* node = new PQnode<T>(k);
        if(isEmpty()){ 
            head = node;
            tail = node;
            parentlist.push(node);
            return;
        }
        PQnode<T>* parentnode = parentlist.front();
        if(parentnode->right == nullptr){
            parentnode->right = node;
        }
        else if(parentnode->left == nullptr){
            parentnode->left = node;
            parentlist.pop();  
        }
        node->parent = parentnode;
        parentlist.push(node);
        this->tail = node;
        shiftup(node);
        
    }


template <class T>
T PQ<T>::pop(){
    if(isEmpty()){
        throw "Out of bounds";
    }
    
    T minval = head->key;
    
    if(line == 1){
        delete head;
        head = tail = nullptr;
        while (!parentlist.empty()) parentlist.pop();
        line = 0;
        return minval;
    }
    
    PQnode<T>* lastnode = tail;
    swap(head, lastnode);
    PQnode<T>* lastParent = lastnode->parent;
    
    if (lastParent) {
        if (lastParent->right == lastnode) {
            lastParent->right = nullptr;
        } else if (lastParent->left == lastnode) {
            lastParent->left = nullptr;
        }
    }
    
    parentlist.push(lastnode->parent);
    delete lastnode;
    line--;
    
    //找到新的最后一个节点（从右向左层序遍历）
    if (head != nullptr) {
        Queue<PQnode<T>*> q;
        q.push(head);
        PQnode<T>* newTail = nullptr;
        
        while (!q.empty()) {
            newTail = q.front();
            q.pop();

            if (newTail->right != nullptr) q.push(newTail->right);
            if (newTail->left != nullptr) q.push(newTail->left);
        }
        
        tail = newTail;
    } 
    else {
        tail = nullptr;
    }

    if (head != nullptr) {
        shiftdown(head);
    }
    
    return minval;
}

template <class T>    
void PQ<T>::shiftup(PQnode<T>* node){
    if(isEmpty() || node == head){
        return;
    }
    //注意要判断parent是否为空，不能通过parent->key与node->key是否相等作为停止上浮的标准
    while(node->parent != nullptr && node->key < node->parent->key){
        swap(node, node->parent);
        node = node->parent; 
    }
}


template <class T>
void PQ<T>::shiftdown(PQnode<T>* node){
    if (node == nullptr) return;
    PQnode<T>* current = node;
    
    while (true) {
        PQnode<T>* left = current->left;
        PQnode<T>* right = current->right;
        PQnode<T>* smallest = current;
        if (right != nullptr && right->key < smallest->key) {
            smallest = right;
        }
        if (left != nullptr && left->key < smallest->key) {
            smallest = left;
        }
        if (smallest == current) {
            break;
        }
        
        swap(current, smallest);
        current = smallest;
    }
}


template <class T>
void PQ<T>::swap(PQnode<T>* node1, PQnode<T>* node2){
        T tmp = node1->key;
        node1->key = node2->key;
        node2->key = tmp;
    }


template <class T>
bool PQ<T>::isEmpty(){
        return head == nullptr;
    }


#endif