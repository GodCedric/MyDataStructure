/*
 * MyFibHeap.h
 *
 *  Created on: 2017年1月6日
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

//定义斐波那契堆
template<class T>
class MyFibHeap{
public:
	//构造析构
	MyFibHeap();
	~MyFibHeap();

	//插入结点
	void insert(T value);
	//输出当前堆的最小键值
	void printMin();
	//合并(将H合并到当前堆中)
	static MyFibHeap<T>* heapunion(MyFibHeap<T>* H1,MyFibHeap<T>* H2);
	//抽取最小结点键值
	T extractMin();
	//打印堆
	void print();
	//释放结点内存
	void clearNode();
	//寻找键值为k的结点
	FibNode<T>* findNode(T val);
	//关键字减值
	void decreaseKey(FibNode<T>* x,T k);
	//删除结点
	void removeNode(FibNode<T>* x);

private:
	FibNode<T>* Min;    //指向最小结点
	int n;              //结点个数
	int maxDegree;      //最大度
	//FibNode<T>** A;     //consolidate使用，记录根结点对应的度数的轨迹

	//把结点插到根链表中
	void addNode(FibNode<T>* min,FibNode<T>* node);
	//把结点从链表中剪切下来
	void cutNode(FibNode<T>* node);
	//抽取最小值辅助函数consolidate
	void consolidate();
	//consolidate辅助函数，把y接到x下面
	void heaplink(FibNode<T>* x,FibNode<T>* y);
	//打印堆
	void print(FibNode<T> *node, FibNode<T> *prev, int direction);
	//寻找键值为key的结点
	FibNode<T>* findNode(FibNode<T>* root,T val);
	//关键字减值辅助函数cut
	void cut(FibNode<T>* x,FibNode<T>* y);
	//关键字减值辅助函数cascading_cut
	void cascading_cut(FibNode<T>* y);
	//释放结点内存
	void clearNode(FibNode<T>* root);

};

//构造函数
template<class T>
MyFibHeap<T>::MyFibHeap(){
	Min = NULL;
	n = 0;
	maxDegree = 0;
}

//析构函数
template<class T>
MyFibHeap<T>::~MyFibHeap(){
	//防止用户忘记释放结点内存
	clearNode(Min);
}

//输出最小键值
template<class T>
void MyFibHeap<T>::printMin(){
	if(Min == NULL){
		cout<<"当前堆无结点！"<<endl;
		return;
	}else{
		cout<<Min->key<<endl;
		return;
	}
}

//把结点插到根链表中
template<class T>
void MyFibHeap<T>::addNode(FibNode<T>* min,FibNode<T>* node){
	node->left = min->left;
	min->left->right = node;
	min->left = node;
	node->right = min;
}

//把结点从链表中删除
template<class T>
void MyFibHeap<T>::cutNode(FibNode<T>* node){
	//对node结点的判断放到外面处理，由调用的成员函数考虑node为空的情况
	node->left->right = node->right;
	node->right->left = node->left;
}


//插入结点
template<class T>
void MyFibHeap<T>::insert(T value){
	//创建结点
	FibNode<T>* node = new FibNode<T>(value);
	//如果根链表为空，则Min指向node
	//如果根链表为空，则Min指向node
	if(Min == NULL){
		Min = node;
	}else{    //不为空则将node放到Min的左边
		addNode(Min,node);
		//判断是否要移动Min的位置
		if(node->key < Min->key)
			Min = node;
	}
	//结点个数增加
	n++;
}


//合并两个堆，静态成员函数
template<class T>
MyFibHeap<T>* MyFibHeap<T>::heapunion(MyFibHeap<T>* H1,MyFibHeap<T>* H2){
	MyFibHeap<T>* H = new MyFibHeap<T>();
	H->Min = H1->Min;
	//把H2链接到H上（应为是静态函数，无法调用非静态成员函数，所以这里把链接的代码又写了一遍）
	H->Min->right->left = H2->Min->left;
	H2->Min->left->right = H->Min->right;
	H->Min->right = H2->Min;
	H2->Min->left = H->Min;
	//更新参数
	if(H1->Min==NULL || (H2->Min!=NULL && H2->Min->key<H1->Min->key))
		H->Min = H2->Min;
	H->n = H1->n + H2->n;
	//为了防止同一内存多次被释放，注意把H1和H2的Min结点置空
	H1->Min = NULL;
	H2->Min = NULL;
	//释放H1和H2的内存
	delete H1;
	delete H2;
	return H;
}

//consolidate辅助函数，把y接到x下面，令y为x的孩子
template<class T>
void MyFibHeap<T>::heaplink(FibNode<T>* x,FibNode<T>* y){
	//先把y从链表删除
	cutNode(y);
	//然后接上去
	if(x->child == NULL){
		x->child = y;
	}else{
		addNode(x->child,y);
	}
	//更新x,y参数
	y->p = x;
	x->degree++;
	x->mark = false;
}

//抽取最小结点辅助函数
template<class T>
void MyFibHeap<T>::consolidate(){
	//首先要分配A的空间
	maxDegree = (log(n)/log(2.0)) + 1;
	FibNode<T>** A = new FibNode<T>*[maxDegree+1];
	//令A的每个元素置空
	for(int i=0;i<maxDegree+1;i++){
		A[i] = NULL;
	}
	//遍历根结点，合并相同度的结点
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
			x->left = x->right = x;  //闭环
		}
		d = x->degree;       //获取它的度
		while(A[d] != NULL){ //当这个度有多个结点时
			y = A[d];        //取出另一个具有相同度的结点
			if(x->key > y->key)
				swap(x,y);
			heaplink(x,y);   //使y成为x的孩子
			A[d] = NULL;     //置空当前度
			d++;             //度加一
		}
		A[d] = x;            //更新后的度指向x
	}

	//然后偶重构根链表
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
	//释放A的空间
	delete[] A;
}

//抽取最小结点
template<class T>
T MyFibHeap<T>::extractMin(){
	if(Min == NULL)
		return (T)-99999;
	FibNode<T>* z = Min;
	FibNode<T>* child;
	if(z != NULL){
		//把z的每一个孩子放到根链表中
		while(z->child != NULL){
			child = z->child;
			cutNode(child);  //先将结点从链表移除，链表中已经没有child了，但child的左右指针还指向链表中
			//考虑child没有左右兄弟的情况
			if(child->left == child){
				//直接把z的孩子置空
				z->child = NULL;
			}else{
				//否则的话，把child的左兄弟当做z的孩子
				z->child = child->left;
			}
			//更新child的参数
			child->p = NULL;
			//然后再把child链接到根结点中
			addNode(Min,child);
		}

		//把z从根链表中删除
		cutNode(z);

		//考虑Min只有z这一个单结点的特殊情况
		if(z == z->right){
			Min = NULL;
		}else{   //否则更新Min的指向x
			Min = z->right;
			//调用辅助函数consolidate
			consolidate();
		}

		//更新堆参数
		n--;
	}
	//返回最小结点
	T keytemp = z->key;
	//释放结点内存
	delete z;
	return keytemp;
}

//打印树
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

//打印树（接口）
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

//释放结点内存
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

//释放结点内存（接口）
template<class T>
void MyFibHeap<T>::clearNode(){
	clearNode(Min);
	cout<<"释放结点内存成功"<<endl;
}

//寻找减值为val的结点
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

//寻找减值为val的结点（接口）
template<class T>
FibNode<T>* MyFibHeap<T>::findNode(T val){
	return findNode(Min,val);
}

//关键字减值辅助函数cut
template<class T>
void MyFibHeap<T>::cut(FibNode<T>* x,FibNode<T>* y){
	//把x从链表剪切下来
	cutNode(x);
	//更新y
	if(x->right == x)
		y->child = NULL;
	else
		y->child = x->right;
	y->degree--;
	//再把x加到根链表中
	addNode(Min,x);
	x->p = NULL;
	x->mark = false;
}

//关键字减值辅助函数cascading_cut（级联切断）
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

//关键字减值
template<class T>
void MyFibHeap<T>::decreaseKey(FibNode<T>* x,T k){
	if(k > x->key){
		cout<<"关键字比当前大！"<<endl;
		return;
	}
	x->key = k;
	FibNode<T>* y = x->p;
	if(y!=NULL && x->key<y->key){  //如果比父结点的键值小，则需要调整
		cut(x,y);
		cascading_cut(y);
	}
	if(x->key < Min->key)
		Min = x;
}

//删除结点
template<class T>
void MyFibHeap<T>::removeNode(FibNode<T>* x){
	decreaseKey(x,(T)-99999);
	extractMin();
}

#endif /* MYFIBHEAP_H_ */
