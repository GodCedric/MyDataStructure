#include<iostream>
#include"MyQueue.h"

using namespace std;

int main(){
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

	return 0;
}