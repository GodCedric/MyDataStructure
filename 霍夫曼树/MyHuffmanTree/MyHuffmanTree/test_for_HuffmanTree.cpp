#include<iostream>
#include"MyHuffmanTree.h"

using namespace std;

int main(){
	cout<<"����������"<<endl;
	MyHuffmanTree<int> mHT;
	mHT.creatHuffmanTree();
	cout<<"�������������ɹ�����ʾ����"<<endl;
	mHT.printTree();
	cout<<"����ǰ�������"<<endl;
	mHT.preOrder();
	cout<<"�������������"<<endl;
	mHT.inOrder();
	cout<<"���ĺ��������"<<endl;
	mHT.postOrder();
	cout<<"�������";
	mHT.clearTree();

	return 0;
}