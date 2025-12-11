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
    int size;
    
public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}
    
    ~Queue() {
        while (!empty()) {
            pop();
        }
    }
    
    // 入队
    void push(T val) {
        QueueNode<T>* newNode = new QueueNode<T>(val);
        if (empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    
    // 出队
    void pop() {
        if (empty()) {
            return;
        }
        QueueNode<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
        if (empty()) {
            tail = nullptr;
        }
    }
    
    // 获取队首元素
    T front() const {
        if (empty()) {
            throw "Queue is empty";
        }
        return head->data;
    }
    
    // 判断队列是否为空
    bool empty() const {
        return head == nullptr;
    }
    
    // 获取队列大小
    int getSize() const {
        return size;
    }
    
    // 清空队列
    void clear() {
        while (!empty()) {
            pop();
        }
    }
    
};

#endif