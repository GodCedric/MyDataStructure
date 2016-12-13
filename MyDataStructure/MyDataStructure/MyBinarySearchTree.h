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
	TreeNode(T data):data(data),p(NULL),left(NULL),right(NULL){}
};

template<class T>
class MyBinarySearchTree{
public:
	MyBinarySearchTree():Root(NULL){}
	~MyBinarySearchTree(){}

	void insert(T val);                          //������
	void print();                                //��ӡ
	TreeNode<T>* search(T val);                  //����
	void preOrder();                             //ǰ�����
	void inOrder();                              //�������
	void postOrder();                            //�������
	TreeNode<T>* minimumNode();					 //Ѱ����С���
	TreeNode<T>* maximumNode();					 //Ѱ�������
	T minimumValue();							 //Ѱ�����ֵ
	T maximumValue();							 //Ѱ����Сֵ
	TreeNode<T>* predecessor(TreeNode<T>* x);    //ǰ��
	TreeNode<T>* sucessor(TreeNode<T>* x);       //���
	void clear();								 //�����

private:
	TreeNode<T>* Root;

	//���غ��������ڲ�ʹ�ã�������������ṹ���ö���ָ���һ��ָ������ò���
	//public����������ⲿ�ӿڣ��ڲ��������private�����صĺ�������
	void insert(TreeNode<T>*& tree,TreeNode<T>* z);
	TreeNode<T>* search(TreeNode<T>*& tree,T val) const;
	void preOrder(TreeNode<T>*& tree) const;
	void inOrder(TreeNode<T>*& tree) const;
	void postOrder(TreeNode<T>*& tree) const;
	TreeNode<T>* minimumNode(TreeNode<T>*& tree) const;
	TreeNode<T>* maximumNode(TreeNode<T>*& tree) const;
	void clear(TreeNode<T>*& tree);

	void print(TreeNode<T>*& tree) const;
	TreeNode<T>* remove(TreeNode<T>*& tree,TreeNode<T>* z);
};

//ǰ�����
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

//�������
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

//��������
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

//����
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

//��ӡ������
template<class T>
void MyBinarySearchTree<T>::print(TreeNode<T>*& tree) const{
	if(tree){
		cout<<"��� "<<tree->data<<":";
		if(tree->left)
			cout<<"����Ϊ "<<tree->left->data<<"  ";
		else
			cout<<"������ ";
		if(tree->right)
			cout<<"�ҽ��Ϊ "<<tree->right->data<<"  ";
		else
			cout<<"���ҽ�� ";
	    cout<<endl;
		print(tree->left);
		print(tree->right);
	}
}

template<class T>
void MyBinarySearchTree<T>::print(){
	print(Root);
}

//��ѯ���
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

//��ѯ��С��㼰��Сֵ
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

//��ѯ����㼰���ֵ
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

//ǰ��
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

//���
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

#endif