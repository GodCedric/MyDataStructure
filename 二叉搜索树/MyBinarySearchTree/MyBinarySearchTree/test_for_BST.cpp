#include<iostream>
#include"MyBinarySearchTree.h"

using namespace std;

int main(){
	cout<<"������������"<<endl;
	MyBinarySearchTree<int> MyTree;
	MyTree.insert(6);
	MyTree.insert(5);
	MyTree.insert(2);
	MyTree.insert(7);
	MyTree.insert(5);
	MyTree.insert(8);
	cout<<"��ӡ����"<<endl;
	MyTree.print();
	cout<<"ǰ�������";
	MyTree.preOrder();
	cout<<"���������";
	MyTree.inOrder();
	cout<<"���������";
	MyTree.postOrder();
	cout<<"Ѱ�ҵ���7�Ľ�㣺";
	TreeNode<int>* tempNode = MyTree.search(7);
	cout<<tempNode->data<<endl;
	cout<<"�ý���ǰ����";
	TreeNode<int>* pre = MyTree.predecessor(tempNode);
	cout<<pre->data<<endl;
	cout<<"�ý��ĺ�̣�";
	TreeNode<int>* su = MyTree.sucessor(tempNode);
	cout<<su->data<<endl;
	cout<<"ɾ���ý�㣬ɾ�������Ϊ��"<<endl;
	MyTree.remove(tempNode);
	MyTree.print();
	cout<<"������ֵ��";
	cout<<MyTree.maximumValue()<<endl;
	cout<<"�����Сֵ��";
	cout<<MyTree.minimumValue()<<endl;
	cout<<"�������";
	MyTree.clear();
	cout<<endl;

	return 0;
}