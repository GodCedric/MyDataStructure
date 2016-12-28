#include<iostream>
#include<vector>
#include"MyStack.h"
#include"MyQueue.h"
#include"MyList.h"
#include"MyBinarySearchTree.h"
#include"MyRBTree.h"
#include"MyLinkGraph.h"
#include"MyMatrixGraph.h"
#include"MyHeap.h"
#include"MyBTree.h"

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
	cout<<endl;

	//红黑树
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

	//图
	//////基于邻接链表的图
	/*MyLinkGraph<char,int> g(30);
	char ch1,ch2;
	int weight;
	g.inputGraph();
	g.outputGraph();
	cout<<"顶点数和边数："<<g.NumofVertices()<<" "<<g.NumofEdges()<<endl;
	cout<<"插入顶点:";  
    cin >>ch1;  
    g.insertVertex(ch1);  //插入点  
    cout<<"插入边："<<endl;  
    cin >>ch1>>ch2>>weight;  
	g.inertEdge(g.getVertexPos(ch1),g.getVertexPos(ch2),weight);//插入边
	g.outputGraph();
	cout<<"删除边：";  
    cin >>ch1>>ch2;  
    g.removeEdge(g.getVertexPos(ch1),g.getVertexPos(ch2)); //删除边  
  
    cout<<"删除点：";  
    cin>>ch1;  
    g.removeVertex(g.getVertexPos(ch1));  
    g.outputGraph(); */

	//////基于矩阵的图
	/*MyMatrixGraph<char,int> r(30);
	char ch3,ch4;
	int weight2;
	r.inputGraph();
	r.outputGraph();
	cout<<"插入顶点:";  
    cin >>ch3;  
    r.insertVertex(ch3);  //插入点  
    cout<<"插入边："<<endl;  
    cin >>ch3>>ch4>>weight2;  
	r.inertEdge(r.getVertexPos(ch3),r.getVertexPos(ch4),weight2);//插入边
	r.outputGraph();
	cout<<"删除边：";  
    cin >>ch3>>ch4;  
    r.removeEdge(r.getVertexPos(ch3),r.getVertexPos(ch4)); //删除边  
  
    cout<<"删除点：";  
    cin>>ch3;  
    r.removeVertex(r.getVertexPos(ch3));  
    r.outputGraph();*/

	//堆
	//////注意，这里的堆不是一个类，而是只提供了三个接口函数
	//////分别为：建立堆Build_Max_Heap，维护堆Max_Heapify，和堆排序heap_sort
	int A[] = {3,7,2,8,10,7,3,9,75,36,88,12,5,77,99,111,57,22,-2,-67};
	vector<int> CC(A,A+20);
	vector<int>::iterator first3=CC.begin();
	vector<int>::iterator last3=CC.end();
	heap_sort(first3,last3);
	cout<<"堆排序结果"<<endl;
	for(int i=0;i<CC.size();i++)
		cout<<CC[i]<<"  ";
	cout<<endl;

	//B树
	MyBTree<char> bt;
	bt.insert('G');
	bt.insert('M');
	bt.insert('P');
	bt.insert('X');
	bt.insert('A');
	bt.insert('C');
	bt.insert('D');
	bt.insert('E');
	bt.insert('J');
	bt.insert('K');
	bt.insert('N');
	bt.insert('O');
	bt.insert('R');

	if(bt.search('A'))
		cout<<"找到了！"<<endl;
	
	
	return 0;
}