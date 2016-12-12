#include<iostream>
#include"MyStack.h"
#include"MyQueue.h"
#include"MyList.h"
using namespace std;

int main(){

	//栈
	MyStack<int> s(5);
	s.push(1);
	s.push(2);
	cout<<"栈："<<endl;
	cout<<"栈是否为空："<<s.empty()<<endl;
	cout<<"弹出栈顶："<<s.pop()<<endl;
	cout<<"弹出栈顶："<<s.pop()<<endl;
	cout<<"栈是否为空："<<s.empty()<<endl;
	cout<<endl;

	//队列
	MyQueue<double> q(5);
	q.enqueue(2.5);
	q.enqueue(3.8);
	cout<<"队列："<<endl;
	cout<<"队列是否为空："<<q.empty()<<endl;
	cout<<"删除队头："<<q.dequeue()<<endl;
	cout<<"删除队头："<<q.dequeue()<<endl;
	cout<<"队列是否为空："<<q.empty()<<endl;
	cout<<endl;
	
	//单向链表
	MyList<int> l;
	cout<<"单向链表："<<endl;
	l.insert(1);
	l.insert(2);
	l.insert(3);
	l.insert(3);
	l.insert(4);
	l.insert(5);
	cout<<"链表插入： ";
	l.visit();
	l.deleteValue(3);
	cout<<"删除值等于3的结点： ";
	l.visit();
	Node<int>* temp = l.find(2);
	cout<<"找到值为2的结点，返回指针： ";
	cout<<temp->data<<endl;
	cout<<"删除等于2的这个结点： ";
	l.deleteNode(temp);
	l.visit();
	cout<<"清空链表： ";
	l.clear();
	l.visit();

	return 0;
}