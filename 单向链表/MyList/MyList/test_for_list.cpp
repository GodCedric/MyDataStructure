#include<iostream>
#include"MyList.h"

using namespace std;

int main(){
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