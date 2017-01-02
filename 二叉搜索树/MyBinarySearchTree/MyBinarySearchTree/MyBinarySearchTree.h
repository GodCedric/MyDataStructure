#ifndef __MYMyBinarySearchTree__H__
#define __MYMyBinarySearchTree__H__
#include<iostream>
using namespace std;

template<class T>
struct TreeNode{
	T data;
	struct TreeNode* p;
	struct TreeNode* left;
	struct TreeNode* right;
	TreeNode(){}
	TreeNode(T data):data(data),p(NULL),left(NULL),right(NULL){}
};

template<class T>
class MyBinarySearchTree{
public:
	MyBinarySearchTree():Root(NULL){}
	~MyBinarySearchTree(){}

	void insert(T val);                          //插入结点
	void print();                                //打印
	TreeNode<T>* search(T val);                  //查找
	void preOrder();                             //前序遍历
	void inOrder();                              //中序遍历
	void postOrder();                            //后序遍历
	TreeNode<T>* minimumNode();					 //寻找最小结点
	TreeNode<T>* maximumNode();					 //寻找最大结点
	T minimumValue();							 //寻找最大值
	T maximumValue();							 //寻找最小值
	TreeNode<T>* predecessor(TreeNode<T>* x);    //前驱
	TreeNode<T>* sucessor(TreeNode<T>* x);       //后继
	void remove(TreeNode<T>* z);				 //删除结点
	void clear();								 //清空树

private:
	TreeNode<T>* Root;

	//重载函数，类内部使用，对链表、树这类结构采用二级指针或一级指针的引用操作
	//public里面仅定义外部接口，内部处理均由private里重载的函数进行
	void insert(TreeNode<T>*& tree,TreeNode<T>* z);
	void print(TreeNode<T>*& tree) const;
	TreeNode<T>* search(TreeNode<T>*& tree,T val) const;
	void preOrder(TreeNode<T>*& tree) const;
	void inOrder(TreeNode<T>*& tree) const;
	void postOrder(TreeNode<T>*& tree) const;
	TreeNode<T>* minimumNode(TreeNode<T>*& tree) const;
	TreeNode<T>* maximumNode(TreeNode<T>*& tree) const;
	void clear(TreeNode<T>*& tree);

	void transplant(TreeNode<T>*& tree,TreeNode<T>*& u,TreeNode<T>*& v);
	void remove(TreeNode<T>*& tree,TreeNode<T>* z);
};

//前序遍历
template<class T>
void MyBinarySearchTree<T>::preOrder(TreeNode<T>*& tree) const{
	if(tree){
		cout<<tree->data<<"  ";
		preOrder(tree->left);
		preOrder(tree->right);
	}
}

template<class T>
void MyBinarySearchTree<T>::preOrder(){
	preOrder(Root);
	cout<<endl;
}

//中序遍历
template<class T>
void MyBinarySearchTree<T>::inOrder(TreeNode<T>*& tree) const{
	if(tree){
		inOrder(tree->left);	
		cout<<tree->data<<"  ";
		inOrder(tree->right);
	}
}

template<class T>
void MyBinarySearchTree<T>::inOrder(){
	inOrder(Root);
	cout<<endl;
}

//后续遍历
template<class T>
void MyBinarySearchTree<T>::postOrder(TreeNode<T>*& tree) const{
	if(tree){
		postOrder(tree->left);
		postOrder(tree->right);
		cout<<tree->data<<"  ";
	}
}

template<class T>
void MyBinarySearchTree<T>::postOrder(){
	postOrder(Root);
	cout<<endl;
}

//插入
template<class T>
void MyBinarySearchTree<T>::insert(TreeNode<T>*& tree,TreeNode<T>* z){
	TreeNode<T>* copytree = tree;
	TreeNode<T>* z_parent = NULL;
	while(copytree != NULL){
		z_parent = copytree;
		if(z->data < copytree->data)
			copytree = copytree->left;
		else
			copytree = copytree->right;
	}
	if(z_parent == NULL)
		tree = z;
	else if(z->data < z_parent->data ){
		z_parent->left = z;
		z->p = z_parent;
	}else{
		z_parent->right = z;
		z->p = z_parent;
	}
}

template<class T> 
void MyBinarySearchTree<T>::insert(T val){
	TreeNode<T>* z = new TreeNode<T>(val);
	insert(Root,z);
}

