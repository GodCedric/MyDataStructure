#include<iostream>
#include"MyBinarySearchTree.h"

using namespace std;

int main(){
	cout<<"二叉搜索树："<<endl;
	MyBinarySearchTree<int> MyTree;
	MyTree.insert(6);
	MyTree.insert(5);
	MyTree.insert(2);
	MyTree.insert(7);
	MyTree.insert(5);
	MyTree.insert(8);
	cout<<"打印树："<<endl;
	MyTree.print();
	cout<<"前序遍历：";
	MyTree.preOrder();
	cout<<"中序遍历：";
	MyTree.inOrder();
	cout<<"后序遍历：";
	MyTree.postOrder();
	cout<<"寻找等于7的结点：";
	TreeNode<int>* tempNode = MyTree.search(7);
	cout<<tempNode->data<<endl;
	cout<<"该结点的前驱：";
	TreeNode<int>* pre = MyTree.predecessor(tempNode);
	cout<<pre->data<<endl;
	cout<<"该结点的后继：";
	TreeNode<int>* su = MyTree.sucessor(tempNode);
	cout<<su->data<<endl;
	cout<<"删除该结点，删除后的树为："<<endl;
	MyTree.remove(tempNode);
	MyTree.print();
	cout<<"输出最大值：";
	cout<<MyTree.maximumValue()<<endl;
	cout<<"输出最小值：";
	cout<<MyTree.minimumValue()<<endl;
	cout<<"清空树：";
	MyTree.clear();
	cout<<endl;

	return 0;
}