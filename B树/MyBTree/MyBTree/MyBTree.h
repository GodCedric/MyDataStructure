#ifndef __MYBTREE__H__
#define __MYBTREE__H__

static const int t = 3;                  //最小度数>=2/关键字类型

template<class KeyType>  
struct BTreeNode{
	int n;                    //关键字个数
	KeyType key[2*t-1];     //关键字矩阵
	bool leaf;                //是否叶结点
	BTreeNode* c[2*t];       //孩子指针矩阵

	BTreeNode(int n=0,bool leaf=true):n(n),leaf(leaf){}   //初始默认为叶结点
};


template<class KeyType>   
class MyBTree{
public:
	MyBTree(){Root = NULL;}     //构造函数
	~MyBTree(){}                //析构函数

	//接口函数
	bool search(KeyType key);                                  //搜索B树
	bool insert(const KeyType& key);                           //插入关键字
	void clear();                                              //清空树
	bool remove(const KeyType& key);                           //删除关键字
	void print_tree()const;                                         //打印树

private:
	BTreeNode<KeyType>* Root;                                 //根

	//内部函数
	bool search(BTreeNode<KeyType>* root,KeyType key);        //搜索B树
	void split_child(BTreeNode<KeyType>* x,int i);            //分裂
	void insert_notfull(BTreeNode<KeyType>* x,const KeyType& key);   //将关键字插入非满结点x
	void removeNode(BTreeNode<KeyType>*& p);                  //删除结点
	void removeTree(BTreeNode<KeyType>*& p);                 //删除树
	KeyType predecessor(BTreeNode<KeyType>* p);               //前驱辅助
	KeyType successor(BTreeNode<KeyType>* p);                 //后继辅助
	void merge(BTreeNode<KeyType>* p,int i);                  //合并结点
	void remove(BTreeNode<KeyType>* p,const KeyType& key);    //删除关键字辅助函数
	void print_tree(BTreeNode<KeyType>* p,int count)const;                                         //辅助打印树
};

//搜索B树
template<class KeyType>
bool MyBTree<KeyType>::search(BTreeNode<KeyType>* root,KeyType key){
	int i = 0;
	while(i<=root->n && key>root->key[i])
		i++;
	if(i<=root->n && key==root->key[i])
		return true;
	else if(root->leaf)
		return false;
	else
		search(root->c[i],key);
}

//搜索B树
template<class KeyType>
bool MyBTree<KeyType>::search(KeyType key){
	return search(Root,key);
}


//分裂
template<class KeyType>
void MyBTree<KeyType>::split_child(BTreeNode<KeyType>* x,int i){
	//分裂过程是将x的满孩子结点x.ci分成两个结点，左结点还放在x.ci里，右结点申请新结点z
	//也就是相当于x的满子结点分裂为两个结点z和y
	BTreeNode<KeyType>* z = new BTreeNode<KeyType>();
	BTreeNode<KeyType>* y = x->c[i];
	z->leaf = y->leaf;
	z->n = t - 1;
	//把y的高半部分的关键字拷到z中，共拷贝t-1个，及下界
	for(int j=0;j<t-1;j++){
		z->key[i] = y->key[i+t];
	}
	//如果不是叶结点，再把孩子的指针拷贝过去
	if(!y->leaf){
		for(int j=0;j<t;j++)
			z->c[j] = y->c[j+t];
	}
	//然后需要更新下y
	y->n = t-1;
	//然后需要把父结点后半部分的值往后移一位 腾出来一个地方
	for(int j=x->n;j>i;j--){
		x->key[j] = x->key[j-1];
		x->c[j+1] = x->c[j];
	}
	//然后插入位置，更新父结点
	x->key[i] = y->key[t];
	x->c[i+1] = z;
	x->n = x->n + 1;
}

//关键字插入非满结点
template<class KeyType>
void MyBTree<KeyType>::insert_notfull(BTreeNode<KeyType>* x,const KeyType& key){
	int i = x->n;
	//先处理x是叶结点的情况
	if(x->leaf){
		//先找到位置
		while(i && key<x->key[i-1]){
			x->key[i] = x->key[i-1];
			i--;
		}
		//插入并更新
		x->key[i] = key;
		x->n = x->n + 1;
	}else{
		//先找到位置
		while(i && key<x->key[i-1]){
			i--;
		}
		//如果结点为满
		BTreeNode<KeyType>* temp = x->c[i];
		if(temp->n == 2*t-1){
			//分裂结点
			split_child(x,i);
			if(key > x->key[i])
				i++;
		}
		insert_notfull(x->c[i],key);
	}
}

