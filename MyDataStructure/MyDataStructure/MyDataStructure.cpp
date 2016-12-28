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

	//ջ
	MyStack<int> s(5);
	s.push(1);
	s.push(2);
	cout<<"ջ��"<<endl;
	cout<<"ջ�Ƿ�Ϊ�գ�"<<s.empty()<<endl;
	cout<<"����ջ����"<<s.pop()<<endl;
	cout<<"����ջ����"<<s.pop()<<endl;
	cout<<"ջ�Ƿ�Ϊ�գ�"<<s.empty()<<endl;
	cout<<endl;

	//����
	MyQueue<double> q(5);
	q.enqueue(2.5);
	q.enqueue(3.8);
	cout<<"���У�"<<endl;
	cout<<"�����Ƿ�Ϊ�գ�"<<q.empty()<<endl;
	cout<<"ɾ����ͷ��"<<q.dequeue()<<endl;
	cout<<"ɾ����ͷ��"<<q.dequeue()<<endl;
	cout<<"�����Ƿ�Ϊ�գ�"<<q.empty()<<endl;
	cout<<endl;
	
	//��������
	MyList<int> l;
	cout<<"��������"<<endl;
	l.insert(1);
	l.insert(2);
	l.insert(3);
	l.insert(3);
	l.insert(4);
	l.insert(5);
	cout<<"������룺 ";
	l.visit();
	l.deleteValue(3);
	cout<<"ɾ��ֵ����3�Ľ�㣺 ";
	l.visit();
	Node<int>* temp = l.find(2);
	cout<<"�ҵ�ֵΪ2�Ľ�㣬����ָ�룺 ";
	cout<<temp->data<<endl;
	cout<<"ɾ������2�������㣺 ";
	l.deleteNode(temp);
	l.visit();
	cout<<"������� ";
	l.clear();
	l.visit();

	//����������
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

	//�����
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

	//ͼ
	//////�����ڽ������ͼ
	/*MyLinkGraph<char,int> g(30);
	char ch1,ch2;
	int weight;
	g.inputGraph();
	g.outputGraph();
	cout<<"�������ͱ�����"<<g.NumofVertices()<<" "<<g.NumofEdges()<<endl;
	cout<<"���붥��:";  
    cin >>ch1;  
    g.insertVertex(ch1);  //�����  
    cout<<"����ߣ�"<<endl;  
    cin >>ch1>>ch2>>weight;  
	g.inertEdge(g.getVertexPos(ch1),g.getVertexPos(ch2),weight);//�����
	g.outputGraph();
	cout<<"ɾ���ߣ�";  
    cin >>ch1>>ch2;  
    g.removeEdge(g.getVertexPos(ch1),g.getVertexPos(ch2)); //ɾ����  
  
    cout<<"ɾ���㣺";  
    cin>>ch1;  
    g.removeVertex(g.getVertexPos(ch1));  
    g.outputGraph(); */

	//////���ھ����ͼ
	/*MyMatrixGraph<char,int> r(30);
	char ch3,ch4;
	int weight2;
	r.inputGraph();
	r.outputGraph();
	cout<<"���붥��:";  
    cin >>ch3;  
    r.insertVertex(ch3);  //�����  
    cout<<"����ߣ�"<<endl;  
    cin >>ch3>>ch4>>weight2;  
	r.inertEdge(r.getVertexPos(ch3),r.getVertexPos(ch4),weight2);//�����
	r.outputGraph();
	cout<<"ɾ���ߣ�";  
    cin >>ch3>>ch4;  
    r.removeEdge(r.getVertexPos(ch3),r.getVertexPos(ch4)); //ɾ����  
  
    cout<<"ɾ���㣺";  
    cin>>ch3;  
    r.removeVertex(r.getVertexPos(ch3));  
    r.outputGraph();*/

	//��
	//////ע�⣬����ĶѲ���һ���࣬����ֻ�ṩ�������ӿں���
	//////�ֱ�Ϊ��������Build_Max_Heap��ά����Max_Heapify���Ͷ�����heap_sort
	int A[] = {3,7,2,8,10,7,3,9,75,36,88,12,5,77,99,111,57,22,-2,-67};
	vector<int> CC(A,A+20);
	vector<int>::iterator first3=CC.begin();
	vector<int>::iterator last3=CC.end();
	heap_sort(first3,last3);
	cout<<"��������"<<endl;
	for(int i=0;i<CC.size();i++)
		cout<<CC[i]<<"  ";
	cout<<endl;

	//B��
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
		cout<<"�ҵ��ˣ�"<<endl;
	
	
	return 0;
}