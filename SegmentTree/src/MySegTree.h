/*
 * MySegTree.h
 *
 *  Created on: 2017年1月20日
 *      Author: Cedric
 */

#ifndef SRC_MYSEGTREE_H_
#define SRC_MYSEGTREE_H_

#include<vector>
#include<cmath>
using namespace std;

//定义线段树结点
struct STNode{
	int val;     //值
	int addMark;    //延迟标记
};

//线段树
class MySegTree{
public:
	MySegTree(int size);
	~MySegTree();

	void bulid(int i_start,int i_end,const vector<int>& arr);
	void print();
	int query(int q_start,int q_end);
	void updateSigle(int index,int addVal);
	void upadteSection(int q_start,int q_end,int addVal);
private:
	int size;    //矩阵的长度
	int TreeSize;   //建立线段树的结点个数
	vector<STNode> SegTree;

	void bulid(int root,int i_start,int i_end,const vector<int>& arr);
	int query(int root,int i_srart,int i_end,int q_start,int q_end);
	void updateSigle(int root,int i_start,int i_end,int index,int addVal);
	void pushdown(int root);
	void updateSection(int root,int i_start,int i_end,int q_start,int q_end,int addVal);
};

//构造
MySegTree::MySegTree(int size):size(size){
	TreeSize = pow(2,ceil(log(size)/log(2))+1);//叶结点N个，实际上线段数的总结点应该为2N-1个，考虑到以堆存储，则应取比2N-1大的最小的2的幂级数
	SegTree.resize(TreeSize);
}

//析构
MySegTree::~MySegTree(){
}

//建立线段树
void MySegTree::bulid(int root,int i_start,int i_end,const vector<int>& arr){
	//初始增值标记位
	SegTree[root].addMark = 0;
	//叶结点处理
	if(i_start == i_end){
		SegTree[root].val = arr[i_start];
	}else{ //父结点的值
		int mid = (i_start + i_end) / 2;
		bulid(root*2+1,i_start,mid,arr);   //左子树
		bulid(root*2+2,mid+1,i_end,arr);   //右子树
		SegTree[root].val = min(SegTree[2*root+1].val,SegTree[2*root+2].val);
	}
}

void MySegTree::bulid(int i_start,int i_end,const vector<int>& arr){
	bulid(0,i_start,i_end,arr);
}

//打印
void MySegTree::print(){
	for(int i=0;i<TreeSize;i++){
		cout<<SegTree[i].val<<"  ";
	}
	cout<<endl;
}

//查询
int MySegTree::query(int root,int i_start,int i_end,int q_start,int q_end){
	//当前节点区间[i_start,i_end]，查询区间[q_start,q_end]
	//如果当前区间包含在查询区间内，则直接返回当前根的值
	if(i_start>=q_start && i_end<=q_end){
		return SegTree[root].val;
	}
	//如果当前区间与查询区间没有交集，则返回99999
	if(q_start>i_end || q_end<i_start){
		return 99999;
	}
	pushdown(root);
	//否则，左右子树查询，返回查询结果的较小值
	int mid = (i_start + i_end) / 2;
	return min(query(2*root+1,i_start,mid,q_start,q_end),query(2*root+2,mid+1,i_end,q_start,q_end));
}

int MySegTree::query(int q_start,int q_end){
	return query(0,0,size-1,q_start,q_end);
}

//增加单节点的值
void MySegTree::updateSigle(int root,int i_start,int i_end,int index,int addVal){
	//找到位置更新
	if(i_start == i_end){
		if(i_start == index){
			SegTree[root].val += addVal;
			return;
		}
	}
	//否则从左右子树找
	int mid = (i_start+i_end)/2;
	if(index <= mid){
		updateSigle(2*root+1,i_start,mid,index,addVal);
	}else{
		updateSigle(2*root+2,mid+1,i_end,index,addVal);
	}
	//回溯更新
	SegTree[root].val = min(SegTree[2*root+1].val,SegTree[2*root+2].val);
}

void MySegTree::updateSigle(int index,int addVal){
	updateSigle(0,0,size-1,index,addVal);
}

//延迟标记下沉
void MySegTree::pushdown(int root){
	if(SegTree[root].addMark != 0){
		//更新左右孩子的延迟标记
		SegTree[2*root+1].addMark += SegTree[root].addMark;
		SegTree[2*root+2].addMark += SegTree[root].addMark;
		//更新做右孩子的值
		SegTree[2*root+1].val += SegTree[root].addMark;
		SegTree[2*root+2].val += SegTree[root].addMark;
		//root标记清空
		SegTree[root].addMark = 0;
	}
}

//更新区间
void MySegTree::updateSection(int root,int i_start,int i_end,int q_start,int q_end,int addVal){
	//当前区间包含在更新区间内
	if(i_start>=q_start && i_end<=q_end){
		SegTree[root].addMark += addVal;
		SegTree[root].val += addVal;
		return;
	}
	//没有交集返回
	if(i_start>q_end || i_end<i_start)
		return;
	pushdown(root);
	//更新左右孩子
	int mid = (i_start+i_end)/2;
	updateSection(2*root+1,i_start,mid,q_start,q_end,addVal);
	updateSection(2*root+2,mid+1,i_end,q_start,q_end,addVal);
	//回溯
	SegTree[root].val = min(SegTree[2*root+1].val,SegTree[2*root+2].val);
}

void MySegTree::upadteSection(int q_start,int q_end,int addVal){
	updateSection(0,0,size-1,q_start,q_end,addVal);
}

#endif /* SRC_MYSEGTREE_H_ */
