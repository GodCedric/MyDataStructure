#ifndef __MYMINHEAP__H__
#define __MYMINHEAP__H__

////���ǵ���������������Ҫ�����ҳ�Ȩֵ��С��������㣬��˸ĳ�һ����ԱֵΪ��������������С��
//������
template<class T>
struct Node{
	T data;
	Node* parent;
	Node* lchild;
	Node* rchild;

	Node(){}
	Node(T data):data(data),parent(NULL),lchild(NULL),rchild(NULL){}
};

//��С��
template<class T>
class MyMinHeap{
public:
	MyMinHeap(int size);
	~MyMinHeap();

	bool insert(Node<T>* NewNode);    //����Ԫ��
	Node<T>* pop();                  //�����Ѷ�

private:
	Node<T>* mHeap;    //����
	int maxNum;  //���洢����
	int curNum;  //��ǰ�洢����

	void filterup(int cur);    //�Ե�����ά���ѵ����ʣ����ڲ���
	void filterdown(int cur);  //�Զ�����ά���ѵ����ʣ�����ɾ��
};

//��������
template<class T>
MyMinHeap<T>::MyMinHeap(int size){
	maxNum = size;
	curNum = 0;
	mHeap = new Node<T>[size];  
}

template<class T>
MyMinHeap<T>::~MyMinHeap(){
	maxNum = 0;
	curNum = 0;
	delete[] mHeap;
}

//����Ԫ��
template<class T>
bool MyMinHeap<T>::insert(Node<T>* NewNode){
	//���˷���-1
	if(curNum == maxNum)
		return false;
	//�Ȳ�������ĩβ
	mHeap[curNum] = *NewNode;
	//������
	filterup(curNum);
	curNum++;
	return true;
}

///�Ե�����ά���ѵ�����
template<class T>
void MyMinHeap<T>::filterup(int cur){
	int parent = (cur-1)/2;
	Node<T> temp = mHeap[cur];   //�ȱ�����Ҫ�����ֵ
	//Ѱ����Ҫ�����λ��
	while(cur){
		//�ȽϽ���븸���Ĵ�С
		if(mHeap[parent].data <= temp.data){  //�����Ƚ�С���ö�
			break;
		}else{                              //�����Ƚ�С��Ҫ����λ��
			mHeap[cur] = mHeap[parent];
			cur = parent;
			parent = (cur-1)/2;
		}	
	}
	//����ֵ
	mHeap[cur] = temp;
	
	return;
}

//�Զ�����ά����
template<class T>
void MyMinHeap<T>::filterdown(int cur){
	int lchild = 2*cur+1;  //����
	Node<T> temp = mHeap[cur];   //�ȴ�ֵ
	while(lchild <= curNum-1){
		if(lchild < curNum-1){   //ѡ�����Һ����бȽ�С���Ǹ�
			if(mHeap[lchild].data > mHeap[lchild+1].data)
				lchild++;
		}
		if(mHeap[cur].data <= mHeap[lchild].data){
			break;
		}else{
			mHeap[cur] = mHeap[lchild];
			cur = lchild;
			lchild = 2*cur+1;
		}
	}
	mHeap[cur] = temp; 

	return;
}

//�����Ѷ�
template<class T>
Node<T>* MyMinHeap<T>::pop(){
	if(curNum == 0)
		return NULL;
	//�ȴ洢�Ѷ���ֵ
	Node<T>* temp = new Node<T>(0);
	*temp = mHeap[0];
	mHeap[0] = mHeap[curNum-1];
	curNum--;
	filterdown(0);
	return temp;
}

#endif