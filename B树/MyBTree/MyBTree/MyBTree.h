#ifndef __MYBTREE__H__
#define __MYBTREE__H__

static const int t = 3;                  //��С����>=2/�ؼ�������

template<class KeyType>  
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
	bool insert(const KeyType& key);                           //����ؼ���
	void clear();                                              //�����
	bool remove(const KeyType& key);                           //ɾ���ؼ���
	void print_tree()const;                                         //��ӡ��

private:
	BTreeNode<KeyType>* Root;                                 //��

	//�ڲ�����
	bool search(BTreeNode<KeyType>* root,KeyType key);        //����B��
	void split_child(BTreeNode<KeyType>* x,int i);            //����
	void insert_notfull(BTreeNode<KeyType>* x,const KeyType& key);   //���ؼ��ֲ���������x
	void removeNode(BTreeNode<KeyType>*& p);                  //ɾ�����
	void removeTree(BTreeNode<KeyType>*& p);                 //ɾ����
	KeyType predecessor(BTreeNode<KeyType>* p);               //ǰ������
	KeyType successor(BTreeNode<KeyType>* p);                 //��̸���
	void merge(BTreeNode<KeyType>* p,int i);                  //�ϲ����
	void remove(BTreeNode<KeyType>* p,const KeyType& key);    //ɾ���ؼ��ָ�������
	void print_tree(BTreeNode<KeyType>* p,int count)const;                                         //������ӡ��
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
	//Ȼ����Ҫ�Ѹ�����벿�ֵ�ֵ������һλ �ڳ���һ���ط�
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

//ɾ�����
template<class KeyType>
void MyBTree<KeyType>::removeNode(BTreeNode<KeyType>*& p){
	if(p){
		delete p;
		p = NULL;
	}
}

//ɾ����
template<class KeyType>
void MyBTree<KeyType>::removeTree(BTreeNode<KeyType>*& p){
	if(p){
		if(!p->leaf){
			//ɾ�������Ӻ���
			for(int i=0;i<=p->n;i++){
				removeTree(p->c[i]);
			}
		}
		removeNode(p);
	}
}

//�����
template<class KeyType>
void MyBTree<KeyType>::clear(){
	removeTree(Root);
	Root = NULL;
}

//ǰ������
//ĳ���ؼ��ֵ�ǰ��һ��������ؼ���ǰһ�����亢��ָ�������ұߵĹؼ���
template<class KeyType>
KeyType MyBTree<KeyType>::predecessor(BTreeNode<KeyType>* p){
	while(!p->leaf){
		p = p->c[p->n];
	}
	return p->key[p->n-1];
}

//��̸���
//ĳ���ؼ��ֵĺ��һ��������ؼ��ֺ�һ�����亢��ָ��������ߵĹؼ���
template<class KeyType>
KeyType MyBTree<KeyType>::successor(BTreeNode<KeyType>* p){
	while(!p->leaf){
		p = p->c[0];
	}
	return p->key[0];
}

//�ϲ����
////������������������㷨����p286��2.c������ֱ�Ϊ�����ָ����ӽ��λ��i
template<class KeyType>
void MyBTree<KeyType>::merge(BTreeNode<KeyType>* p,int i){
	BTreeNode<KeyType>* pLeftChild = p->c[i];     //����
    BTreeNode<KeyType>* pRightChild = p->c[i+1];  //�Һ���
    //�Һ��Ӻϲ�������
    pLeftChild->n = 2*t-1;  //������ 
	pLeftChild->key[t-1] = p->key[i];//�������i��ֵ����    
    //�������Ƶ������ĺ���
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
	//�����ɾ��i��key��i�����ǰ��һλ  
    --p->n;  
    for(int j=i;j<p->n;j++)  
    {  
        p->key[j] = p->key[j+1];  
        p->c[j+1] = p->c[j+2];  
    }  
	//ɾ��pRightChild
    removeNode(pRightChild);  
}


