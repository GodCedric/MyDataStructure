/*
 * MyFibHeap.h
 *
 *  Created on: 2017��1��6��
 *      Author: Cedric
 */

#ifndef MYFIBHEAP_H_
#define MYFIBHEAP_H_

#include"FibNode.h"
#include<iostream>
#include<cmath>
#include<algorithm>
#include<iomanip>

using namespace std;

//����쳲�������
template<class T>
class MyFibHeap{
public:
	//��������
	MyFibHeap();
	~MyFibHeap();

	//������
	void insert(T value);
	//�����ǰ�ѵ���С��ֵ
	void printMin();
	//�ϲ�(��H�ϲ�����ǰ����)
	static MyFibHeap<T>* heapunion(MyFibHeap<T>* H1,MyFibHeap<T>* H2);
	//��ȡ��С����ֵ
	T extractMin();
	//��ӡ��
	void print();
	//�ͷŽ���ڴ�
	void clearNode();
	//Ѱ�Ҽ�ֵΪk�Ľ��
	FibNode<T>* findNode(T val);
	//�ؼ��ּ�ֵ
	void decreaseKey(FibNode<T>* x,T k);
	//ɾ�����
	void removeNode(FibNode<T>* x);

private:
	FibNode<T>* Min;    //ָ����С���
	int n;              //������
	int maxDegree;      //����
	//FibNode<T>** A;     //consolidateʹ�ã���¼������Ӧ�Ķ����Ĺ켣

	//�ѽ��嵽��������
	void addNode(FibNode<T>* min,FibNode<T>* node);
	//�ѽ��������м�������
	void cutNode(FibNode<T>* node);
	//��ȡ��Сֵ��������consolidate
	void consolidate();
	//consolidate������������y�ӵ�x����
	void heaplink(FibNode<T>* x,FibNode<T>* y);
	//��ӡ��
	void print(FibNode<T> *node, FibNode<T> *prev, int direction);
	//Ѱ�Ҽ�ֵΪkey�Ľ��
	FibNode<T>* findNode(FibNode<T>* root,T val);
	//�ؼ��ּ�ֵ��������cut
	void cut(FibNode<T>* x,FibNode<T>* y);
	//�ؼ��ּ�ֵ��������cascading_cut
	void cascading_cut(FibNode<T>* y);
	//�ͷŽ���ڴ�
	void clearNode(FibNode<T>* root);

};

//���캯��
template<class T>
MyFibHeap<T>::MyFibHeap(){
	Min = NULL;
	n = 0;
	maxDegree = 0;
}

//��������
template<class T>
MyFibHeap<T>::~MyFibHeap(){
	//��ֹ�û������ͷŽ���ڴ�
	clearNode(Min);
}

//�����С��ֵ
template<class T>
void MyFibHeap<T>::printMin(){
	if(Min == NULL){
		cout<<"��ǰ���޽�㣡"<<endl;
		return;
	}else{
		cout<<Min->key<<endl;
		return;
	}
}

//�ѽ��嵽��������
template<class T>
void MyFibHeap<T>::addNode(FibNode<T>* min,FibNode<T>* node){
	node->left = min->left;
	min->left->right = node;
	min->left = node;
	node->right = min;
}

//�ѽ���������ɾ��
template<class T>
void MyFibHeap<T>::cutNode(FibNode<T>* node){
	//��node�����жϷŵ����洦���ɵ��õĳ�Ա��������nodeΪ�յ����
	node->left->right = node->right;
	node->right->left = node->left;
}


//������
template<class T>
void MyFibHeap<T>::insert(T value){
	//�������
	FibNode<T>* node = new FibNode<T>(value);
	//���������Ϊ�գ���Minָ��node
	//���������Ϊ�գ���Minָ��node
	if(Min == NULL){
		Min = node;
	}else{    //��Ϊ����node�ŵ�Min�����
		addNode(Min,node);
		//�ж��Ƿ�Ҫ�ƶ�Min��λ��
		if(node->key < Min->key)
			Min = node;
	}
	//����������
	n++;
}


