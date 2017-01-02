#include<iostream>
#include"MyRBTree.h"

using namespace std;

int main(){
	cout<<"�������"<<endl;
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
	cout<<"��ӡ�������"<<endl;
	RBTree1.print();
	cout<<"ǰ�������";
	RBTree1.preOrder();
	cout<<"���������";
	RBTree1.inOrder();
	cout<<"���������";
	RBTree1.postOrder();
	cout<<"Ѱ�ҵ���7�Ľ�㣺";
	RBTreeNode<int>* tempRBNode = RBTree1.search(14);
	cout<<tempRBNode->data<<endl;
	cout<<"�ý���ǰ����";
	RBTreeNode<int>* RBpre = RBTree1.predecessor(tempRBNode);
	cout<<RBpre->data<<endl;
	cout<<"�ý��ĺ�̣�";
	RBTreeNode<int>* RBsu = RBTree1.sucessor(tempRBNode);
	cout<<RBsu->data<<endl;
	cout<<"ɾ���ý�㣬ɾ�������Ϊ��"<<endl;
	RBTree1.remove(tempRBNode);
	RBTree1.print();
	cout<<"������ֵ��";
	cout<<RBTree1.maximumValue()<<endl;
	cout<<"�����Сֵ��";
	cout<<RBTree1.minimumValue()<<endl;
	cout<<"�������";
	RBTree1.clear();
	cout<<endl;

	return 0;
}