//ɾ���ؼ��ָ�������
template<class KeyType>
void MyBTree<KeyType>::remove(BTreeNode<KeyType>* p,const KeyType& key){
	int i=0;  
    while(i<p->n && key>p->key[i])  
        ++i;  
    if (i<p->n && key==p->key[i])//�ؼ���key�ڽ��p��  
    {  
        if (p->leaf)//p�Ǹ�Ҷ���  
        {  
            //��p��ɾ��k  
            --p->n;  
            for (;i<p->n;i++)  
            {  
                p->key[i] = p->key[i+1];  
            }  
                return;  
        }else{          //p�Ǹ��ڽ��
            BTreeNode<KeyType>* cPrev = p->c[i];//���p��ǰ��key���ӽ��  
            BTreeNode<KeyType>* cNext = p->c[i+1];//���p�к���key���ӽ��  
            if (cPrev->n >= t){//���cPrev�����ٰ���t���ؼ���  
                KeyType prevKey = predecessor(cPrev); //��ȡkey��ǰ���ؼ���  
                remove(cPrev,prevKey);  
                p->key[i] = prevKey;              //�滻��key��ǰ���ؼ���  
                return;  
            }else if(cNext->n >= t){              //���cNext�����ٰ���t���ؼ��� 
                KeyType nextKey = successor(cNext); //��ȡkey�ĺ�̹ؼ���  
                remove(cNext,nextKey);  
                p->key[i] = nextKey;          //�滻��key�ĺ�̹ؼ���  
                return;  
            }else{                           //���cPrev��cNext�ж�ֻ����t-1���ؼ���  
                merge(p, i);  
                remove(cPrev, key);  
            }  
        }  
    }else{                 //�ؼ���key���ڽ��p��  
        BTreeNode<KeyType>* cNode = p->c[i];//����key�����������  
        if (cNode->n == t-1){//ֻ��t-1���ؼ���  
            BTreeNode<KeyType>* pLeft = i>0 ? p->c[i-1] : NULL;  //���ֵܽ��  
            BTreeNode<KeyType>* pRight = i<p->n ? p->c[i+1] : NULL;//���ֵܽ��  
            int j;  
            if (pLeft && pLeft->n>=t){//���ֵܽ��������t���ؼ���  
                for (j=cNode->n;j>0;j--){     //�������i-1�Ĺؼ���������cNode��
                    cNode->key[j] = cNode->key[j-1];  
                }  
                cNode->key[0] = p->key[i-1];  
                if (!pLeft->leaf){    
                    for (j=cNode->n+1;j>0;j--){ //pLeft����к��ʵ���Ůָ����ֲ��cNode��  
                        cNode->c[j] = cNode->c[j-1];  
                    }  
                    cNode->c[0] = pLeft->c[pLeft->n];  
                }  
                ++cNode->n;  
                p->key[i] = pLeft->key[pLeft->n-1];//pLeft����е����ؼ���������p��  
                --pLeft->n;  
            }else if (pRight&&pRight->n>=t){     //���ֵܽ��������t���ؼ���  
                  //�������i�Ĺؼ���������cNode��  
                cNode->key[cNode->n] = p->key[i];  
                ++cNode->n;  
                p->key[i] = pRight->key[0];//pRight����е���С�ؼ���������p��  
                --pRight->n;  
                for (j=0; j<pRight->n; ++j){  
                   pRight->key[j] = pRight->key[j+1];  
                }  
                if (!pRight->leaf)    
                {  
                    cNode->c[cNode->n] = pRight->c[0];//pRight����к��ʵ���Ůָ����ֲ��cNode��  
                    for (j=0;j<=pRight->n;j++){  
                        pRight->c[j] = pRight->c[j+1];  
                    }  
                }  
            }else if(pLeft){  
                //�����ֵܽ�㶼ֻ����t-1�����  
                //�����ֵܺϲ�  
                merge(p, i-1);  
                cNode = pLeft;  
            }else if(pRight){        //�����ֵܺϲ�  
                merge(p, i);  
            }  
        }  
        remove(cNode, key);  
    }
}

//ɾ��ĳ�ؼ���
template<class KeyType>
bool MyBTree<KeyType>::remove(const KeyType& key){
	if (!search(Root, key)){  //������  
        return false;  
    }
	if (Root->n == 1){    //�����������  
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

//��ӡ��
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