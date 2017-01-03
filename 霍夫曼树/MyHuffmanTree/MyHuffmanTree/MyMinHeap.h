#ifndef __MYMINHEAP__H__
#define __MYMINHEAP__H__

////考虑到建立霍夫曼树需要不断找出权值最小的两个结点，因此改出一个成员值为霍夫曼树结点的最小堆
//定义结点
template<class T>
struct Node{
	T data;
	Node* parent;
	Node* lchild;
	Node* rchild;

	Node(){}
	Node(T data):data(data),parent(NULL),lchild(NULL),rchild(NULL){}
};

//最小堆
template<class T>
class MyMinHeap{
public:
	MyMinHeap(int size);
	~MyMinHeap();

	bool insert(Node<T>* NewNode);    //插入元素
	Node<T>* pop();                  //弹出堆顶

private:
	Node<T>* mHeap;    //数据
	int maxNum;  //最大存储个数
	int curNum;  //当前存储个数

	void filterup(int cur);    //自底向上维护堆的性质，用于插入
	void filterdown(int cur);  //自顶向下维护堆的性质，用于删除
};

//构造析构
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

//插入元素
template<class T>
bool MyMinHeap<T>::insert(Node<T>* NewNode){
	//满了返回-1
	if(curNum == maxNum)
		return false;
	//先插入数组末尾
	mHeap[curNum] = *NewNode;
	//调整堆
	filterup(curNum);
	curNum++;
	return true;
}

///自底向上维护堆的性质
template<class T>
void MyMinHeap<T>::filterup(int cur){
	int parent = (cur-1)/2;
	Node<T> temp = mHeap[cur];   //先保存需要插入的值
	//寻找需要插入的位置
	while(cur){
		//比较结点与父结点的大小
		if(mHeap[parent].data <= temp.data){  //父结点比较小不用动
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

//自顶向下维护堆
template<class T>
void MyMinHeap<T>::filterdown(int cur){
	int lchild = 2*cur+1;  //左孩子
	Node<T> temp = mHeap[cur];   //先存值
	while(lchild <= curNum-1){
		if(lchild < curNum-1){   //选择左右孩子中比较小的那个
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

//弹出堆顶
template<class T>
Node<T>* MyMinHeap<T>::pop(){
	if(curNum == 0)
		return NULL;
	//先存储堆顶的值
	Node<T>* temp = new Node<T>(0);
	*temp = mHeap[0];
	mHeap[0] = mHeap[curNum-1];
	curNum--;
	filterdown(0);
	return temp;
}

#endif