//�ϲ������ѣ���̬��Ա����
template<class T>
MyFibHeap<T>* MyFibHeap<T>::heapunion(MyFibHeap<T>* H1,MyFibHeap<T>* H2){
	MyFibHeap<T>* H = new MyFibHeap<T>();
	H->Min = H1->Min;
	//��H2���ӵ�H�ϣ�ӦΪ�Ǿ�̬�������޷����÷Ǿ�̬��Ա������������������ӵĴ�����д��һ�飩
	H->Min->right->left = H2->Min->left;
	H2->Min->left->right = H->Min->right;
	H->Min->right = H2->Min;
	H2->Min->left = H->Min;
	//���²���
	if(H1->Min==NULL || (H2->Min!=NULL && H2->Min->key<H1->Min->key))
		H->Min = H2->Min;
	H->n = H1->n + H2->n;
	//Ϊ�˷�ֹͬһ�ڴ��α��ͷţ�ע���H1��H2��Min����ÿ�
	H1->Min = NULL;
	H2->Min = NULL;
	//�ͷ�H1��H2���ڴ�
	delete H1;
	delete H2;
	return H;
}

//consolidate������������y�ӵ�x���棬��yΪx�ĺ���
template<class T>
void MyFibHeap<T>::heaplink(FibNode<T>* x,FibNode<T>* y){
	//�Ȱ�y������ɾ��
	cutNode(y);
	//Ȼ�����ȥ
	if(x->child == NULL){
		x->child = y;
	}else{
		addNode(x->child,y);
	}
	//����x,y����
	y->p = x;
	x->degree++;
	x->mark = false;
}

//��ȡ��С��㸨������
template<class T>
void MyFibHeap<T>::consolidate(){
	//����Ҫ����A�Ŀռ�
	maxDegree = (log(n)/log(2.0)) + 1;
	FibNode<T>** A = new FibNode<T>*[maxDegree+1];
	//��A��ÿ��Ԫ���ÿ�
	for(int i=0;i<maxDegree+1;i++){
		A[i] = NULL;
	}
	//��������㣬�ϲ���ͬ�ȵĽ��
	FibNode<T>* x;
	FibNode<T>* y;
	int d;
	while(Min != NULL){
		x = Min;
		if(x == x->right){
			Min = NULL;
		}else{
			cutNode(x);
			Min = x->right;
			x->left = x->right = x;  //�ջ�
		}
		d = x->degree;       //��ȡ���Ķ�
		while(A[d] != NULL){ //��������ж�����ʱ
			y = A[d];        //ȡ����һ��������ͬ�ȵĽ��
			if(x->key > y->key)
				swap(x,y);
			heaplink(x,y);   //ʹy��Ϊx�ĺ���
			A[d] = NULL;     //�ÿյ�ǰ��
			d++;             //�ȼ�һ
		}
		A[d] = x;            //���º�Ķ�ָ��x
	}

	//Ȼ��ż�ع�������
	Min = NULL;
	for(int i=0;i<maxDegree+1;i++){
		if(A[i] != NULL){
			if(Min == NULL){
				Min = A[i];
			}else{
				addNode(Min,A[i]);
				if((A[i])->key < Min->key)
					Min = A[i];
			}
		}
	}
	//�ͷ�A�Ŀռ�
	delete[] A;
}

//��ȡ��С���
template<class T>
T MyFibHeap<T>::extractMin(){
	if(Min == NULL)
		return (T)-99999;
	FibNode<T>* z = Min;
	FibNode<T>* child;
	if(z != NULL){
		//��z��ÿһ�����ӷŵ���������
		while(z->child != NULL){
			child = z->child;
			cutNode(child);  //�Ƚ����������Ƴ����������Ѿ�û��child�ˣ���child������ָ�뻹ָ��������
			//����childû�������ֵܵ����
			if(child->left == child){
				//ֱ�Ӱ�z�ĺ����ÿ�
				z->child = NULL;
			}else{
				//����Ļ�����child�����ֵܵ���z�ĺ���
				z->child = child->left;
			}
			//����child�Ĳ���
			child->p = NULL;
			//Ȼ���ٰ�child���ӵ��������
			addNode(Min,child);
		}

		//��z�Ӹ�������ɾ��
		cutNode(z);

		//����Minֻ��z��һ���������������
		if(z == z->right){
			Min = NULL;
		}else{   //�������Min��ָ��x
			Min = z->right;
			//���ø�������consolidate
			consolidate();
		}

		//���¶Ѳ���
		n--;
	}
	//������С���
	T keytemp = z->key;
	//�ͷŽ���ڴ�
	delete z;
	return keytemp;
}

