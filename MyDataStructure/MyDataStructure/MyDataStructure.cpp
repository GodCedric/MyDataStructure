#include<iostream>
#include"MyStack.h"
#include"MyQueue.h"
#include"MyList.h"
using namespace std;

int main(){

	//ջ
	MyStack<int> s(5);
	s.push(1);
	s.push(2);
	cout<<"ջ��"<<endl;
	cout<<"ջ�Ƿ�Ϊ�գ�"<<s.empty()<<endl;
	cout<<"����ջ����"<<s.pop()<<endl;
	cout<<"����ջ����"<<s.pop()<<endl;
	cout<<"ջ�Ƿ�Ϊ�գ�"<<s.empty()<<endl;
	cout<<endl;

	//����
	MyQueue<double> q(5);
	q.enqueue(2.5);
	q.enqueue(3.8);
	cout<<"���У�"<<endl;
	cout<<"�����Ƿ�Ϊ�գ�"<<q.empty()<<endl;
	cout<<"ɾ����ͷ��"<<q.dequeue()<<endl;
	cout<<"ɾ����ͷ��"<<q.dequeue()<<endl;
	cout<<"�����Ƿ�Ϊ�գ�"<<q.empty()<<endl;
	cout<<endl;
	
	//��������
	MyList<int> l;
	cout<<"��������"<<endl;
	l.insert(1);
	l.insert(2);
	l.insert(3);
	l.insert(3);
	l.insert(4);
	l.insert(5);
	cout<<"������룺 ";
	l.visit();
	l.deleteValue(3);
	cout<<"ɾ��ֵ����3�Ľ�㣺 ";
	l.visit();
	Node<int>* temp = l.find(2);
	cout<<"�ҵ�ֵΪ2�Ľ�㣬����ָ�룺 ";
	cout<<temp->data<<endl;
	cout<<"ɾ������2�������㣺 ";
	l.deleteNode(temp);
	l.visit();
	cout<<"������� ";
	l.clear();
	l.visit();

	return 0;
}