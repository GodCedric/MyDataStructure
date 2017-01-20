/*
 * MySegTree.h
 *
 *  Created on: 2017��1��20��
 *      Author: Cedric
 */

#ifndef SRC_MYSEGTREE_H_
#define SRC_MYSEGTREE_H_

#include<vector>
#include<cmath>
using namespace std;

//�����߶������
struct STNode{
	int val;     //ֵ
	int addMark;    //�ӳٱ��
};

//�߶���
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
	int size;    //����ĳ���
	int TreeSize;   //�����߶����Ľ�����
	vector<STNode> SegTree;

	void bulid(int root,int i_start,int i_end,const vector<int>& arr);
	int query(int root,int i_srart,int i_end,int q_start,int q_end);
	void updateSigle(int root,int i_start,int i_end,int index,int addVal);
	void pushdown(int root);
	void updateSection(int root,int i_start,int i_end,int q_start,int q_end,int addVal);
};

//����
MySegTree::MySegTree(int size):size(size){
	TreeSize = pow(2,ceil(log(size)/log(2))+1);//Ҷ���N����ʵ�����߶������ܽ��Ӧ��Ϊ2N-1�������ǵ��ԶѴ洢����Ӧȡ��2N-1�����С��2���ݼ���
	SegTree.resize(TreeSize);
}

//����
MySegTree::~MySegTree(){
}

//�����߶���
void MySegTree::bulid(int root,int i_start,int i_end,const vector<int>& arr){
	//��ʼ��ֵ���λ
	SegTree[root].addMark = 0;
	//Ҷ��㴦��
	if(i_start == i_end){
		SegTree[root].val = arr[i_start];
	}else{ //������ֵ
		int mid = (i_start + i_end) / 2;
		bulid(root*2+1,i_start,mid,arr);   //������
		bulid(root*2+2,mid+1,i_end,arr);   //������
		SegTree[root].val = min(SegTree[2*root+1].val,SegTree[2*root+2].val);
	}
}

void MySegTree::bulid(int i_start,int i_end,const vector<int>& arr){
	bulid(0,i_start,i_end,arr);
}

//��ӡ
void MySegTree::print(){
	for(int i=0;i<TreeSize;i++){
		cout<<SegTree[i].val<<"  ";
	}
	cout<<endl;
}

//��ѯ
int MySegTree::query(int root,int i_start,int i_end,int q_start,int q_end){
	//��ǰ�ڵ�����[i_start,i_end]����ѯ����[q_start,q_end]
	//�����ǰ��������ڲ�ѯ�����ڣ���ֱ�ӷ��ص�ǰ����ֵ
	if(i_start>=q_start && i_end<=q_end){
		return SegTree[root].val;
	}
	//�����ǰ�������ѯ����û�н������򷵻�99999
	if(q_start>i_end || q_end<i_start){
		return 99999;
	}
	pushdown(root);
	//��������������ѯ�����ز�ѯ����Ľ�Сֵ
	int mid = (i_start + i_end) / 2;
	return min(query(2*root+1,i_start,mid,q_start,q_end),query(2*root+2,mid+1,i_end,q_start,q_end));
}

int MySegTree::query(int q_start,int q_end){
	return query(0,0,size-1,q_start,q_end);
}

//���ӵ��ڵ��ֵ
void MySegTree::updateSigle(int root,int i_start,int i_end,int index,int addVal){
	//�ҵ�λ�ø���
	if(i_start == i_end){
		if(i_start == index){
			SegTree[root].val += addVal;
			return;
		}
	}
	//���������������
	int mid = (i_start+i_end)/2;
	if(index <= mid){
		updateSigle(2*root+1,i_start,mid,index,addVal);
	}else{
		updateSigle(2*root+2,mid+1,i_end,index,addVal);
	}
	//���ݸ���
	SegTree[root].val = min(SegTree[2*root+1].val,SegTree[2*root+2].val);
}

void MySegTree::updateSigle(int index,int addVal){
	updateSigle(0,0,size-1,index,addVal);
}

//�ӳٱ���³�
void MySegTree::pushdown(int root){
	if(SegTree[root].addMark != 0){
		//�������Һ��ӵ��ӳٱ��
		SegTree[2*root+1].addMark += SegTree[root].addMark;
		SegTree[2*root+2].addMark += SegTree[root].addMark;
		//�������Һ��ӵ�ֵ
		SegTree[2*root+1].val += SegTree[root].addMark;
		SegTree[2*root+2].val += SegTree[root].addMark;
		//root������
		SegTree[root].addMark = 0;
	}
}

//��������
void MySegTree::updateSection(int root,int i_start,int i_end,int q_start,int q_end,int addVal){
	//��ǰ��������ڸ���������
	if(i_start>=q_start && i_end<=q_end){
		SegTree[root].addMark += addVal;
		SegTree[root].val += addVal;
		return;
	}
	//û�н�������
	if(i_start>q_end || i_end<i_start)
		return;
	pushdown(root);
	//�������Һ���
	int mid = (i_start+i_end)/2;
	updateSection(2*root+1,i_start,mid,q_start,q_end,addVal);
	updateSection(2*root+2,mid+1,i_end,q_start,q_end,addVal);
	//����
	SegTree[root].val = min(SegTree[2*root+1].val,SegTree[2*root+2].val);
}

void MySegTree::upadteSection(int q_start,int q_end,int addVal){
	updateSection(0,0,size-1,q_start,q_end,addVal);
}

#endif /* SRC_MYSEGTREE_H_ */
