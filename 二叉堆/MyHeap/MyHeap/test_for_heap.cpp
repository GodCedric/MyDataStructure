#include<iostream>
#include"MyMaxHeap.h"
#include"MyMinHeap.h"

using namespace std;

int main(){
	cout<<"���ѣ�"<<endl;
	MyMaxHeap<int> maxhp(30); 
	maxhp.insert(5);
	maxhp.insert(1);
	maxhp.insert(26);
	maxhp.insert(13);
	maxhp.insert(6);
	maxhp.insert(8);
	maxhp.insert(-5);
	maxhp.insert(100);
	maxhp.insert(-25);
	maxhp.insert(-34);
	cout<<"����Ԫ�غ�Ķ�Ϊ��"<<endl;
	maxhp.print();
	maxhp.remove(6);
	cout<<"ɾ��Ԫ��6��Ķ�Ϊ��"<<endl;
	maxhp.print();
	cout<<endl;

	cout<<"��С�ѣ�"<<endl;
	MyMinHeap<int> minhp(30);
	minhp.insert(5);
	minhp.insert(1);
	minhp.insert(26);
	minhp.insert(13);
	minhp.insert(6);
	minhp.insert(8);
	minhp.insert(-5);
	minhp.insert(100);
	minhp.insert(-25);
	minhp.insert(-34);
	cout<<"����Ԫ�غ�Ķ�Ϊ��"<<endl;
	minhp.print();
	minhp.remove(6);
	cout<<"ɾ��Ԫ��6��Ķ�Ϊ��"<<endl;
	minhp.print();
	cout<<endl;


	return 0;
}