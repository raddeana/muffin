#### C++ 模板 与 泛型编程
泛型编程这种编程方法，主要使用于：容器、迭代器、算法
比如C++著名的标准模板库中都是使用模板和泛型编程

```cpp
#include<iostream>
#include <iomanip>

using namespace std;

class Queue {
  struct Node{
    int a;
    Node * next;
  };
public:
  Queue();
  ~Queue();
  void push(int b);
  void pop();
  int getlength();
  virtual void print();

private:
  Node * head;
  Node * rear;
  int num;
};

void Queue::push(int b){
  Node *pl = new Node;
  pl->a = b;
  pl->next = NULL;
  rear->next = pl;
  rear = pl;
  num++;
  cout << setw(2) << b << setw(2) << " 进入队列 " << endl;
}

void Queue::pop(){
  Node *p;
  p = head->next;
  cout << "  " << setw(2) << p->a << setw(2) << " 出队 " << endl;
  head->next = p->next;
  delete p;
  num--;
}

int Queue::getlength(){
  return num;
}

void Queue::print(){
  Node *p;
  p = head->next;
  cout << "队列中的元素是：" << endl;
  while(p){
    cout << p->a << " -> ";
    p = p->next;
  }
  cout << "NULL" << endl;
}

Queue::Queue(){
  rear = head = new Node();
}

Queue::~Queue(){
  delete head;
}
```

#### main.cpp
```cpp
#include <iostream>
#include "queue.h"

using namespace std;

int main(){
  Queue q;
  q.push(10);
  q.push(20);
  q.push(30);
  q.print();

  system("pause");
  return 0;
}
```

#### queue.h
```cpp
#include<iostream>
#include <iomanip>

using namespace std;

template<class T>
class Queue {
  struct Node{
    T a;
    Node * next;
  };
public:
  Queue();
  ~Queue();
  void push(T b);
  void pop();
  int getlength();
  virtual void print();

private:
  Node * head;
  Node * rear;
  int num;
};

template<class T>
void Queue<T>::push(T b){
  Node *pl = new Node;
  pl->a = b;
  pl->next = NULL;
  rear->next = pl;
  rear = pl;
  num++;
  cout << setw(2) << b << setw(2) << " 进入队列 " << endl;
}

template<class T>
void Queue<T>::pop(){
  Node *p;
  p = head->next;
  cout << "  " << setw(2) << p->a << setw(2) << " 出队 " << endl;
  head->next = p->next;
  delete p;
  num--;
}

template<class T>
int Queue<T>::getlength(){
  return num;
}

template<class T>
void Queue<T>::print(){
  Node *p;
  p = head->next;
  cout << "队列中的元素是：" << endl;
  while(p){
    cout << p->a << " -> ";
    p = p->next;
  }
  cout << "NULL" << endl;
}

template<class T>
Queue<T>::Queue(){
  rear = head = new Node();
}

template<class T>
Queue<T>::~Queue(){
  delete head;
}
```

```cpp
#include <iostream>
#include "queue.h"

using namespace std;

int main () {
  Queue<int> q;
  q.push(10);
  q.push(20);
  q.push(30);
  q.print();

  Queue<string> qs;
  qs.push("www");
  qs.push("aobosir");
  qs.push("com");
  qs.print();

  qs.pop();
  qs.print();

  system("pause");
  return 0;
}
```

