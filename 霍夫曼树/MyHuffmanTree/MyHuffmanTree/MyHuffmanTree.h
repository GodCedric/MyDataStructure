#ifndef __MUHUFFMANTREE__H__
#define __MUHUFFMANTREE__H__

#include"MyMinHeap.h"

//Huffman��
template<class T>
class MyHuffmanTree{
public:
	//��������
	MyHuffmanTree():Root(NULL){};
	~MyHuffmanTree(){};

	//����Huffman��
	void creatHuffmanTree();
	//��ʾ��������
	void printTree();
	//ǰ�����
	void preOrder();
	//�������
	void inOrder();
	//�������
	void postOrder();
	//�����
	void clearTree();

private:
	Node<T>* Root;

	void printTree(Node<T>* tree)const;    //��ʾ��
	void preOrder(Node<T>* tree)const;     //ǰ�����
	void inOrder(Node<T>* tree)const;      //�������
	void postOrder(Node<T>* tree)const;    //�������
	void clearTree(Node<T>*& tree);         //�����
};

//����Huffman��
template<class T>
void MyHuffmanTree<T>::creatHuffmanTree(){
	cout<<"�����������"<<endl;
	int N_node;
	cin>>N_node;
	MyMinHeap<T> nodeHeap(N_node);
	cout<<"������������Ȩֵ��"<<endl;
	T tempdata;
	Node<T>* tempnode;
	//�����н��ŵ���С����
	for(int i=0;i<N_node;i++){
		cin>>tempdata;
		tempnode = new Node<T>(tempdata);
		nodeHeap.insert(tempnode);
	}
	//��ʼ������������
	Node<T>* l;
	Node<T>* r;
	Node<T>* p;
	for(int i=0;i<N_node-1;i++){
		l = nodeHeap.pop();    //��С��Ȩ��
		r = nodeHeap.pop();    //��С��Ȩ��
		T pa = l->data + r->data;
		p = new Node<T>(pa);
		p->lchild = l;
		p->rchild = r;
		l->parent = p;
		r->parent = p;
		nodeHeap.insert(p);       //�ٰ������ɵĸ����ŵ�����
	}
	//������ֵ
	Root = p;
}

//��ʾ��������
template<class T>
void MyHuffmanTree<T>::printTree(Node<T>* tree)const{
	if(tree){
		cout<<"��㣺"<<tree->data<<" ";
		if(tree->lchild)
			cout<<"����Ϊ��"<<tree->lchild->data<<" ";
		else
			cout<<"������ ";
		if(tree->rchild)
			cout<<"�Һ���Ϊ��"<<tree->rchild->data<<" ";
		else
			cout<<"���Һ��� ";
		cout<<endl;
		printTree(tree->lchild);
		printTree(tree->rchild);
	}

}

template<class T>
void MyHuffmanTree<T>::printTree(){
	printTree(Root);
}

//ǰ�����
template<class T>
void MyHuffmanTree<T>::preOrder(Node<T>* tree)const{
	if(tree){
		cout<<tree->data<<"  ";
		preOrder(tree->lchild);
		preOrder(tree->rchild);
	}
}

template<class T>
void MyHuffmanTree<T>::preOrder(){
	preOrder(Root);
	cout<<endl;
}

//�������
template<class T>
void MyHuffmanTree<T>::inOrder(Node<T>* tree)const{
	if(tree){
		inOrder(tree->lchild);
		cout<<tree->data<<"  ";
		inOrder(tree->rchild);
	}
}

template<class T>
void MyHuffmanTree<T>::inOrder(){
	inOrder(Root);
	cout<<endl;
}

//�������
template<class T>
void MyHuffmanTree<T>::postOrder(Node<T>* tree)const{
	if(tree){
		postOrder(tree->lchild);
		postOrder(tree->rchild);
		cout<<tree->data<<"  ";
	}
}

template<class T>
void MyHuffmanTree<T>::postOrder(){
	postOrder(Root);
	cout<<endl;
}

//�����
template<class T>
void MyHuffmanTree<T>::clearTree(Node<T>*& tree){
	if(tree == NULL)
		return;
	if(tree->lchild)
		clearTree(tree->lchild);
	if(tree->rchild)
		clearTree(tree->rchild);
	delete tree;
	tree = NULL;
}

template<class T>
void MyHuffmanTree<T>::clearTree(){
	clearTree(Root);
	if(Root == NULL)
		cout<<"����ճɹ���"<<endl;
	else
		cout<<"�����ʧ�ܣ�"<<endl;
}

#endif