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
	int getVertexPos(VertexType vertex){    //结点的位置以它在表中的下标序号决定
		for(int i=0;i<numVertices;i++){
			if(NodeTable[i].data == vertex)
				return i;
		}
		return -1;
	}

	VertexType getValue(int i);            //获取结点值
	EdgeType getWeight(int v1,int v2);  // 获取边的权重
	int getFirstNeighbor(int v);          //取结点v的第一个邻接点
	int getNextNeighbor(int v,int w);     //取邻接结点w的下一个邻接结点
	bool insertVertex(const VertexType& vertex);   //插入结点
	bool inertEdge(int v1,int v2,EdgeType cost);   //插入边
	bool removeVertex(int v);             //删除结点
	bool removeEdge(int v1,int v2);       //删除边(v1,v2)
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
	for(int i=0;i<maxVertices;i++){
		NodeTable[i].adj = NULL;
	}
}

//析构函数
template<typename VertexType,typename EdgeType> 
MyLinkGraph<VertexType,EdgeType>::~MyLinkGraph(){
	//释放链表空间
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

//返回结点i的值
template<typename VertexType,typename EdgeType>
VertexType MyLinkGraph<VertexType,EdgeType>::getValue(int i){          //获取结点值
	return (i>=0 && i<numVertices)?NodeTable[i].data:0;
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

//获取结点v的第一个邻接点
template<typename VertexType,typename EdgeType> 
int MyLinkGraph<VertexType,EdgeType>::getFirstNeighbor(int v){
	if(v != -1){
		Edge<typename VertexType,typename EdgeType> *p = NodeTable[v].adj;
		if(p){
			return p->dest;  //便有两个结点，输入v为边的一个结点，而p->dest是存的变得另一个结点的位置
		}
	}
	return -1;
}

//获取结点v的邻接结点w的下一个邻接点
template<typename VertexType,typename EdgeType> 
int MyLinkGraph<VertexType,EdgeType>::getNextNeighbor(int v,int w){   //这里w要是v的一个邻接点
	if(v != -1){
		Edge<typename VertexType,typename EdgeType> *p = NodeTable[v].adj;
		while(p && p->dest!=w)    //先找到w
			p = p->link;
		if(p && p->link)
			return p->link->dest;
	}
	return -1;
}

//插入结点
template<typename VertexType,typename EdgeType> 
bool MyLinkGraph<VertexType,EdgeType>::insertVertex(const VertexType& vertex){    //输入值为结点名
	if(numVertices == maxVertices)
		return false;
	NodeTable[numVertices].data = vertex;
	numVertices++;
	return true;
}

//插入边
template<typename VertexType,typename EdgeType> 
bool MyLinkGraph<VertexType,EdgeType>::inertEdge(int v1,int v2,EdgeType weight){
	//要求输入的v1和v2合理
	if(v1>=0 && v1<numVertices && v2>=0 && v2<numVertices){
		//查找这个边是不是已经存在了，如果存在，则返回插入失败
		Edge<VertexType,EdgeType> *p = NodeTable[v1].adj;
		while(p && p->dest!=v2)
			p = p->link;
		if(p){//如果p存在
			cout<<"该边已经存在了，插入失败"<<endl;
			return false;
		}
		//如果输入v1和v2合理，且该边不存在，则可插入该边到v1结点邻接表的表头
		Edge<VertexType,EdgeType> *v1p = new Edge<VertexType,EdgeType>; //插入到结点v1的表头
		Edge<VertexType,EdgeType> *v2p = new Edge<VertexType,EdgeType>; //插入到结点v2的表头
		v1p->dest = v2;
		v1p->cost = weight;
		v1p->link = NodeTable[v1].adj;  //把v1结点本来的邻接表接到新建的Edge的link上
		NodeTable[v1].adj = v1p;        //并把新建的Edge放到v1结点邻接表的表头
		v2p->dest = v1;
		v2p->cost = weight;
		v2p->link = NodeTable[v2].adj;  //把v2结点本来的邻接表接到新建的Edge的link上
		NodeTable[v2].adj = v2p;        //并把新建的Edge放到v2结点邻接表的表头

		numEdges++; //边加1
		return true;
	}
	return false;
}

//删除结点
template<typename VertexType,typename EdgeType> 
bool MyLinkGraph<VertexType,EdgeType>::removeVertex(int v){
	//先判断下结点v是否合理
	if(v<0 || v>=numVertices || numVertices==1)  //只有1个结点先不让删除
		return false;
	//删除结点，首先要把与这个结点相关的边全删除掉
	Edge<VertexType,EdgeType> *p;
	Edge<VertexType,EdgeType> *q;
	Edge<VertexType,EdgeType> *q_before;
	int k;
	while(NodeTable[v].adj){
		//首先要找到与其相连的结点，把那个结点上相关联的边删掉
		p = NodeTable[v].adj;
		k = p->dest;
		q = NodeTable[k].adj;
		q_before = NULL;  //维护一个q边的前面一条边的指针
		while(q && q->dest!=v){
			q_before = q;
			q = q->link;
		}
		if(q){
			if(q_before == NULL) //上面的while没进行，说明q->dest==v
				NodeTable[k].adj = q->link;
			else
				q_before->link = q->link;
			delete q;
		}
		
		//然后需要把结点v上面这条边也删掉
		NodeTable[v].adj = p->link;
		delete p;
		numEdges--;
	}
	//边删完了 现在要把点删掉，那么点的个数少了一个，就把原来放最后面的点放到v的位置，并把numVertices--
	NodeTable[v].data = NodeTable[numVertices].data;
	NodeTable[v].adj = NodeTable[numVertices].adj;
	//这里需要把这个结点以边相连的另一个结点的值更新一下
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

//删除边
template<typename VertexType,typename EdgeType> 
bool MyLinkGraph<VertexType,EdgeType>::removeEdge(int v1,int v2){
	//先判断下输入是否合理
	if(v1>=0 && v1<numVertices && v2>=0 && v2<numVertices){
		//先把v1的边删掉
		Edge<VertexType,EdgeType> *v1p = NodeTable[v1].adj;
		Edge<VertexType,EdgeType> *v1p_before = NULL;   //维护一个前指针
		//先找到这条边
		while(v1p && v1p->dest!=v2){
			v1p_before = v1p;
			v1p = v1p->link;
		}
		if(v1p){    //能找到
			if(v1p_before == NULL)
				NodeTable[v1].adj = v1p->link;
			else
				v1p_before->link = v1p->link;
			delete v1p;
		}else{     //找不到，就是没有这条边，返回错误
 			return false;
		}

		//再把v2的边删掉
		Edge<VertexType,EdgeType> *v2p = NodeTable[v2].adj;
		Edge<VertexType,EdgeType> *v2p_before = NULL;   //维护一个前指针
		//先找到这条边
		while(v2p && v2p->dest!=v1){
			v2p_before = v1p;
			v2p = v2p->link;
		}
		if(v2p){    //能找到
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

//图的输入与构造
template<typename VertexType,typename EdgeType> 
void MyLinkGraph<VertexType,EdgeType>::inputGraph(){
	int num_Vertices; // 结点数
	int num_Edges;    //边数
	cout<<"请依次输入结点数和边树："<<endl;
	cin>>num_Vertices>>num_Edges;
	
	VertexType v1,v2;   //边的两个结点
	EdgeType weight;    //边的权重
	cout<<"请依次输入各个结点："<<endl;
	for(int i=0;i<num_Vertices;i++){
		cin>>v1;
		this->insertVertex(v1);   //this表明当前对象，以防止对个对象建立图时混乱
	}

	cout<<"请输入各条边，输入格式为：v1 v1 weight"<<endl;
	int j = 0;
	while(j<num_Edges){
		cin>>v1>>v2>>weight;
		int m = this->getVertexPos(v1);
		int n = this->getVertexPos(v2);
		if(m==-1 || n==-1){
			cout<<"输入不符合要求，请检查两结点是否均存在"<<endl;
		}else{
			if(this->inertEdge(m,n,weight)){
				j++;
			}
		}
	}
}

//图的输出
template<typename VertexType,typename EdgeType> 
void MyLinkGraph<VertexType,EdgeType>::outputGraph(){
	int num_Vertices = this->NumofVertices(); // 结点数
	int num_Edges = this->NumofEdges();    //边数
	cout<<"该图的结点数目为："<<num_Vertices<<" "<<"边的数目为："<<num_Edges<<endl;
	cout<<"该图的结点分别为：";
	for(int i=0;i<num_Vertices;i++){
		cout<<NodeTable[i].data<<" ";
	}
	cout<<endl;
	cout<<"该图的边分别为："<<endl;
	int weight;
	VertexType v1,v2;
	for(int i=0;i<num_Vertices;i++){
		for(int j=i+1;j<num_Vertices;j++){   //因为一条边只输出一次，所以用这种方法
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