/*
 * test_for_FibHeap.cpp
 *
 *  Created on: 2017��1��6��
 *      Author: Cedric
 */
#include"MyFibHeap.h"

int main(){

	cout<<"����쳲�������1������ֵ��"<<endl;
	MyFibHeap<int>* MFH1 = new MyFibHeap<int>();
	MFH1->insert(1);
	MFH1->insert(2);
	MFH1->insert(3);
	MFH1->insert(4);
	cout<<"��1����ϸ��Ϣ"<<endl;
	MFH1->print();
	cout<<"����쳲�������2������ֵ��"<<endl;
	MyFibHeap<int>* MFH2 = new MyFibHeap<int>();
	MFH2->insert(5);
	MFH2->insert(6);
	MFH2->insert(7);
	MFH2->insert(8);
	cout<<"��2����ϸ��Ϣ"<<endl;
	MFH2->print();
	cout<<"��1���2�ϲ�Ϊ��3��"<<endl;
	MyFibHeap<int>* MFH3 = MyFibHeap<int>::heapunion(MFH1,MFH2);
	cout<<"��3����ϸ��Ϣ"<<endl;
	MFH3->print();
	int temp = MFH3->extractMin();
	cout<<"��ȡ��Сֵ��";
	cout<<temp<<endl;
	temp = MFH3->extractMin();
	cout<<"�ٳ�ȡ��Сֵ��";
	cout<<temp<<endl;
	cout<<"��ȡ��Сֵ���3����Ϣ"<<endl;
	MFH3->print();
	cout<<"���Ҽ�ֵ����7�Ľ�㣺";
	FibNode<int>* x = MFH3->findNode(7);
	if(x != NULL)
		cout<<x->key<<endl;
	else
		cout<<"û�������㣡"<<endl;
	cout<<"��7�������ֵ����1"<<endl;
	MFH3->decreaseKey(x,1);
	cout<<"�����ǰ����С��㣺";
	MFH3->printMin();
	cout<<"ɾ����ֵΪ6�Ľ��"<<endl;
	x = MFH3->findNode(6);
	MFH3->removeNode(x);
	cout<<"ɾ��֮��Ķѣ�"<<endl;
	MFH3->print();
	cout<<"�ͷŵ���3�Ľ���ڴ棺";
	MFH3->clearNode();

	return 0;
}
