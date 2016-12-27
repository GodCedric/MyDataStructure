#ifndef __MYHEAP__H__
#define __MYHEAP__H__

//维护堆 时间复杂度O(lgn)
template<class RandomAccessIterator>
void Max_Heapify(RandomAccessIterator first,RandomAccessIterator last,int i){
	int n = last - first;
	int left = 2*i;
	int right = 2*i + 1;
	int largest = i;
	if(left <= n && *(first+left-1)>*(first+i-1))
		largest = left;
	if(right <=n && *(first+right-1)>*(first+largest-1))
		largest = right;
	if(i != largest){
		iter_swap(first+i-1,first+largest-1);
		Max_Heapify(first,last,largest);
	}
} 

//构造堆 时间复杂度O(n)
template<class RandomAccessIterator>
void Build_Max_Heap(RandomAccessIterator first,RandomAccessIterator last){
	int n = last - first;
	for(size_t i=n/2;i>0;i--){
		Max_Heapify(first,last,i);
	}
}

//堆排序 时间复杂度O(nlgn)
template<class RandomAccessIterator>
void heap_sort(RandomAccessIterator first,RandomAccessIterator last){
	Build_Max_Heap(first,last);
	RandomAccessIterator tempEnd = last-1;
	while(tempEnd - first > 0){
		iter_swap(first,tempEnd);
		Max_Heapify(first,tempEnd,1);
		tempEnd--;
	}
}

#endif