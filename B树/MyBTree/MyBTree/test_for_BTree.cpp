#include<iostream>
#include"MyBTree.h"

using namespace std;

int main(){
	cout<<endl;
	cout<<"B��"<<endl;
	MyBTree<char> bt;
	bt.insert('G');
	bt.insert('M');
	bt.insert('P');
	bt.insert('X');
	bt.insert('A');
	bt.insert('C');
	bt.insert('D');
	bt.insert('E');
	bt.insert('J');
	bt.insert('K');
	bt.insert('N');
	bt.insert('O');
	bt.insert('R');

	cout<<"����ؼ��ֺ��ӡ����"<<endl;
	bt.print_tree();
	cout<<"Ѱ�ҹؼ���'A'��"<<endl;
	if(bt.search('A'))
		cout<<"�ҵ��ˣ�"<<endl;
	cout<<"ɾ���ؼ���'A'��"<<endl;
	if(bt.remove('A'))
		cout<<"ɾ���ˣ�"<<endl;
	cout<<"ɾ�����ӡ����"<<endl;
	bt.print_tree();
	return 0;

}