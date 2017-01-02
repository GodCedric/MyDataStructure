#ifndef __MYMINHEAP__H__
#define __MYMINHEAP__H__

//最小堆
template<class T>
class MyMinHeap{
public:
	MyMinHeap(int size);
	~MyMinHeap();

	int getIndex(T data);    //返回索引
	bool insert(T data);      //插入元素
	void print();            //输出堆
	bool remove(T data);      //删除元素

private:
	T* mHeap;    //数据
	int maxNum;  //最大存储个数
	int curNum;  //当前存储个数

	void filterup(int cur);    //自底向上维护堆的性质，用于插入
	void filterdown(int cur);  //自顶向下维护堆的性质，用于删除
};

//构造析构
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

//返回元素索引
template<class T>
int MyMinHeap<T>::getIndex(T data){
	for(int i=0;i<curNum;i++){
		if(mHeap[i] == data)
			return i;
	}
	return -1;
}

//插入元素
template<class T>
bool MyMinHeap<T>::insert(T data){
	//满了返回-1
	if(curNum == maxNum)
		return false;
	//先插入数组末尾
	mHeap[curNum] = data;
	//调整堆
	filterup(curNum);
	curNum++;
	return true;
}

///自底向上维护堆的性质
template<class T>
void MyMinHeap<T>::filterup(int cur){
	int parent = (cur-1)/2;
	T temp = mHeap[cur];   //先保存需要插入的值
	//寻找需要插入的位置
	while(cur){
		//比较结点与父结点的大小
		if(mHeap[parent] <= temp){  //父结点比较小不用动
			break;
		}else{                              //父结点比较小需要交换位置
			mHeap[cur] = mHeap[parent];
			cur = parent;
			parent = (cur-1)/2;
		}	
	}
	//插入值
	mHeap[cur] = temp;
	
	return;
}

//输出堆
template<class T>
void MyMinHeap<T>::print(){
	for(int i=0;i<curNum;i++){
		cout<<mHeap[i]<<" ";
	}
	cout<<endl;
}

//删除元素
template<class T>
bool MyMinHeap<T>::remove(T data){
	int cur = getIndex(data);
	//先确定是否包含此元素
	if(cur == -1)
		return false;
	//把最后一个元素放到这个位置，并减小元素个数
	mHeap[cur] = mHeap[--curNum];
	//自顶向下维护堆
	filterdown(cur);
	return true;
} 

//自顶向下维护堆
template<class T>
void MyMinHeap<T>::filterdown(int cur){
	int lchild = 2*cur+1;  //左孩子
	T temp = mHeap[cur];   //先存值
	while(lchild <= curNum-1){
		if(lchild < curNum-1){   //选择左右孩子中比较小的那个
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