#include<iostream>
#include"MyQueue.h"

using namespace std;

int main(){
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

	return 0;
}