#ifndef __MYLINKGRAPH__H__
#define __MYLINKGRAPH__H__

/*********�����ڽ����������ͼ��*********/
#include"MyGraph.h"

//�����
template<typename VertexType,typename EdgeType> 
struct Edge{
	int dest;  //�ߵ���һ�����λ��
	EdgeType cost;   //�ߵ�Ȩֵ
	Edge<VertexType,EdgeType> *link;  //ָ�룬ָ����һ����

	Edge(){}    //Ĭ�Ϲ��캯��
	Edge(int num,EdgeType weight):dest(num),cost(weight),link(NULL){}   //���캯��

};

//������
template<typename VertexType,typename EdgeType> 
struct Vertex{
	VertexType data;                //�����
	Edge<VertexType,EdgeType> *adj; //����ͷָ��
};

//�ڽ������ʾ��ͼ
template<typename VertexType,typename EdgeType> 
class MyLinkGraph:public MyGraph<VertexType,EdgeType>{
public:
	//��������
	MyLinkGraph(int sz = DefaultVertices);
	~MyLinkGraph();
	//���ി�麯��ʵ����
	int getVertexPos(VertexType vertex){    //����λ�������ڱ��е��±���ž���
		for(int i=0;i<numVertices;i++){
			if(NodeTable[i].data == vertex)
				return i;
		}
		return -1;
	}

	VertexType getValue(int i);            //��ȡ���ֵ
	EdgeType getWeight(int v1,int v2);  // ��ȡ�ߵ�Ȩ��
	int getFirstNeighbor(int v);          //ȡ���v�ĵ�һ���ڽӵ�
	int getNextNeighbor(int v,int w);     //ȡ�ڽӽ��w����һ���ڽӽ��
	bool insertVertex(const VertexType& vertex);   //������
	bool inertEdge(int v1,int v2,EdgeType cost);   //�����
	bool removeVertex(int v);             //ɾ�����
	bool removeEdge(int v1,int v2);       //ɾ����(v1,v2)
	//��Ա����
	void inputGraph();
	void outputGraph();
	
private:
	Vertex<VertexType,EdgeType>* NodeTable;   //���� 
};

//���캯��
template<typename VertexType,typename EdgeType> 
MyLinkGraph<VertexType,EdgeType>::MyLinkGraph(int sz){
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	NodeTable = new Vertex<VertexType,EdgeType>[maxVertices];
	if(NodeTable == NULL){
		cerr<<"�洢�������"<<endl;
		exit(1);
	}
	for(int i=0;i<maxVertices;i++){
		NodeTable[i].adj = NULL;
	}
}

