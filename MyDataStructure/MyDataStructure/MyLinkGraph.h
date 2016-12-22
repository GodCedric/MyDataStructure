#ifndef __MYLINKGRAPH__H__
#define __MYLINKGRAPH__H__

/*********基于邻接链表的派生图类*********/
#include"MyGraph.h"

//定义边
template<typename VertexType,typename EdgeType> 
struct Edge{
	int dest;  //边的另一个结点位置
	EdgeType cost;   //边的权值
	Edge<VertexType,EdgeType> *link;  //指针，指向下一条边

	Edge(){}    //默认构造函数
	Edge(int num,EdgeType weight):dest(num),cost(weight),link(NULL){}   //构造函数

};

//定义结点
template<typename VertexType,typename EdgeType> 
struct Vertex{
	VertexType data;                //结点名
	Edge<VertexType,EdgeType> *adj; //链表头指针
};

//邻接链表表示的图
template<typename VertexType,typename EdgeType> 
class MyLinkGraph:public MyGraph<VertexType,EdgeType>{
public:
	//构造析构
	MyLinkGraph(int sz = DefaultVertices);
	~MyLinkGraph();
	//基类纯虚函数实例化
	Vertex getValue(int i){          //获取结点值
		return (i>=0 && i<numVertices)?NodeTable[i].data:0;
	}
	EdgeType getWeight(int v1,int v2);  // 
	int getFirstNeighbor(int v);          //取结点v的第一个邻接点
	int getNextNeighbor(int v,int w);     //取邻接结点w的下一个邻接结点
	bool insertVertex(const VertexType& vertex);   //插入结点
	bool inertEdge(int v1,int v2,EdgeType cost);   //插入边
	bool removeVertex(int v);             //删除结点
	bool removeEdge(int v1,int v2);       //删除边(v1,v2)
	int getVertexPos(VertexType vertex){    //结点的位置以它在表中的下标序号决定
		for(int i=0;i<numVertices;i++){
			if(NodeTable[i].date == vertex)
				return i;
		}
		return -1;
	}
	//成员函数
	void inputGraph();
	void outputGraph();
	
private:
	Vertex<VertexType,EdgeType>* NodeTable;   //结点表 
};

//构造函数
template<typename VertexType,typename EdgeType> 
MyLinkGraph<VertexType,EdgeType>::MyLinkGraph(int sz){
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	NodeTable = new Vertex<VertexType,EdgeType>[maxVertices];
	if(NodeTable == NULL){
		cerr<<"存储分配错误"<<endl;
		exit(1);
	}
	for(int i=0;i<MaxVertices;i++){
		NodeTable[i].adj = NULL;
	}
}

//析构函数
template<typename VertexType,typename EdgeType> 
MyLinkGraph<VertexType,EdgeType>::~MyLinkGraph(){
	//释放链表空间
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

//返回边的权重
////v1，v2表示结点位置，如果两个结点之间存在边，则返回该边的权重，否则返回0
template<typename VertexType,typename EdgeType> 
EdgeType MyLinkGraph<VertexType,EdgeType>::getWeight(int v1,int v2){
	//前提是结点必须存在
	if(v1!=-1 && v2!=-1){
		Edge<VertexType,EdgeType> *p = NodeTable[v1].adj;//取出结点对应的边链表的头指针
		while(p && p->dest!=v2)
			p = p->link;
		if(p)
			return p->cost;
	}
	return 0;
}





#endif