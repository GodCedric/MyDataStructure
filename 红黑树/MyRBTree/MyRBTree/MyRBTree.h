#ifndef __MYRBTREE__H__
#define __MYRBTREE__H__
#include<iostream>

enum RBTColor{RED,BLACK};
const char Color[2] = {'R','B'};

template<class T>
struct RBTreeNode{
	T data;
	RBTColor color;
	struct RBTreeNode* left;
	struct RBTreeNode* right;
	struct RBTreeNode* p;
	RBTreeNode(T data):data(data),color(BLACK),left(NULL),right(NULL),p(NULL){}
};

template<class T>
class MyRBTree{
public:
	MyRBTree(){
		NIL = new RBTreeNode<T>(-99999);
		Root = NIL;
	}
	~MyRBTree(){}

	void insert(T val);					//������
	void print();						//��ӡ��
	RBTreeNode<T>* search(T val);                  //����
	void preOrder();                             //ǰ�����
	void inOrder();                              //�������
	void postOrder();                            //�������
	RBTreeNode<T>* minimumNode();					 //Ѱ����С���
	RBTreeNode<T>* maximumNode();					 //Ѱ�������
	T minimumValue();							 //Ѱ�����ֵ
	T maximumValue();							 //Ѱ����Сֵ
	RBTreeNode<T>* predecessor(RBTreeNode<T>* x);    //ǰ��
	RBTreeNode<T>* sucessor(RBTreeNode<T>* x);       //���
	void remove(RBTreeNode<T>*& z);             //ɾ�����
	void clear();								 //�����


private:
	RBTreeNode<T>* Root;                //�����
	RBTreeNode<T>* NIL;                 //�ڱ�

	void left_rotate(RBTreeNode<T>*& tree,RBTreeNode<T>* x);         //����
	void right_rotate(RBTreeNode<T>*& tree,RBTreeNode<T>* x);        //����
	void insert_fixup(RBTreeNode<T>*& tree,RBTreeNode<T>*& z);        //���뱣�ֺ������
	void insert(RBTreeNode<T>*& tree,RBTreeNode<T>* z);              //������
	void print(RBTreeNode<T>*& tree) const;							 //��ӡ��
	RBTreeNode<T>* search(RBTreeNode<T>*& tree,T val) const;
	void preOrder(RBTreeNode<T>*& tree) const;
	void inOrder(RBTreeNode<T>*& tree) const;
	void postOrder(RBTreeNode<T>*& tree) const;
	RBTreeNode<T>* minimumNode(RBTreeNode<T>*& tree) const;          //��С���
	RBTreeNode<T>* maximumNode(RBTreeNode<T>*& tree) const;          //z�����
	void transplant(RBTreeNode<T>*& tree,RBTreeNode<T>*& u,RBTreeNode<T>*& v);     //ɾ������ӹ���
	void remove_fixup(RBTreeNode<T>*& tree,RBTreeNode<T>*& x);        //ɾ�����ֺ������
	void remove(RBTreeNode<T>*& tree,RBTreeNode<T>*& z);              //ɾ�����
	void clear(RBTreeNode<T>*& tree);                        //�����
};

//����
template<class T>
void MyRBTree<T>::left_rotate(RBTreeNode<T>*& tree,RBTreeNode<T>* x){
	RBTreeNode<T>* y = x->right;
	x->right = y->left;
	if(y->left != NIL)
		y->left->p = x;
	y->p = x->p;
	if(x->p == NIL)
		tree = y;
	else if(x == x->p->left)
		x->p->left = y;
	else 
		x->p->right = y;
	y->left = x;
	x->p = y;
}

//����
template<class T>
void MyRBTree<T>::right_rotate(RBTreeNode<T>*& tree,RBTreeNode<T>* x){
	RBTreeNode<T>* y = x->left;
	x->left = y->right;
	if(y->right != NIL)
		y->right->p = x;
	y->p = x->p;
	if(x->p == NIL)
		tree = y;
	else if(x == x->p->right)
		x->p->right = y;
	else 
		x->p->left = y;
	y->right = x;
	x->p = y;
}

