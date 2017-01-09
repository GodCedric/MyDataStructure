/*
 * test_for_FibHeap.cpp
 *
 *  Created on: 2017年1月6日
 *      Author: Cedric
 */
#include"MyFibHeap.h"

int main(){

	cout<<"创建斐波那契堆1并插入值："<<endl;
	MyFibHeap<int>* MFH1 = new MyFibHeap<int>();
	MFH1->insert(1);
	MFH1->insert(2);
	MFH1->insert(3);
	MFH1->insert(4);
	cout<<"堆1的详细信息"<<endl;
	MFH1->print();
	cout<<"创建斐波那契堆2并插入值："<<endl;
	MyFibHeap<int>* MFH2 = new MyFibHeap<int>();
	MFH2->insert(5);
	MFH2->insert(6);
	MFH2->insert(7);
	MFH2->insert(8);
	cout<<"堆2的详细信息"<<endl;
	MFH2->print();
	cout<<"堆1与堆2合并为堆3："<<endl;
	MyFibHeap<int>* MFH3 = MyFibHeap<int>::heapunion(MFH1,MFH2);
	cout<<"堆3的详细信息"<<endl;
	MFH3->print();
	int temp = MFH3->extractMin();
	cout<<"抽取最小值：";
	cout<<temp<<endl;
	temp = MFH3->extractMin();
	cout<<"再抽取最小值：";
	cout<<temp<<endl;
	cout<<"抽取最小值后堆3的信息"<<endl;
	MFH3->print();
	cout<<"查找键值等于7的结点：";
	FibNode<int>* x = MFH3->findNode(7);
	if(x != NULL)
		cout<<x->key<<endl;
	else
		cout<<"没有这个结点！"<<endl;
	cout<<"将7这个结点键值减到1"<<endl;
	MFH3->decreaseKey(x,1);
	cout<<"输出当前堆最小结点：";
	MFH3->printMin();
	cout<<"删掉键值为6的结点"<<endl;
	x = MFH3->findNode(6);
	MFH3->removeNode(x);
	cout<<"删除之后的堆："<<endl;
	MFH3->print();
	cout<<"释放掉堆3的结点内存：";
	MFH3->clearNode();

	return 0;
}
