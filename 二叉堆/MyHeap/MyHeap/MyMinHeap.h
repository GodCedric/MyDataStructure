#ifndef __MYMINHEAP__H__
#define __MYMINHEAP__H__

//��С��
template<class T>
class MyMinHeap{
public:
	MyMinHeap(int size);
	~MyMinHeap();

	int getIndex(T data);    //��������
	bool insert(T data);      //����Ԫ��
	void print();            //�����
	bool remove(T data);      //ɾ��Ԫ��

private:
	T* mHeap;    //����
	int maxNum;  //���洢����
	int curNum;  //��ǰ�洢����

	void filterup(int cur);    //�Ե�����ά���ѵ����ʣ����ڲ���
	void filterdown(int cur);  //�Զ�����ά���ѵ����ʣ�����ɾ��
};

//��������
template<class T>
MyMinHeap<T>::MyMinHeap(int size):maxNum(size){
	curNum = 0;
	mHeap = new T[size];
}

template<class T>
MyMinHeap<T>::~MyMinHeap(){
	maxNum = 0;
	curNum = 0;
	delete[] mHeap;
}

//����Ԫ������
template<class T>
int MyMinHeap<T>::getIndex(T data){
	for(int i=0;i<curNum;i++){
		if(mHeap[i] == data)
			return i;
	}
	return -1;
}

//����Ԫ��
template<class T>
bool MyMinHeap<T>::insert(T data){
	//���˷���-1
	if(curNum == maxNum)
		return false;
	//�Ȳ�������ĩβ
	mHeap[curNum] = data;
	//������
	filterup(curNum);
	curNum++;
	return true;
}

///�Ե�����ά���ѵ�����
template<class T>
void MyMinHeap<T>::filterup(int cur){
	int parent = (cur-1)/2;
	T temp = mHeap[cur];   //�ȱ�����Ҫ�����ֵ
	//Ѱ����Ҫ�����λ��
	while(cur){
		//�ȽϽ���븸���Ĵ�С
		if(mHeap[parent] <= temp){  //�����Ƚ�С���ö�
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

//�����
template<class T>
void MyMinHeap<T>::print(){
	for(int i=0;i<curNum;i++){
		cout<<mHeap[i]<<" ";
	}
	cout<<endl;
}

//ɾ��Ԫ��
template<class T>
bool MyMinHeap<T>::remove(T data){
	int cur = getIndex(data);
	//��ȷ���Ƿ������Ԫ��
	if(cur == -1)
		return false;
	//�����һ��Ԫ�طŵ����λ�ã�����СԪ�ظ���
	mHeap[cur] = mHeap[--curNum];
	//�Զ�����ά����
	filterdown(cur);
	return true;
} 

//�Զ�����ά����
template<class T>
void MyMinHeap<T>::filterdown(int cur){
	int lchild = 2*cur+1;  //����
	T temp = mHeap[cur];   //�ȴ�ֵ
	while(lchild <= curNum-1){
		if(lchild < curNum-1){   //ѡ�����Һ����бȽ�С���Ǹ�
			if(mHeap[lchild] > mHeap[lchild+1])
				lchild++;
		}
		if(mHeap[cur] <= mHeap[lchild]){
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

#endif