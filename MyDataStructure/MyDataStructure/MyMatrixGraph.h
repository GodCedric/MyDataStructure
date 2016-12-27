#ifndef __MYMATRIXGRAPH__H__
#define __MYMATRIXGRAPH__H__

/*********���ھ����ͼ��*********/
#include"MyGraph.h"

template<typename VertexType,typename EdgeType> 
class MyMatrixGraph:public MyGraph<VertexType,EdgeType>{
public:
	//��������
	MyMatrixGraph(int size=DefaultVertices);
	~MyMatrixGraph();

	//���ി�麯��ʵ����
	int getVertexPos(VertexType vertex){    //����λ�������ڱ��е��±���ž���
		for(int i=0;i<numVertices;i++){
			if(VerticesList[i] == vertex)
				return i;
		}
		return -1;
	}

	VertexType getValue(int i);            //��ȡ���ֵ
	EdgeType getWeight(int v1,int v2);  // ��ȡ�ߵ�Ȩ��
	bool insertVertex(const VertexType& vertex);   //������
	bool inertEdge(int v1,int v2,EdgeType cost);   //�����
	bool removeVertex(int v);             //ɾ�����
	bool removeEdge(int v1,int v2);       //ɾ����(v1,v2)
	//��Ա����
	void inputGraph();
	void outputGraph();
private:
	VertexType* VerticesList;   //�����һά����洢
	EdgeType** Edge;            //���ö�ά�����ʾ
};

//���캯��
template<typename VertexType,typename EdgeType>
MyMatrixGraph<VertexType,EdgeType>::MyMatrixGraph(int size){
	numVertices = 0;
	numEdges = 0;
	maxVertices = size;
	//���������ռ�
	VerticesList = new VertexType[maxVertices];
	//����߾���ռ�
	Edge = new EdgeType*[maxVertices];
	for(int i=0;i<maxVertices;i++)
		Edge[i] = new EdgeType[maxVertices];
	//�߾���Ȩֵ����ֵ
	for(int i=0;i<maxVertices;i++){
		for(int j=0;j<maxVertices;j++){
			Edge[i][j] = -1;
		}
	}
}

//��������
template<typename VertexType,typename EdgeType>
MyMatrixGraph<VertexType,EdgeType>::~MyMatrixGraph(){
	//�ͷŽ�����ռ�
	delete[] VerticesList;
	//�ͷű߾���ռ�
	for(int i=0;i<maxVertices;i++)
		delete[] Edge[i];
	delete[] Edge;
}

//��ȡ���ֵ
template<typename VertexType,typename EdgeType>
VertexType MyMatrixGraph<VertexType,EdgeType>::getValue(int i){
	return (i>=0 && i<numVertices)?VerticesList[i]:0;
}

//��ȡ�ߵ�Ȩֵ
template<typename VertexType,typename EdgeType>
EdgeType MyMatrixGraph<VertexType,EdgeType>::getWeight(int v1,int v2){
	return (v1!=-1 && v2!=-1)?Edge[v1][v2]:0;
}

//������
template<typename VertexType,typename EdgeType>
bool MyMatrixGraph<VertexType,EdgeType>::insertVertex(const VertexType& vertex){
	if(numVertices == maxVertices)
		return false;
	VerticesList[numVertices++] = vertex;
	return true;
}

//�����
template<typename VertexType,typename EdgeType>
bool MyMatrixGraph<VertexType,EdgeType>::inertEdge(int v1,int v2,EdgeType cost){
	if(v1>-1 && v1<numVertices && v2>-1 && v2<numVertices){
		if(Edge[v1][v2] < 0){
			Edge[v1][v2] = cost;
			numEdges++;
			return true;
		}else{
		    cout<<"�ñ��Ѿ�����"<<endl;
			return false;
		} 	
	}
	return false;
}

//ɾ�����
template<typename VertexType,typename EdgeType>
bool MyMatrixGraph<VertexType,EdgeType>::removeVertex(int v){
	//�ж������Ƿ����
	if(numVertices==1 || v<0 || v>=numVertices)
		return false;
	//�ȵ������
	numVertices--;
	VerticesList[v] = VerticesList[numVertices];
	//�ٵ�����
	for(int i=0;i<numVertices;i++){
		if(Edge[i][v] >= 0){
			numEdges--;  //�Ȱѱ�������
		}
		Edge[i][v] = Edge[i][numVertices];
		Edge[i][numVertices] = -1;
		if(Edge[v][i] >= 0){
			numEdges--;
		}
		Edge[v][i] = Edge[numVertices][i];
		Edge[numVertices][i] = -1;
	}
	return true;
}

//ɾ����
template<typename VertexType,typename EdgeType>
bool MyMatrixGraph<VertexType,EdgeType>::removeEdge(int v1,int v2){
	if(v1>-1 && v1<numVertices && v2>-1 &&v2<numVertices && Edge[v1][v2]>=0){
		Edge[v1][v2] = -1;
		numEdges--;
		return true;
	}else{
		cout<<"�ñ߲����ڻ�������������"<<endl;
		return false;
	}
}

//ͼ����
template<typename VertexType,typename EdgeType>
void MyMatrixGraph<VertexType,EdgeType>::inputGraph(){
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
			break;
		}else{
			if(this->inertEdge(m,n,weight)){
				j++;
			}
		}
	}
}

//ͼ���
template<typename VertexType,typename EdgeType>
void MyMatrixGraph<VertexType,EdgeType>::outputGraph(){
	int num_Vertices = this->NumofVertices(); // �����
	int num_Edges = this->NumofEdges();    //����
	cout<<"��ͼ�Ľ����ĿΪ��"<<num_Vertices<<" "<<"�ߵ���ĿΪ��"<<num_Edges<<endl;
	
	cout<<"��ͼ�Ľ��ֱ�Ϊ��";
	for(int i=0;i<num_Vertices;i++){
		cout<<VerticesList[i]<<" ";
	}
	cout<<endl;
	
	cout<<"��ͼ�ı߷ֱ�Ϊ��"<<endl;
	int weight;
	VertexType v1,v2;
	for(int i=0;i<num_Vertices;i++){
		for(int j=0;j<num_Vertices;j++){   //��Ϊһ����ֻ���һ�Σ����������ַ���
			weight = this->getWeight(i,j);
			if(weight >= 0){
				v1 = this->getValue(i);
				v2 = this->getValue(j);
				cout<<"("<<v1<<","<<v2<<","<<weight<<")"<<endl;
			}
		}
	}
}



#endif