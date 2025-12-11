#ifndef __QUEUE_H__
#define __QUEUE_H__
//用一个链表管理可以生child的parent节点
template <class T>
class QueueNode {
public:
    T data;
    QueueNode<T>* next;
    
    QueueNode(T val) : data(val), next(nullptr) {}
};

template <class T>
class Queue {
private:
    QueueNode<T>* head;
    QueueNode<T>* tail;
   
    
public:
    Queue() : head(nullptr), tail(nullptr) {}
    
    ~Queue() {
        while (!empty()) {
            pop();
        }
    }
    
 
    void push(T val) {
        QueueNode<T>* newNode = new QueueNode<T>(val);
        if (empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
  
    }
    
  
    void pop() {
        if (empty()) {
            return;
        }
        QueueNode<T>* temp = head;
        head = head->next;
        delete temp;
   
        if (empty()) {
            tail = nullptr;
        }
    }
    
  
    T front() const {
        if (empty()) {
            throw "Queue is empty";
        }
        return head->data;
    }
    
  
    bool empty() const {
        return head == nullptr;
    }
    
};

#endif