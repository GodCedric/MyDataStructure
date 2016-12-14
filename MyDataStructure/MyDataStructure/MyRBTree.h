#ifndef __MYRBTREE__H__
#define __MYRBTREE__H__
#include<iostream>

enum RBTColor{RED,BLACK};

template<class T>
struct RBTreeNode{
	T data;
	RBTColor color;
	struct RBTreeNode* left;
	struct RBTreeNode* right;
	struct RBTreeNode* p;
	RBTreeNode(T data):data(data),color(RED),left(NULL),right(NULL),p(NULL){}
};

template<class T>
class MyRBTree{
public:
	MyRBTree():Root(NULL){}
	~MyRBTree(){}

	void insert(T val);					//插入结点


private:
	RBTreeNode<T>* Root;                //根结点

	void left_rotate(RBTreeNode<T>*& tree,RBTreeNode<T>* x);         //左旋
	void right_rotate(RBTreeNode<T>*& tree,RBTreeNode<T>* x);        //右旋
	void insert_fixup(RBTreeNode<T>*& tree,RBTreeNode<T>* z);        //插入保持红黑性质
	void insert(RBTreeNode<T>*& tree,RBTreeNode<T>* z);              //插入结点
};

//左旋
template<class T>
void MyRBTree<T>::left_rotate(RBTreeNode<T>*& tree,RBTreeNode<T>* x){
	RBTreeNode<T>* y = x->right;
	x->right = y->left;
	if(y->left != NULL)
		y->left->p = x;
	y->p = x->p;
	if(x->p == NULL)
		tree = y;
	else if(x == x->p->left)
		x->p->left = y;
	else 
		x->p->right = y;
	y->left = x;
	x->p = y;
}

//右旋
template<class T>
void MyRBTree<T>::right_rotate(RBTreeNode<T>*& tree,RBTreeNode<T>* x){
	RBTreeNode<T>* y = x->left;
	x->left = y->right;
	if(y->right != NULL)
		y->right->p = x;
	y->p = x->p;
	if(x->p == NULL)
		tree = y;
	else if(x == x->p->right)
		x->p->right = y;
	else 
		x->p->left = y;
	y->right = x;
	x->p = y;
}

//插入保持红黑性质
template<class T>
void MyRBTree<T>::insert_fixup(RBTreeNode<T>*& tree,RBTreeNode<T>* z){
	RBTreeNode<T>* y;
	while(z->p->color == RED){
		if(z->p == z->p->p->left){
			y = z->p->p->right;
			if(y->color == RED){
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}else if(z == z->p->right){
				z = z->p;
				left_rotate(tree,z);
			}
			z->p->color = BLACK;
			z->p->p->color = RED;
			right_rotate(tree,z->p->p);
		}else{
			y = z->p->p->left;
			if(y->color == RED){
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}else if(z == z->p->left){
				z = z->p;
				right_rotate(tree,z);
			}
			z->p->color = BLACK;
			z->p->p->color = RED;
			left_rotate(tree,z->p->p);
		}
		tree->color = BLACK;
	}
}

//插入节点
template<class T>
void MyRBTree<T>::insert(RBTreeNode<T>*& tree,RBTreeNode<T>* z){
	RBTreeNode<T>* y = new RBTreeNode<T>(0);
	RBTreeNode<T>* x = Root;
	while(x != NULL){
		y = x;
		if(z->data < x->data)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if(y == NULL)
		tree = z;
	else if(z->data < y->data)
		y->left = z;
	else
		y->right = z;
	z->left = NULL;
	z->right = NULL;
	z->color = RED;
	insert_fixup(tree,z);
}

template<class T>
void MyRBTree<T>::insert(T val){
	RBTreeNode<T>* z = new RBTreeNode<T>(val);
	insert(Root,z);
}

#endif