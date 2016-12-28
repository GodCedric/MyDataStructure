#ifndef __MYBTREE__H__
#define __MYBTREE__H__

//����������
static const int t = 3;              //��С����>=2

//��㶨��
template<class KeyType>              //�ؼ�������
struct BTreeNode{
	int n;                    //�ؼ��ָ���
	KeyType key[2*t-1];     //�ؼ��־���
	bool leaf;                //�Ƿ�Ҷ���
	BTreeNode* c[2*t];       //����ָ�����

	BTreeNode(int n=0,bool leaf=true):n(n),leaf(leaf){}   //��ʼĬ��ΪҶ���
};


template<class KeyType>   
class MyBTree{
public:
	MyBTree(){Root = NULL;}     //���캯��
	~MyBTree(){}                //��������

	//�ӿں���
	bool search(KeyType key);                                  //����B��
	bool insert(const KeyType& key);                          //����ؼ���

private:
	BTreeNode<KeyType>* Root;               //��

	//�ڲ�����
	bool search(BTreeNode<KeyType>* root,KeyType key);        //����B��
	void split_child(BTreeNode<KeyType>* x,int i);            //����
	void insert_notfull(BTreeNode<KeyType>* x,const KeyType& key);   //���ؼ��ֲ���������x
};

//����B��
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

//����B��
template<class KeyType>
bool MyBTree<KeyType>::search(KeyType key){
	return search(Root,key);
}


//����
template<class KeyType>
void MyBTree<KeyType>::split_child(BTreeNode<KeyType>* x,int i){
	//���ѹ����ǽ�x�������ӽ��x.ci�ֳ�������㣬���㻹����x.ci��ҽ�������½��z
	//Ҳ�����൱��x�����ӽ�����Ϊ�������z��y
	BTreeNode<KeyType>* z = new BTreeNode<KeyType>();
	BTreeNode<KeyType>* y = x->c[i];
	z->leaf = y->leaf;
	z->n = t - 1;
	//��y�ĸ߰벿�ֵĹؼ��ֿ���z�У�������t-1�������½�
	for(int j=0;j<t-1;j++){
		z->key[i] = y->key[i+t];
	}
	//�������Ҷ��㣬�ٰѺ��ӵ�ָ�뿽����ȥ
	if(!y->leaf){
		for(int j=0;j<t;j++)
			z->c[j] = y->c[j+t];
	}
	//Ȼ����Ҫ������y
	y->n = t-1;
	//Ȼ����Ҫ�Ѹ��ڵ��벿�ֵ�ֵ������һλ �ڳ���һ���ط�
	for(int j=x->n;j>i;j--){
		x->key[j] = x->key[j-1];
		x->c[j+1] = x->c[j];
	}
	//Ȼ�����λ�ã����¸����
	x->key[i] = y->key[t];
	x->c[i+1] = z;
	x->n = x->n + 1;
}

//�ؼ��ֲ���������
template<class KeyType>
void MyBTree<KeyType>::insert_notfull(BTreeNode<KeyType>* x,const KeyType& key){
	int i = x->n;
	//�ȴ���x��Ҷ�������
	if(x->leaf){
		//���ҵ�λ��
		while(i && key<x->key[i-1]){
			x->key[i] = x->key[i-1];
			i--;
		}
		//���벢����
		x->key[i] = key;
		x->n = x->n + 1;
	}else{
		//���ҵ�λ��
		while(i && key<x->key[i-1]){
			i--;
		}
		//������Ϊ��
		BTreeNode<KeyType>* temp = x->c[i];
		if(temp->n == 2*t-1){
			//���ѽ��
			split_child(x,i);
			if(key > x->key[i])
				i++;
		}
		insert_notfull(x->c[i],key);
	}
}

//����ؼ���
template<class KeyType>
bool MyBTree<KeyType>::insert(const KeyType& key){
	//�ȴ�����Ϊ�յ����
	if(Root == NULL){
		Root = new BTreeNode<KeyType>();
	}
	BTreeNode<KeyType>* r = Root;
	//�ȴ��������������
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