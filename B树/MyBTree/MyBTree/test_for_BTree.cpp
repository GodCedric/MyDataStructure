#include<iostream>
#include"MyBTree.h"

using namespace std;

int main(){
	cout<<endl;
	cout<<"BÊ÷"<<endl;
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

	cout<<"²åÈë¹Ø¼ü×Öºó´òÓ¡Ê÷£º"<<endl;
	bt.print_tree();
	cout<<"Ñ°ÕÒ¹Ø¼ü×Ö'A'£º"<<endl;
	if(bt.search('A'))
		cout<<"ÕÒµ½ÁË£¡"<<endl;
	cout<<"É¾³ı¹Ø¼ü×Ö'A'£º"<<endl;
	if(bt.remove('A'))
		cout<<"É¾³ıÁË£¡"<<endl;
	cout<<"É¾³ıºó´òÓ¡Ê÷£º"<<endl;
	bt.print_tree();
	return 0;

}