#ifndef __MYGRAPH__H__
#define __MYGRAPH__H__

/*********图基类（抽象类）*********/
#include<iostream>
using namespace std;

const int DefaultVertices = 30;    //设置默认结点个数

template<typename VertexType,typename EdgeType> 
//VertexType表示结点类型，RelationType表示邻接关系（邻接关系）
class MyGraph{
public:
	//构造析构
	MyGraph(int size = DefaultVertices){}
	~MyGraph(){}

	///////////基本成员函数
	bool GraphEmpty()const{                         //判断图是否为空
		if(numEdges == 0)
			return true;
		else
			return false;
	}
	int NumofVertices()const{return numVertices;}   //返回顶点个数
	int NumofEdges()const{return numEdges;}         //返回边条数
	///////////纯虚函数
	virtual int getVertexPos(VertexType vertex)=0;  //获取结点位置
													//结点位置即为它在链表的下标
	virtual VertexType getValue(int i)=0;           //返回结点i的值          
	virtual EdgeType getWeight(int v1,int v2)=0;    //返回边权值
	//virtual int getFirstNeighbor(int v)=0;          //取结点v的第一个邻接点
	//virtual int getNextNeighbor(int v,int w)=0;     //取邻接结点w的下一个邻接结点
	virtual bool insertVertex(const VertexType& vertex)=0;   //插入结点
	virtual bool inertEdge(int v1,int v2,EdgeType cost)=0;   //插入边
	virtual bool removeVertex(int v)=0;             //删除结点
	virtual bool removeEdge(int v1,int v2)=0;       //删除边(v1,v2)
	

protected:
	int numVertices;   //结点个数
	int numEdges;      //边个数
	int maxVertices;   //最大结点个数
};

#endif