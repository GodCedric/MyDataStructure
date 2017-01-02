#include<iostream>
#include"MyRBTree.h"

using namespace std;

int main(){
	cout<<"红黑树："<<endl;
	MyRBTree<int> RBTree1;
	RBTree1.insert(4);
	RBTree1.insert(5);
	RBTree1.insert(14);
	RBTree1.insert(15);
	RBTree1.insert(2);
	RBTree1.insert(11);
	RBTree1.insert(7);
	RBTree1.insert(1);
	RBTree1.insert(8);
	cout<<"打印红黑树："<<endl;
	RBTree1.print();
	cout<<"前序遍历：";
	RBTree1.preOrder();
	cout<<"中序遍历：";
	RBTree1.inOrder();
	cout<<"后序遍历：";
	RBTree1.postOrder();
	cout<<"寻找等于7的结点：";
	RBTreeNode<int>* tempRBNode = RBTree1.search(14);
	cout<<tempRBNode->data<<endl;
	cout<<"该结点的前驱：";
	RBTreeNode<int>* RBpre = RBTree1.predecessor(tempRBNode);
	cout<<RBpre->data<<endl;
	cout<<"该结点的后继：";
	RBTreeNode<int>* RBsu = RBTree1.sucessor(tempRBNode);
	cout<<RBsu->data<<endl;
	cout<<"删除该结点，删除后的树为："<<endl;
	RBTree1.remove(tempRBNode);
	RBTree1.print();
	cout<<"输出最大值：";
	cout<<RBTree1.maximumValue()<<endl;
	cout<<"输出最小值：";
	cout<<RBTree1.minimumValue()<<endl;
	cout<<"清空树：";
	RBTree1.clear();
	cout<<endl;

	return 0;
}