/*
 * test_for_SegTree.cpp
 *
 *  Created on: 2017��1��20��
 *      Author: Cedric
 */
#include<iostream>
#include"MySegTree.h"

using namespace std;

int main(){

	int arr1[6] = {2,5,1,4,9,3};
	vector<int> arr(arr1,arr1+6);
	int size = 6;
	MySegTree test1(size);
	cout<<"�����߶�������ӡ��"<<endl;
	test1.bulid(0,size-1,arr);
	test1.print();
	cout<<"��ѯ[0,3]�����ڵ���Сֵ��"<<endl;
	cout<<test1.query(0,3)<<endl;
	cout<<"���µ��ڵ��ֵ���ѵ�����ֵ1���8��"<<endl;
	test1.updateSigle(2,7);
	cout<<"��ѯ[0,3]�����ڵ���Сֵ��"<<endl;
	cout<<test1.query(0,3)<<endl;
	cout<<"��������[0,3]��ֵ��ȫ����1"<<endl;
	test1.upadteSection(0,3,1);
	cout<<"��ѯ[0,3]�����ڵ���Сֵ��"<<endl;
	cout<<test1.query(0,3)<<endl;

	return 0;
}



