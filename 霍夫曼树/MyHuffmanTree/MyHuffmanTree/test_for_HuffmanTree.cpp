#include<iostream>
#include"MyHuffmanTree.h"

using namespace std;

int main(){
	cout<<"霍夫曼树："<<endl;
	MyHuffmanTree<int> mHT;
	mHT.creatHuffmanTree();
	cout<<"霍夫曼树建立成功，显示树："<<endl;
	mHT.printTree();
	cout<<"树的前序遍历："<<endl;
	mHT.preOrder();
	cout<<"树的中序遍历："<<endl;
	mHT.inOrder();
	cout<<"树的后序遍历："<<endl;
	mHT.postOrder();
	cout<<"清空树：";
	mHT.clearTree();

	return 0;
}