#include<iostream>
#include"MyStack.h"
#include"MyQueue.h"
#include"MyList.h"
#include"MyBinarySearchTree.h"
using namespace std;

int main(){

	//栈
	MyStack<int> s(5);
	s.push(1);
	s.push(2);
	cout<<"栈："<<endl;
	cout<<"栈是否为空："<<s.empty()<<endl;
	cout<<"弹出栈顶："<<s.pop()<<endl;
	cout<<"弹出栈顶："<<s.pop()<<endl;
	cout<<"栈是否为空："<<s.empty()<<endl;
	cout<<endl;

	//队列
	MyQueue<double> q(5);
	q.enqueue(2.5);
	q.enqueue(3.8);
	cout<<"队列："<<endl;
	cout<<"队列是否为空："<<q.empty()<<endl;
	cout<<"删除队头："<<q.dequeue()<<endl;
	cout<<"删除队头："<<q.dequeue()<<endl;
	cout<<"队列是否为空："<<q.empty()<<endl;
	cout<<endl;
	
	//单向链表
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

	//二叉搜索树
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

	return 0;
}