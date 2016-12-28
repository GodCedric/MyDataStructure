#ifndef __MYBTREE__H__
#define __MYBTREE__H__

//结点参数设置
static const int t = 3;              //最小度数>=2

//结点定义
template<class KeyType>              //关键字类型
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
	bool insert(const KeyType& key);                          //插入关键字

private:
	BTreeNode<KeyType>* Root;               //根

	//内部函数
	bool search(BTreeNode<KeyType>* root,KeyType key);        //搜索B树
	void split_child(BTreeNode<KeyType>* x,int i);            //分裂
	void insert_notfull(BTreeNode<KeyType>* x,const KeyType& key);   //将关键字插入非满结点x
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
	//然后需要把父节点后半部分的值往后移一位 腾出来一个地方
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

#endif