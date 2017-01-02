#ifndef __MYLIST__H__
#define __MYLIST__H__
#include<iostream>

template<class T>
struct Node{
	T data;
	struct Node* next;
	Node(T x):data(x),next(NULL){};
};

template<class T>
class MyList{
public:
	MyList(){
		Head = NULL;
	}
	~MyList(){
		delete Head;
	}
	void insert(T data);//在头结点插入节点
	void deleteValue(T val);//删除data等于val的结点
	void visit();//遍历链表
	Node<T>* find(T x);//查找第一个等于x的结点
	void deleteNode(Node<T>* p);//删除某个结点
	void clear();//清空链表
private:
	Node<T>* Head;
};

template<class T>
void MyList<T>::insert(T data){
	Node<T>* p = new Node<T>(data);
	p->next = Head;
	Head = p;
}

template<class T>
void MyList<T>::deleteValue(T val){
	Node<T>** pp = &Head;
	for(pp;*pp;pp=&(*pp)->next){
		if((*pp)->data == val){
			Node<T>* temp = (*pp)->next;
			(*pp) = temp->next;
			delete temp;
		}
	}
}

template<class T>
void MyList<T>::visit(){
	Node<T>* p = Head;
	while(p){
		cout<<p->data<<"  ";
		p = p->next;
	}
	cout<<endl;
}

template<class T>
Node<T>* MyList<T>::find(T x){
	Node<T>* p = Head;
	while(p && p->data != x){
		p = p->next;
	}
	return p;
}

template<class T>
void MyList<T>::deleteNode(Node<T>* p){
	Node<T>** pp = &Head;
	for(pp;*pp;pp=&(*pp)->next){
		if((*pp) == p){
			(*pp) = p->next;
			delete p;
		}
	}
}

template<class T>
void MyList<T>::clear(){
	Node<T>* p;
	for(Head;Head;){
		p = Head->next;
		delete Head;
		Head = p;
	}
	cout<<"链表已清空"<<endl;
}

#endif