//���뱣�ֺ������
template<class T>
void MyRBTree<T>::insert_fixup(RBTreeNode<T>*& tree,RBTreeNode<T>*& z){
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
			}else{
				z->p->color = BLACK;
				z->p->p->color = RED;
				right_rotate(tree,z->p->p);
			}
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
			}else{
				z->p->color = BLACK;
				z->p->p->color = RED;
				left_rotate(tree,z->p->p);
			}
		}
	}
	tree->color = BLACK;
}

//������
template<class T>
void MyRBTree<T>::insert(RBTreeNode<T>*& tree,RBTreeNode<T>* z){
	RBTreeNode<T>* y = NIL;
	RBTreeNode<T>* x = Root;
	while(x != NIL){
		y = x;
		if(z->data < x->data)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if(y == NIL)
		tree = z;
	else if(z->data < y->data)
		y->left = z;
	else
		y->right = z;
	z->left = NIL;
	z->right = NIL;
	z->color = RED;
	insert_fixup(tree,z);
}

template<class T>
void MyRBTree<T>::insert(T val){
	RBTreeNode<T>* z = new RBTreeNode<T>(val);
	insert(Root,z);
}

//��ӡ��
template<class T>
void MyRBTree<T>::print(RBTreeNode<T>*& tree) const{
	if(tree){
		if(tree != NIL){
			cout<<"��� "<<tree->data<<"("<<Color[tree->color]<<")"<<":";
			if(tree->left != NIL)
				cout<<"����Ϊ"<<tree->left->data<<"("<<Color[tree->left->color]<<")"<<"  ";
			else
				cout<<"����Ϊ�ڱ� ";

			if(tree->right != NIL)
				cout<<"�ҽ��Ϊ"<<tree->right->data<<"("<<Color[tree->right->color]<<")"<<"  ";
			else
				cout<<"�ҽ��Ϊ�ڱ� ";
			cout<<endl;
		}
		print(tree->left);
		print(tree->right);
	}
}

template<class T>
void MyRBTree<T>::print(){
	print(Root);
}

//ǰ�����
template<class T>
void MyRBTree<T>::preOrder(RBTreeNode<T>*& tree) const{
	if(tree != NIL){
		cout<<tree->data<<"  ";
		preOrder(tree->left);
		preOrder(tree->right);
	}
}

template<class T>
void MyRBTree<T>::preOrder(){
	preOrder(Root);
	cout<<endl;
}

//�������
template<class T>
void MyRBTree<T>::inOrder(RBTreeNode<T>*& tree) const{
	if(tree != NIL){
		inOrder(tree->left);	
		cout<<tree->data<<"  ";
		inOrder(tree->right);
	}
}

template<class T>
void MyRBTree<T>::inOrder(){
	inOrder(Root);
	cout<<endl;
}

//��������
template<class T>
void MyRBTree<T>::postOrder(RBTreeNode<T>*& tree) const{
	if(tree != NIL){
		postOrder(tree->left);
		postOrder(tree->right);
		cout<<tree->data<<"  ";
	}
}

template<class T>
void MyRBTree<T>::postOrder(){
	postOrder(Root);
	cout<<endl;
}

//��ѯ���
template<class T>
RBTreeNode<T>* MyRBTree<T>::search(RBTreeNode<T>*& tree,T val) const{
	RBTreeNode<T>* copytree = tree;
	while(copytree != NIL){
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
RBTreeNode<T>* MyRBTree<T>::search(T val){
	return search(Root,val);
}

//��ѯ��С��㼰��Сֵ
template<class T>
RBTreeNode<T>* MyRBTree<T>::minimumNode(RBTreeNode<T>*& tree) const{
	RBTreeNode<T>* copytree = tree;
	while(copytree->left != NIL){
		copytree = copytree->left;
	}
	return copytree;
}

template<class T>
RBTreeNode<T>* MyRBTree<T>::minimumNode(){
	return minimumNode(Root);
}

template<class T>
T MyRBTree<T>::minimumValue(){
	RBTreeNode<T>* temp = minimumNode(Root);
	return temp->data;
}

//��ѯ����㼰���ֵ
template<class T>
RBTreeNode<T>* MyRBTree<T>::maximumNode(RBTreeNode<T>*& tree) const{
	RBTreeNode<T>* copytree = tree;
	while(copytree->right != NIL){
		copytree = copytree->right;
	}
	return copytree;
}

template<class T>
RBTreeNode<T>* MyRBTree<T>::maximumNode(){
	return maximumNode(Root);
}

template<class T>
T MyRBTree<T>::maximumValue(){
	RBTreeNode<T>* temp = maximumNode(Root);
	return temp->data;
}

//ǰ��
template<class T>
RBTreeNode<T>* MyRBTree<T>::predecessor(RBTreeNode<T>* x){
	if(x->left != NIL)
		return maximumNode(x->left);
	RBTreeNode<T>* temp = x->p;
	while(temp!=NIL && x==temp->left){
		x = temp;
		temp = temp->p;
	}
	return temp;
}

//���
template<class T>
RBTreeNode<T>* MyRBTree<T>::sucessor(RBTreeNode<T>* x){
	if(x->right != NIL)
		return minimumNode(x->right);
	RBTreeNode<T>* temp = x->p;
	while(temp!=NIL && x==temp->right){
		x = temp;
		temp = temp->p;
	}
	return temp;
}

//ɾ������ӹ���
template<class T>
void MyRBTree<T>::transplant(RBTreeNode<T>*& tree,RBTreeNode<T>*& u,RBTreeNode<T>*& v){
	if(u->p == NIL)
		tree = v;
	else if(u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	v->p = u->p;
}

//ɾ�����ֺ������
template<class T>
void MyRBTree<T>::remove_fixup(RBTreeNode<T>*& tree,RBTreeNode<T>*& x){
	while(x!=tree && x->color==BLACK){
		if(x==x->p->left){
			RBTreeNode<T>* w = x->p->right;
			if(w->color == RED){
				w->color = BLACK;
				x->p->color = RED;
				left_rotate(tree,x->p);
				w = x->p->right;
			}
			if(w->left->color==BLACK && w->right->color==BLACK){
				w->color = RED;
				x = x->p;
			}else if(w->right->color == BLACK){
				w->left->color = BLACK;
				w->color = RED;
				right_rotate(tree,w);
				w = x->p->right;
			}else{
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				left_rotate(tree,x->p);
				x = tree;
			}
		}else{
			RBTreeNode<T>* w = x->p->left;
			if(w->color == RED){
				w->color = BLACK;
				x->p->color = RED;
				right_rotate(tree,x->p);
				w = x->p->left;
			}
			if(w->right->color==BLACK && w->left->color==BLACK){
				w->color = RED;
				x = x->p;
			}else if(w->left->color == BLACK){
				w->right->color = BLACK;
				w->color = RED;
				left_rotate(tree,w);
				w = x->p->left;
			}else{
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				right_rotate(tree,x->p);
				x = tree;
			}
		}
	}
	x->color = BLACK;
}

template<class T>
void MyRBTree<T>::remove(RBTreeNode<T>*& tree,RBTreeNode<T>*& z){
	RBTreeNode<T>* y = z;
	RBTColor original_color = y->color;
	RBTreeNode<T>* x;
	if(z->left == NIL){
		x = z->right;
		transplant(tree,z,z->right);
	}else if(z->right == NIL){
		x = z->left;
		transplant(tree,z,z->left);
	}else{
		y = minimumNode(z->right);
		original_color = y->color;
		x = y->right;
		if(y->p == z)
			x->p = y;
		else{
			transplant(tree,y,y->right);
			y->right = z->right;
			y->right->p = y;
		}
		transplant(tree,z,y);
		y->left = z->left;
		y->left->p = y;
		y->color = z->color;
	}
	if(original_color == BLACK)
		remove_fixup(tree,x);
	
}

template<class T>
void MyRBTree<T>::remove(RBTreeNode<T>*& z){
	remove(Root,z);
}

//�����
template<class T>
void MyRBTree<T>::clear(RBTreeNode<T>*& tree){
	if(tree->left != NIL){
		clear(tree->left);
	}
	if(tree->right != NIL){
		clear(tree->right);
	}
	if(tree->left==NIL && tree->right==NIL){
		delete tree;
		tree = NIL;           //�������ü�һ�����NULL����Ϊ���ֻ�ͷſռ䲻��NULL�Ļ����丸�ڵ�ĺ���ָ�뽫����ָ��NULL��Ҳ�Ͳ���ݹ��ȥ����ɾ����
	}
}

template<class T>
void MyRBTree<T>::clear(){
	clear(Root);
	if(Root == NIL)
		cout<<"�����"<<endl;
	else
		cout<<"���ʧ��"<<endl;
}



#endif