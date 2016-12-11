#include<iostream>
#include"MyStack.h"
#include"MyQueue.h"
using namespace std;

int main(){

	//栈
	MyStack<int> s(5);
	s.push(1);
	s.push(2);
	cout<<"栈"<<endl;
	cout<<"栈是否为空："<<s.empty()<<endl;
	cout<<"弹出栈顶："<<s.pop()<<endl;
	cout<<"弹出栈顶："<<s.pop()<<endl;
	cout<<"栈是否为空："<<s.empty()<<endl;

	//队列
	MyQueue<double> q(5);
	q.enqueue(2.5);
	q.enqueue(3.8);
	cout<<"队列"<<endl;
	cout<<"队列是否为空："<<q.empty()<<endl;
	cout<<"删除队头："<<q.dequeue()<<endl;
	cout<<"删除队头："<<q.dequeue()<<endl;
	cout<<"队列是否为空："<<q.empty()<<endl;
	
	
	return 0;
}