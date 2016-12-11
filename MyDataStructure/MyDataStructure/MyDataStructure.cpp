#include<iostream>
#include"MyStack.h"
using namespace std;

int main(){

	//Õ»
	MyStack<int> s(5);
	s.push(1);
	s.push(2);
	cout<<"Õ»"<<endl;
	cout<<"Õ»ÊÇ·ñÎª¿Õ£º"<<s.empty()<<endl;
	cout<<"µ¯³öÕ»¶¥£º"<<s.pop()<<endl;
	cout<<"µ¯³öÕ»¶¥£º"<<s.pop()<<endl;
	cout<<"Õ»ÊÇ·ñÎª¿Õ£º"<<s.empty()<<endl;

	return 0;
}