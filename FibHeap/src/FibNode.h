/*
 * FibNode.h
 *
 *  Created on: 2017年1月6日
 *      Author: Cedric
 */

#ifndef FIBNODE_H_
#define FIBNODE_H_

#include<stddef.h>

//定义斐波那契堆结点
template<class T>
struct FibNode{
	T key;              //值
	int degree;         //度
	FibNode<T>* p;      //父指针
	FibNode<T>* child;  //孩子指针
	FibNode<T>* left;   //左兄弟
	FibNode<T>* right;  //右兄弟
	bool mark;          //标记

	FibNode(T value):key(value),degree(0),p(NULL),child(NULL),left(this),right(this),mark(false){
	}

};



#endif /* FIBNODE_H_ */