//插入关键字
template<class KeyType>
bool MyBTree<KeyType>::insert(const KeyType& key){
	//先处理树为空的情况
	if(Root == NULL){
		Root = new BTreeNode<KeyType>();
	}
	BTreeNode<KeyType>* r = Root;
	//先处理根结点满的情况
	if(r->n == 2*t-1){
		BTreeNode<KeyType>* s = new BTreeNode<KeyType>();
		Root = s;
		s->leaf = false;
		s->n = 0;
		s->c[0] = r;
		split_child(s,0);
		insert_notfull(s,key);
	}else{
		insert_notfull(r,key);
	}
	return true;
}

//删除结点
template<class KeyType>
void MyBTree<KeyType>::removeNode(BTreeNode<KeyType>*& p){
	if(p){
		delete p;
		p = NULL;
	}
}

//删除树
template<class KeyType>
void MyBTree<KeyType>::removeTree(BTreeNode<KeyType>*& p){
	if(p){
		if(!p->leaf){
			//删除所有子孩子
			for(int i=0;i<=p->n;i++){
				removeTree(p->c[i]);
			}
		}
		removeNode(p);
	}
}

//清空树
template<class KeyType>
void MyBTree<KeyType>::clear(){
	removeTree(Root);
	Root = NULL;
}

//前驱辅助
//某个关键字的前驱一定是这个关键字前一个区间孩子指针下最右边的关键字
template<class KeyType>
KeyType MyBTree<KeyType>::predecessor(BTreeNode<KeyType>* p){
	while(!p->leaf){
		p = p->c[p->n];
	}
	return p->key[p->n-1];
}

//后继辅助
//某个关键字的后继一定是这个关键字后一个区间孩子指针下最左边的关键字
template<class KeyType>
KeyType MyBTree<KeyType>::successor(BTreeNode<KeyType>* p){
	while(!p->leaf){
		p = p->c[0];
	}
	return p->key[0];
}

//合并结点
////这个辅助过程是用于算法导论p286的2.c，输入分别为父结点指针和子结点位置i
template<class KeyType>
void MyBTree<KeyType>::merge(BTreeNode<KeyType>* p,int i){
	BTreeNode<KeyType>* pLeftChild = p->c[i];     //左孩子
    BTreeNode<KeyType>* pRightChild = p->c[i+1];  //右孩子
    //右孩子合并到左孩子
    pLeftChild->n = 2*t-1;  //左孩子满 
	pLeftChild->key[t-1] = p->key[i];//将父结点i的值下移    
    //把右树移到左树的后面
	for (int j=0;j<t-1;j++)  
    {  
        pLeftChild->key[j+t] = pRightChild->key[j];  
    }  
    if (!pLeftChild->leaf)  
    {  
        for (int j=0;j<t;j++)  
        {  
            pLeftChild->c[j+t] = pRightChild->c[j];  
        }  
    }  
	//父结点删除i的key，i后的往前移一位  
    --p->n;  
    for(int j=i;j<p->n;j++)  
    {  
        p->key[j] = p->key[j+1];  
        p->c[j+1] = p->c[j+2];  
    }  
	//删除pRightChild
    removeNode(pRightChild);  
}


