#include<iostream>
#include"MyList.h"

using namespace std;

int main(){
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