//打印二叉树
template<class T>
void MyBinarySearchTree<T>::print(TreeNode<T>*& tree) const{
	if(tree){
		cout<<"结点 "<<tree->data<<":";
		if(tree->left)
			cout<<"左结点为"<<tree->left->data<<"  ";
		else
			cout<<"无左结点 ";
		if(tree->right)
			cout<<"右结点为"<<tree->right->data<<"  ";
		else
			cout<<"无右结点 ";
	    cout<<endl;
		print(tree->left);
		print(tree->right);
	}
}

template<class T>
void MyBinarySearchTree<T>::print(){
	print(Root);
}

//查询结点
template<class T>
TreeNode<T>* MyBinarySearchTree<T>::search(TreeNode<T>*& tree,T val) const{
	TreeNode<T>* copytree = tree;
	while(copytree != NULL){
		if(copytree->data == val){
			return copytree;
		}else if(copytree->data > val){
			copytree = copytree->left;
		}else{
			copytree = copytree->right;
		}
	}
	return NULL;
}

template<class T>
TreeNode<T>* MyBinarySearchTree<T>::search(T val){
	return search(Root,val);
}

//查询最小结点及最小值
template<class T>
TreeNode<T>* MyBinarySearchTree<T>::minimumNode(TreeNode<T>*& tree) const{
	TreeNode<T>* copytree = tree;
	while(copytree->left){
		copytree = copytree->left;
	}
	return copytree;
}

template<class T>
TreeNode<T>* MyBinarySearchTree<T>::minimumNode(){
	return minimumNode(Root);
}

template<class T>
T MyBinarySearchTree<T>::minimumValue(){
	TreeNode<T>* temp = minimumNode(Root);
	return temp->data;
}

//查询最大结点及最大值
template<class T>
TreeNode<T>* MyBinarySearchTree<T>::maximumNode(TreeNode<T>*& tree) const{
	TreeNode<T>* copytree = tree;
	while(copytree->right){
		copytree = copytree->right;
	}
	return copytree;
}

template<class T>
TreeNode<T>* MyBinarySearchTree<T>::maximumNode(){
	return maximumNode(Root);
}

template<class T>
T MyBinarySearchTree<T>::maximumValue(){
	TreeNode<T>* temp = maximumNode(Root);
	return temp->data;
}

//前驱
template<class T>
TreeNode<T>* MyBinarySearchTree<T>::predecessor(TreeNode<T>* x){
	if(x->left)
		return maximumNode(x->left);
	TreeNode<T>* temp = x->p;
	while(temp && x==temp->left){
		x = temp;
		temp = temp->p;
	}
	return temp;
}

//后继
template<class T>
TreeNode<T>* MyBinarySearchTree<T>::sucessor(TreeNode<T>* x){
	if(x->right)
		return minimumNode(x->right);
	TreeNode<T>* temp = x->p;
	while(temp && x==temp->right){
		x = temp;
		temp = temp->p;
	}
	return temp;
}

//删除结点子过程
template<class T>
void MyBinarySearchTree<T>::transplant(TreeNode<T>*& tree,TreeNode<T>*& u,TreeNode<T>*& v){
	if(tree == u)
		tree = v;
	else if(u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	if(v != NULL)
		v->p = u->p;        //没有释放u的空间
}

//删除结点
template<class T>
void MyBinarySearchTree<T>::remove(TreeNode<T>*& tree,TreeNode<T>* z){
	TreeNode<T>* y;
	if(z->left == NULL)
		transplant(tree,z,z->right);
	else if(z->right == NULL)
		transplant(tree,z,z->right);
	else{
		y = minimumNode(z->right);
		if(y->p == z){
			transplant(tree,z,y);
			y->left = z->left;
			z->left->p = y;
		}else{
			transplant(tree,y,y->right);
			y->right = z->right;
			y->right->p = y;
		}
	}
	delete z;
}

template<class T>
void MyBinarySearchTree<T>::remove(TreeNode<T>* z){
	remove(Root,z);
}

//清空树
template<class T>
void MyBinarySearchTree<T>::clear(TreeNode<T>*& tree){
	if(tree->left != NULL){
		clear(tree->left);
	}
	if(tree->right != NULL){
		clear(tree->right);
	}
	if(tree->left==NULL && tree->right==NULL){
		delete tree;
		tree = NULL;           //这里必须得加一行设成NULL，因为如果只释放空间不置NULL的话，其父节点的孩子指针将不会指向NULL，也就不会递归回去继续删除。
	}
}

template<class T>
void MyBinarySearchTree<T>::clear(){
	clear(Root);
	if(Root == NULL)
		cout<<"已清空"<<endl;
	else
		cout<<"清空失败"<<endl;
}



#endif