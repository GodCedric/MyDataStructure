#ifndef __MYSTACK_H__
#define __MYSTACK_H__

template<class T>
class MyStack{
public:
	MyStack(int n):n(n),top(NULL){
		arr = new T[n];
	}
	~MyStack(){
		delete[] arr;
	}
	bool empty();
	T push(T x);
	T pop();

private:
	int n;
	int* top;
	int* arr;
};

template<class T>
bool MyStack<T>::empty(){
	if(top == NULL)
		return true;
	else
		return false;
}

template<class T>
T MyStack<T>::push(T x){
	if(top == &arr[n-1])
		return 0;    //越上界返回0
	if(top == NULL){
		top = arr;
		*top = x;
	}else{
		top++;
		*top = x;
	}
	return *top;
}

template<class T>
T MyStack<T>::pop(){
	if(top == NULL)
		return 0;   //越下界返回0
	if(top == &arr[0]){
		top = NULL;
		return arr[0];
	}
	T temp = *top;
	top--;
	return temp;;
}


#endif