//删除关键字辅助函数
template<class KeyType>
void MyBTree<KeyType>::remove(BTreeNode<KeyType>* p,const KeyType& key){
	int i=0;  
    while(i<p->n && key>p->key[i])  
        ++i;  
    if (i<p->n && key==p->key[i])//关键字key在结点p中  
    {  
        if (p->leaf)//p是个叶结点  
        {  
            //从p中删除k  
            --p->n;  
            for (;i<p->n;i++)  
            {  
                p->key[i] = p->key[i+1];  
            }  
                return;  
        }else{          //p是个内结点
            BTreeNode<KeyType>* cPrev = p->c[i];//结点p中前于key的子结点  
            BTreeNode<KeyType>* cNext = p->c[i+1];//结点p中后于key的子结点  
            if (cPrev->n >= t){//结点cPrev中至少包含t个关键字  
                KeyType prevKey = predecessor(cPrev); //获取key的前驱关键字  
                remove(cPrev,prevKey);  
                p->key[i] = prevKey;              //替换成key的前驱关键字  
                return;  
            }else if(cNext->n >= t){              //结点cNext中至少包含t个关键字 
                KeyType nextKey = successor(cNext); //获取key的后继关键字  
                remove(cNext,nextKey);  
                p->key[i] = nextKey;          //替换成key的后继关键字  
                return;  
            }else{                           //结点cPrev和cNext中都只包含t-1个关键字  
                merge(p, i);  
                remove(cPrev, key);  
            }  
        }  
    }else{                 //关键字key不在结点p中  
        BTreeNode<KeyType>* cNode = p->c[i];//包含key的子树根结点  
        if (cNode->n == t-1){//只有t-1个关键字  
            BTreeNode<KeyType>* pLeft = i>0 ? p->c[i-1] : NULL;  //左兄弟结点  
            BTreeNode<KeyType>* pRight = i<p->n ? p->c[i+1] : NULL;//右兄弟结点  
            int j;  
            if (pLeft && pLeft->n>=t){//左兄弟结点至少有t个关键字  
                for (j=cNode->n;j>0;j--){     //父结点中i-1的关键字下移至cNode中
                    cNode->key[j] = cNode->key[j-1];  
                }  
                cNode->key[0] = p->key[i-1];  
                if (!pLeft->leaf){    
                    for (j=cNode->n+1;j>0;j--){ //pLeft结点中合适的子女指针移植到cNode中  
                        cNode->c[j] = cNode->c[j-1];  
                    }  
                    cNode->c[0] = pLeft->c[pLeft->n];  
                }  
                ++cNode->n;  
                p->key[i] = pLeft->key[pLeft->n-1];//pLeft结点中的最大关键字上升到p中  
                --pLeft->n;  
            }else if (pRight&&pRight->n>=t){     //右兄弟结点至少有t个关键字  
                  //父结点中i的关键字下移至cNode中  
                cNode->key[cNode->n] = p->key[i];  
                ++cNode->n;  
                p->key[i] = pRight->key[0];//pRight结点中的最小关键字上升到p中  
                --pRight->n;  
                for (j=0; j<pRight->n; ++j){  
                   pRight->key[j] = pRight->key[j+1];  
                }  
                if (!pRight->leaf)    
                {  
                    cNode->c[cNode->n] = pRight->c[0];//pRight结点中合适的子女指针移植到cNode中  
                    for (j=0;j<=pRight->n;j++){  
                        pRight->c[j] = pRight->c[j+1];  
                    }  
                }  
            }else if(pLeft){  
                //左右兄弟结点都只包含t-1个结点  
                //与左兄弟合并  
                merge(p, i-1);  
                cNode = pLeft;  
            }else if(pRight){        //与右兄弟合并  
                merge(p, i);  
            }  
        }  
        remove(cNode, key);  
    }
}

//删除某关键字
template<class KeyType>
bool MyBTree<KeyType>::remove(const KeyType& key){
	if (!search(Root, key)){  //不存在  
        return false;  
    }
	if (Root->n == 1){    //特殊情况处理  
        if (Root->leaf){  
            clear();  
            return true;  
        }else{ 
            BTreeNode<KeyType>* pLeftChild = Root->c[0];  
            BTreeNode<KeyType>* pRightChild = Root->c[1];  
            if(pLeftChild->n==t-1 && pRightChild->n==t-1){  
                merge(Root, 0);  
                removeNode(Root);  
                Root = pLeftChild;  
            }  
        }  
    }  
    remove(Root, key);  
    return true;
}

//打印树
template<class KeyType>
void MyBTree<KeyType>::print_tree(BTreeNode<KeyType>* p,int count)const{
	if(p){
		int i,j;
        for (i=0;i<p->n;i++){
			if (!p->leaf){
				print_tree(p->c[i],count-2);  
            }
			for (j=count;j>=0;j--){  
                cout<<"-";  
            }
            cout<<p->key[i]<<endl;  
        }  
        if(!p->leaf){
			print_tree(p->c[i],count-2);  
        }  
    } 
}

template<class KeyType>
void MyBTree<KeyType>::print_tree()const{
	print_tree(Root,(2*t-1));
}

#endif