//��ӡ��
template<class T>
void MyFibHeap<T>::print(FibNode<T> *node, FibNode<T> *prev, int direction){
	if(node == NULL)
		return;
	FibNode<T>* p = node;
	do{
		if(direction == 1){
			cout<<setw(8)<<node->key<<"("<<node->degree<<")is"<<setw(2)<<prev->key<<"'s child"<<endl;
		}else{
			cout<<setw(8)<<node->key<<"("<<node->degree<<")is"<<setw(2)<<prev->key<<"'s next"<<endl;
		}
		if(node->child != NULL){
			print(node->child,node,1);
		}
		prev = node;
		node = node->right;
		direction = 2;
	}while(node != p);

}

//��ӡ�����ӿڣ�
template<class T>
void MyFibHeap<T>::print(){
	int i = 0;
	FibNode<T>* p;
	if(Min == NULL)
		return;
	p = Min;
	do{
		i++;
		cout<<setw(2)<<i<<"."<<setw(4)<<p->key<<"("<<p->degree<<") is root"<<endl;
		print(p->child,p,1);
		p = p->right;
	}while(p != Min);
	cout<<endl;
}

//�ͷŽ���ڴ�
template<class T>
void MyFibHeap<T>::clearNode(FibNode<T>* root){
	if(root == NULL)
		return;
	FibNode<T>* start = root;
	do{
		clearNode(root->child);
		root = root->right;
		delete root->left;
	}while(root != start);
}

//�ͷŽ���ڴ棨�ӿڣ�
template<class T>
void MyFibHeap<T>::clearNode(){
	clearNode(Min);
	cout<<"�ͷŽ���ڴ�ɹ�"<<endl;
}

//Ѱ�Ҽ�ֵΪval�Ľ��
template<class T>
FibNode<T>* MyFibHeap<T>::findNode(FibNode<T>*root,T val){
	if(root == NULL)
		return NULL;
	FibNode<T>* start = root;
	FibNode<T>* temp;
	do{
		if(start->key == val){
			return start;
		}else{
			temp = findNode(start->child,val);
			if(temp != NULL)
				return temp;
			start = start->right;
		}
	}while(start != root);
	return NULL;
}

//Ѱ�Ҽ�ֵΪval�Ľ�㣨�ӿڣ�
template<class T>
FibNode<T>* MyFibHeap<T>::findNode(T val){
	return findNode(Min,val);
}

//�ؼ��ּ�ֵ��������cut
template<class T>
void MyFibHeap<T>::cut(FibNode<T>* x,FibNode<T>* y){
	//��x�������������
	cutNode(x);
	//����y
	if(x->right == x)
		y->child = NULL;
	else
		y->child = x->right;
	y->degree--;
	//�ٰ�x�ӵ���������
	addNode(Min,x);
	x->p = NULL;
	x->mark = false;
}

//�ؼ��ּ�ֵ��������cascading_cut�������жϣ�
template<class T>
void MyFibHeap<T>::cascading_cut(FibNode<T>* y){
	FibNode<T>* z = y->p;
	if(z != NULL){
		if(y->mark == false){
			y->mark = true;
		}else{
			cut(y,z);
			cascading_cut(z);
		}
	}
}

//�ؼ��ּ�ֵ
template<class T>
void MyFibHeap<T>::decreaseKey(FibNode<T>* x,T k){
	if(k > x->key){
		cout<<"�ؼ��ֱȵ�ǰ��"<<endl;
		return;
	}
	x->key = k;
	FibNode<T>* y = x->p;
	if(y!=NULL && x->key<y->key){  //����ȸ����ļ�ֵС������Ҫ����
		cut(x,y);
		cascading_cut(y);
	}
	if(x->key < Min->key)
		Min = x;
}

//ɾ�����
template<class T>
void MyFibHeap<T>::removeNode(FibNode<T>* x){
	decreaseKey(x,(T)-99999);
	extractMin();
}

#endif /* MYFIBHEAP_H_ */
