#ifndef __MYGRAPH__H__
#define __MYGRAPH__H__

/*********ͼ���ࣨ�����ࣩ*********/
#include<iostream>
using namespace std;

const int DefaultVertices = 30;    //����Ĭ�Ͻ�����

template<typename VertexType,typename EdgeType> 
//VertexType��ʾ������ͣ�RelationType��ʾ�ڽӹ�ϵ���ڽӹ�ϵ��
class MyGraph{
public:
	//��������
	MyGraph(int size = DefaultVertices){}
	~MyGraph(){}

	///////////������Ա����
	bool GraphEmpty()const{                         //�ж�ͼ�Ƿ�Ϊ��
		if(numEdges == 0)
			return true;
		else
			return false;
	}
	int NumofVertices()const{return numVertices;}   //���ض������
	int NumofEdges()const{return numEdges;}         //���ر�����
	///////////���麯��
	virtual int getVertexPos(VertexType vertex)=0;  //��ȡ���λ��
													//���λ�ü�Ϊ����������±�
	virtual VertexType getValue(int i)=0;           //���ؽ��i��ֵ          
	virtual EdgeType getWeight(int v1,int v2)=0;    //���ر�Ȩֵ
	//virtual int getFirstNeighbor(int v)=0;          //ȡ���v�ĵ�һ���ڽӵ�
	//virtual int getNextNeighbor(int v,int w)=0;     //ȡ�ڽӽ��w����һ���ڽӽ��
	virtual bool insertVertex(const VertexType& vertex)=0;   //������
	virtual bool inertEdge(int v1,int v2,EdgeType cost)=0;   //�����
	virtual bool removeVertex(int v)=0;             //ɾ�����
	virtual bool removeEdge(int v1,int v2)=0;       //ɾ����(v1,v2)
	

protected:
	int numVertices;   //������
	int numEdges;      //�߸���
	int maxVertices;   //��������
};

#endif