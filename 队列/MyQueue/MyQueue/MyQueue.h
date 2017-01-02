#ifndef __MYQUEUE__H__
#define __MYQUEUE__H__

template<class T>
class MyQueue{
public:
	MyQueue(int n):n(n){
		arr = new T[n];
		head = &arr[n/2];
		tail = &arr[n/2];
	}
	~MyQueue(){
		delete[] arr;
	}
	bool empty();
	T enqueue(T x);
	T dequeue();
private:
	int n;
	T* arr;
	T* head;
	T* tail;
};

template<class T>
bool MyQueue<T>::empty(){
	if(head == tail)
		return true;
	else
		return false;
}

template<class T>
T MyQueue<T>::enqueue(T x){
	if(head == tail+1)
		return 0;  //越上界返回0
	if(tail == &arr[n-1]){
		tail = &arr[0];
		*tail = x;
	}else{
		*tail = x;
		tail++;
	}
	return *tail;
}

template<class T>
T MyQueue<T>::dequeue(){
	if(head == tail)
		return 0;   //越下界返回0
	if(head == &arr[n-1]){
		T temp = *head;
		head = &arr[0];
		return temp;
	}else{
		T temp = *head;
		head++;
		return temp;
	}
}

#endif