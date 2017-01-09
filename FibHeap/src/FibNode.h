/*
 * FibNode.h
 *
 *  Created on: 2017��1��6��
 *      Author: Cedric
 */

#ifndef FIBNODE_H_
#define FIBNODE_H_

#include<stddef.h>

//����쳲������ѽ��
template<class T>
struct FibNode{
	T key;              //ֵ
	int degree;         //��
	FibNode<T>* p;      //��ָ��
	FibNode<T>* child;  //����ָ��
	FibNode<T>* left;   //���ֵ�
	FibNode<T>* right;  //���ֵ�
	bool mark;          //���

	FibNode(T value):key(value),degree(0),p(NULL),child(NULL),left(this),right(this),mark(false){
	}

};



#endif /* FIBNODE_H_ */
