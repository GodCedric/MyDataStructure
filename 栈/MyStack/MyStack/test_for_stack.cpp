#include<iostream>
#include"MyStack.h"

using namespace std;

int main(){
	MyStack<int> s(5);
	s.push(1);
	s.push(2);
	cout<<"ջ��"<<endl;
	cout<<"ջ�Ƿ�Ϊ�գ�"<<s.empty()<<endl;
	cout<<"����ջ����"<<s.pop()<<endl;
	cout<<"����ջ����"<<s.pop()<<endl;
	cout<<"ջ�Ƿ�Ϊ�գ�"<<s.empty()<<endl;
	cout<<endl;

	return 0;
}