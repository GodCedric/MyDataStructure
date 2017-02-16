#ifndef __VERTEXANDEDGE__H__
#define __VERTEXANDEDGE__H__

enum Color{WHITE,GRAY,BLACK};

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
	//用于搜索的属性
	Color color;//颜色
	int d;//路径长(其实时间)
	int f;
	int i;
	Vertex* pi;//结点前驱

	Edge<VertexType,EdgeType> *adj; //链表头指针

	Vertex():color(WHITE),d(INT_MAX),f(0),pi(NULL),adj(NULL){}
};



#endif