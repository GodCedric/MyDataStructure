#ifndef __MUHUFFMANTREE__H__
#define __MUHUFFMANTREE__H__

#include"MyMinHeap.h"

//Huffman树
template<class T>
class MyHuffmanTree{
public:
	//构造析构
	MyHuffmanTree():Root(NULL){};
	~MyHuffmanTree(){};

	//创建Huffman树
	void creatHuffmanTree();
	//显示霍夫曼树
	void printTree();
	//前序遍历
	void preOrder();
	//中序遍历
	void inOrder();
	//后序遍历
	void postOrder();
	//清空树
	void clearTree();

private:
	Node<T>* Root;

	void printTree(Node<T>* tree)const;    //显示树
	void preOrder(Node<T>* tree)const;     //前序遍历
	void inOrder(Node<T>* tree)const;      //中序遍历
	void postOrder(Node<T>* tree)const;    //后序遍历
	void clearTree(Node<T>*& tree);         //清空树
};

//创建Huffman树
template<class T>
void MyHuffmanTree<T>::creatHuffmanTree(){
	cout<<"请输入结点个数"<<endl;
	int N_node;
	cin>>N_node;
	MyMinHeap<T> nodeHeap(N_node);
	cout<<"请依次输入结点权值："<<endl;
	T tempdata;
	Node<T>* tempnode;
	//把所有结点放到最小堆中
	for(int i=0;i<N_node;i++){
		cin>>tempdata;
		tempnode = new Node<T>(tempdata);
		nodeHeap.insert(tempnode);
	}
	//开始创建霍夫曼树
	Node<T>* l;
	Node<T>* r;
	Node<T>* p;
	for(int i=0;i<N_node-1;i++){
		l = nodeHeap.pop();    //最小的权重
		r = nodeHeap.pop();    //次小的权重
		T pa = l->data + r->data;
		p = new Node<T>(pa);
		p->lchild = l;
		p->rchild = r;
		l->parent = p;
		r->parent = p;
		nodeHeap.insert(p);       //再把新生成的父结点放到堆中
	}
	//赋给根值
	Root = p;
}

//显示霍夫曼树
template<class T>
void MyHuffmanTree<T>::printTree(Node<T>* tree)const{
	if(tree){
		cout<<"结点："<<tree->data<<" ";
		if(tree->lchild)
			cout<<"左孩子为："<<tree->lchild->data<<" ";
		else
			cout<<"无左孩子 ";
		if(tree->rchild)
			cout<<"右孩子为："<<tree->rchild->data<<" ";
		else
			cout<<"无右孩子 ";
		cout<<endl;
		printTree(tree->lchild);
		printTree(tree->rchild);
	}

}

template<class T>
void MyHuffmanTree<T>::printTree(){
	printTree(Root);
}

//前序遍历
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

//中序遍历
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

//后序遍历
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

//清空树
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
		cout<<"树清空成功！"<<endl;
	else
		cout<<"树清空失败！"<<endl;
}

#endif