/*
 * test_for_SegTree.cpp
 *
 *  Created on: 2017年1月20日
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
	cout<<"建立线段树并打印："<<endl;
	test1.bulid(0,size-1,arr);
	test1.print();
	cout<<"查询[0,3]区间内的最小值："<<endl;
	cout<<test1.query(0,3)<<endl;
	cout<<"更新单节点的值（把第三个值1变成8）"<<endl;
	test1.updateSigle(2,7);
	cout<<"查询[0,3]区间内的最小值："<<endl;
	cout<<test1.query(0,3)<<endl;
	cout<<"更新区间[0,3]的值，全部加1"<<endl;
	test1.upadteSection(0,3,1);
	cout<<"查询[0,3]区间内的最小值："<<endl;
	cout<<test1.query(0,3)<<endl;

	return 0;
}