//��������
template<typename VertexType,typename EdgeType> 
MyLinkGraph<VertexType,EdgeType>::~MyLinkGraph(){
	//�ͷ�����ռ�
	for(int i=0;i<maxVertices;i++){
		Edge<VertexType,EdgeType>* p = NodeTable[i].adj;
		while(p){
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
	delete[] NodeTable;
}

//���ؽ��i��ֵ
template<typename VertexType,typename EdgeType>
VertexType MyLinkGraph<VertexType,EdgeType>::getValue(int i){          //��ȡ���ֵ
	return (i>=0 && i<numVertices)?NodeTable[i].data:0;
}


//���رߵ�Ȩ��
////v1��v2��ʾ���λ�ã�����������֮����ڱߣ��򷵻ظñߵ�Ȩ�أ����򷵻�0
template<typename VertexType,typename EdgeType> 
EdgeType MyLinkGraph<VertexType,EdgeType>::getWeight(int v1,int v2){
	//ǰ���ǽ��������
	if(v1!=-1 && v2!=-1){
		Edge<VertexType,EdgeType> *p = NodeTable[v1].adj;//ȡ������Ӧ�ı������ͷָ��
		while(p && p->dest!=v2)
			p = p->link;
		if(p)
			return p->cost;
	}
	return 0;
}

//��ȡ���v�ĵ�һ���ڽӵ�
template<typename VertexType,typename EdgeType> 
int MyLinkGraph<VertexType,EdgeType>::getFirstNeighbor(int v){
	if(v != -1){
		Edge<typename VertexType,typename EdgeType> *p = NodeTable[v].adj;
		if(p){
			return p->dest;  //����������㣬����vΪ�ߵ�һ����㣬��p->dest�Ǵ�ı����һ������λ��
		}
	}
	return -1;
}

//��ȡ���v���ڽӽ��w����һ���ڽӵ�
template<typename VertexType,typename EdgeType> 
int MyLinkGraph<VertexType,EdgeType>::getNextNeighbor(int v,int w){   //����wҪ��v��һ���ڽӵ�
	if(v != -1){
		Edge<typename VertexType,typename EdgeType> *p = NodeTable[v].adj;
		while(p && p->dest!=w)    //���ҵ�w
			p = p->link;
		if(p && p->link)
			return p->link->dest;
	}
	return -1;
}

//������
template<typename VertexType,typename EdgeType> 
bool MyLinkGraph<VertexType,EdgeType>::insertVertex(const VertexType& vertex){    //����ֵΪ�����
	if(numVertices == maxVertices)
		return false;
	NodeTable[numVertices].data = vertex;
	numVertices++;
	return true;
}

//�����
template<typename VertexType,typename EdgeType> 
bool MyLinkGraph<VertexType,EdgeType>::inertEdge(int v1,int v2,EdgeType weight){
	//Ҫ�������v1��v2����
	if(v1>=0 && v1<numVertices && v2>=0 && v2<numVertices){
		//����������ǲ����Ѿ������ˣ�������ڣ��򷵻ز���ʧ��
		Edge<VertexType,EdgeType> *p = NodeTable[v1].adj;
		while(p && p->dest!=v2)
			p = p->link;
		if(p){//���p����
			cout<<"�ñ��Ѿ������ˣ�����ʧ��"<<endl;
			return false;
		}
		//�������v1��v2�����Ҹñ߲����ڣ���ɲ���ñߵ�v1����ڽӱ�ı�ͷ
		Edge<VertexType,EdgeType> *v1p = new Edge<VertexType,EdgeType>; //���뵽���v1�ı�ͷ
		Edge<VertexType,EdgeType> *v2p = new Edge<VertexType,EdgeType>; //���뵽���v2�ı�ͷ
		v1p->dest = v2;
		v1p->cost = weight;
		v1p->link = NodeTable[v1].adj;  //��v1��㱾�����ڽӱ�ӵ��½���Edge��link��
		NodeTable[v1].adj = v1p;        //�����½���Edge�ŵ�v1����ڽӱ�ı�ͷ
		v2p->dest = v1;
		v2p->cost = weight;
		v2p->link = NodeTable[v2].adj;  //��v2��㱾�����ڽӱ�ӵ��½���Edge��link��
		NodeTable[v2].adj = v2p;        //�����½���Edge�ŵ�v2����ڽӱ�ı�ͷ

		numEdges++; //�߼�1
		return true;
	}
	return false;
}

//ɾ�����
template<typename VertexType,typename EdgeType> 
bool MyLinkGraph<VertexType,EdgeType>::removeVertex(int v){
	//���ж��½��v�Ƿ����
	if(v<0 || v>=numVertices || numVertices==1)  //ֻ��1������Ȳ���ɾ��
		return false;
	//ɾ����㣬����Ҫ������������صı�ȫɾ����
	Edge<VertexType,EdgeType> *p;
	Edge<VertexType,EdgeType> *q;
	Edge<VertexType,EdgeType> *q_before;
	int k;
	while(NodeTable[v].adj){
		//����Ҫ�ҵ����������Ľ�㣬���Ǹ������������ı�ɾ��
		p = NodeTable[v].adj;
		k = p->dest;
		q = NodeTable[k].adj;
		q_before = NULL;  //ά��һ��q�ߵ�ǰ��һ���ߵ�ָ��
		while(q && q->dest!=v){
			q_before = q;
			q = q->link;
		}
		if(q){
			if(q_before == NULL) //�����whileû���У�˵��q->dest==v
				NodeTable[k].adj = q->link;
			else
				q_before->link = q->link;
			delete q;
		}
		
		//Ȼ����Ҫ�ѽ��v����������Ҳɾ��
		NodeTable[v].adj = p->link;
		delete p;
		numEdges--;
	}
	//��ɾ���� ����Ҫ�ѵ�ɾ������ô��ĸ�������һ�����Ͱ�ԭ���������ĵ�ŵ�v��λ�ã�����numVertices--
	NodeTable[v].data = NodeTable[numVertices].data;
	NodeTable[v].adj = NodeTable[numVertices].adj;
	//������Ҫ���������Ա���������һ������ֵ����һ��
	Edge<VertexType,EdgeType> *m = NodeTable[numVertices].adj;
	while(m){
		Edge<VertexType,EdgeType> *n = NodeTable[m->dest].adj;
		while(n){
			if(n->dest == numVertices){
				n->dest = v;
				break;
			}else{
				n = n->link;
			}
		}
		m = m->link;
	}
	numVertices--;
	return true;
}

//ɾ����
template<typename VertexType,typename EdgeType> 
bool MyLinkGraph<VertexType,EdgeType>::removeEdge(int v1,int v2){
	//���ж��������Ƿ����
	if(v1>=0 && v1<numVertices && v2>=0 && v2<numVertices){
		//�Ȱ�v1�ı�ɾ��
		Edge<VertexType,EdgeType> *v1p = NodeTable[v1].adj;
		Edge<VertexType,EdgeType> *v1p_before = NULL;   //ά��һ��ǰָ��
		//���ҵ�������
		while(v1p && v1p->dest!=v2){
			v1p_before = v1p;
			v1p = v1p->link;
		}
		if(v1p){    //���ҵ�
			if(v1p_before == NULL)
				NodeTable[v1].adj = v1p->link;
			else
				v1p_before->link = v1p->link;
			delete v1p;
		}else{     //�Ҳ���������û�������ߣ����ش���
 			return false;
		}

		//�ٰ�v2�ı�ɾ��
		Edge<VertexType,EdgeType> *v2p = NodeTable[v2].adj;
		Edge<VertexType,EdgeType> *v2p_before = NULL;   //ά��һ��ǰָ��
		//���ҵ�������
		while(v2p && v2p->dest!=v1){
			v2p_before = v1p;
			v2p = v2p->link;
		}
		if(v2p){    //���ҵ�
			if(v1p_before == NULL)
				NodeTable[v2].adj = v2p->link;
			else
				v2p_before->link = v2p->link;
			delete v2p;
		}
		numEdges--;
		return true;
	}
	return false;
}

//ͼ�������빹��
template<typename VertexType,typename EdgeType> 
void MyLinkGraph<VertexType,EdgeType>::inputGraph(){
	int num_Vertices; // �����
	int num_Edges;    //����
	cout<<"���������������ͱ�����"<<endl;
	cin>>num_Vertices>>num_Edges;
	
	VertexType v1,v2;   //�ߵ��������
	EdgeType weight;    //�ߵ�Ȩ��
	cout<<"���������������㣺"<<endl;
	for(int i=0;i<num_Vertices;i++){
		cin>>v1;
		this->insertVertex(v1);   //this������ǰ�����Է�ֹ�Ը�������ͼʱ����
	}

	cout<<"����������ߣ������ʽΪ��v1 v1 weight"<<endl;
	int j = 0;
	while(j<num_Edges){
		cin>>v1>>v2>>weight;
		int m = this->getVertexPos(v1);
		int n = this->getVertexPos(v2);
		if(m==-1 || n==-1){
			cout<<"���벻����Ҫ������������Ƿ������"<<endl;
		}else{
			if(this->inertEdge(m,n,weight)){
				j++;
			}
		}
	}
}

//ͼ�����
template<typename VertexType,typename EdgeType> 
void MyLinkGraph<VertexType,EdgeType>::outputGraph(){
	int num_Vertices = this->NumofVertices(); // �����
	int num_Edges = this->NumofEdges();    //����
	cout<<"��ͼ�Ľ����ĿΪ��"<<num_Vertices<<" "<<"�ߵ���ĿΪ��"<<num_Edges<<endl;
	cout<<"��ͼ�Ľ��ֱ�Ϊ��";
	for(int i=0;i<num_Vertices;i++){
		cout<<NodeTable[i].data<<" ";
	}
	cout<<endl;
	cout<<"��ͼ�ı߷ֱ�Ϊ��"<<endl;
	int weight;
	VertexType v1,v2;
	for(int i=0;i<num_Vertices;i++){
		for(int j=i+1;j<num_Vertices;j++){   //��Ϊһ����ֻ���һ�Σ����������ַ���
			weight = this->getWeight(i,j);
			if(weight>0){
				v1 = this->getValue(i);
				v2 = this->getValue(j);
				cout<<"("<<v1<<","<<v2<<","<<weight<<")"<<endl;
			}
		}
	}
}



#endif