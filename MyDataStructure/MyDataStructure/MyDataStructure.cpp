#include<iostream>
#include"MyStack.h"
#include"MyQueue.h"
using namespace std;

int main(){

	//ջ
	MyStack<int> s(5);
	s.push(1);
	s.push(2);
	cout<<"ջ"<<endl;
	cout<<"ջ�Ƿ�Ϊ�գ�"<<s.empty()<<endl;
	cout<<"����ջ����"<<s.pop()<<endl;
	cout<<"����ջ����"<<s.pop()<<endl;
	cout<<"ջ�Ƿ�Ϊ�գ�"<<s.empty()<<endl;

	//����
	MyQueue<double> q(5);
	q.enqueue(2.5);
	q.enqueue(3.8);
	cout<<"����"<<endl;
	cout<<"�����Ƿ�Ϊ�գ�"<<q.empty()<<endl;
	cout<<"ɾ����ͷ��"<<q.dequeue()<<endl;
	cout<<"ɾ����ͷ��"<<q.dequeue()<<endl;
	cout<<"�����Ƿ�Ϊ�գ�"<<q.empty()<<endl;
	
	
	return 0;
}