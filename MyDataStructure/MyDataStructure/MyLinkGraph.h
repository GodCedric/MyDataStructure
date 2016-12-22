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
	Vertex getValue(int i){          //��ȡ���ֵ
		return (i>=0 && i<numVertices)?NodeTable[i].data:0;
	}
	EdgeType getWeight(int v1,int v2);  // 
	int getFirstNeighbor(int v);          //ȡ���v�ĵ�һ���ڽӵ�
	int getNextNeighbor(int v,int w);     //ȡ�ڽӽ��w����һ���ڽӽ��
	bool insertVertex(const VertexType& vertex);   //������
	bool inertEdge(int v1,int v2,EdgeType cost);   //�����
	bool removeVertex(int v);             //ɾ�����
	bool removeEdge(int v1,int v2);       //ɾ����(v1,v2)
	int getVertexPos(VertexType vertex){    //����λ�������ڱ��е��±���ž���
		for(int i=0;i<numVertices;i++){
			if(NodeTable[i].date == vertex)
				return i;
		}
		return -1;
	}
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
	for(int i=0;i<MaxVertices;i++){
		NodeTable[i].adj = NULL;
	}
}

//��������
template<typename VertexType,typename EdgeType> 
MyLinkGraph<VertexType,EdgeType>::~MyLinkGraph(){
	//�ͷ�����ռ�
	for(int i=0;i<MaxVertices;i++){
		Edge<VertexType,EdgeType>* p = NodeTable[i].adj;
		while(p){
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
	delete[] NodeTable;
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





#endif