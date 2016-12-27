#ifndef __MYMATRIXGRAPH__H__
#define __MYMATRIXGRAPH__H__

/*********基于矩阵的图类*********/
#include"MyGraph.h"

template<typename VertexType,typename EdgeType> 
class MyMatrixGraph:public MyGraph<VertexType,EdgeType>{
public:
	//构造析构
	MyMatrixGraph(int size=DefaultVertices);
	~MyMatrixGraph();

	//基类纯虚函数实例化
	int getVertexPos(VertexType vertex){    //结点的位置以它在表中的下标序号决定
		for(int i=0;i<numVertices;i++){
			if(VerticesList[i] == vertex)
				return i;
		}
		return -1;
	}

	VertexType getValue(int i);            //获取结点值
	EdgeType getWeight(int v1,int v2);  // 获取边的权重
	bool insertVertex(const VertexType& vertex);   //插入结点
	bool inertEdge(int v1,int v2,EdgeType cost);   //插入边
	bool removeVertex(int v);             //删除结点
	bool removeEdge(int v1,int v2);       //删除边(v1,v2)
	//成员函数
	void inputGraph();
	void outputGraph();
private:
	VertexType* VerticesList;   //结点用一维数组存储
	EdgeType** Edge;            //边用二维数组表示
};

//构造函数
template<typename VertexType,typename EdgeType>
MyMatrixGraph<VertexType,EdgeType>::MyMatrixGraph(int size){
	numVertices = 0;
	numEdges = 0;
	maxVertices = size;
	//分配结点矩阵空间
	VerticesList = new VertexType[maxVertices];
	//分配边矩阵空间
	Edge = new EdgeType*[maxVertices];
	for(int i=0;i<maxVertices;i++)
		Edge[i] = new EdgeType[maxVertices];
	//边矩阵权值赋初值
	for(int i=0;i<maxVertices;i++){
		for(int j=0;j<maxVertices;j++){
			Edge[i][j] = -1;
		}
	}
}

//析构函数
template<typename VertexType,typename EdgeType>
MyMatrixGraph<VertexType,EdgeType>::~MyMatrixGraph(){
	//释放结点矩阵空间
	delete[] VerticesList;
	//释放边矩阵空间
	for(int i=0;i<maxVertices;i++)
		delete[] Edge[i];
	delete[] Edge;
}

//获取结点值
template<typename VertexType,typename EdgeType>
VertexType MyMatrixGraph<VertexType,EdgeType>::getValue(int i){
	return (i>=0 && i<numVertices)?VerticesList[i]:0;
}

//获取边的权值
template<typename VertexType,typename EdgeType>
EdgeType MyMatrixGraph<VertexType,EdgeType>::getWeight(int v1,int v2){
	return (v1!=-1 && v2!=-1)?Edge[v1][v2]:0;
}

//插入结点
template<typename VertexType,typename EdgeType>
bool MyMatrixGraph<VertexType,EdgeType>::insertVertex(const VertexType& vertex){
	if(numVertices == maxVertices)
		return false;
	VerticesList[numVertices++] = vertex;
	return true;
}

//插入边
template<typename VertexType,typename EdgeType>
bool MyMatrixGraph<VertexType,EdgeType>::inertEdge(int v1,int v2,EdgeType cost){
	if(v1>-1 && v1<numVertices && v2>-1 && v2<numVertices){
		if(Edge[v1][v2] < 0){
			Edge[v1][v2] = cost;
			numEdges++;
			return true;
		}else{
		    cout<<"该边已经存在"<<endl;
			return false;
		} 	
	}
	return false;
}

//删除结点
template<typename VertexType,typename EdgeType>
bool MyMatrixGraph<VertexType,EdgeType>::removeVertex(int v){
	//判断输入是否合理
	if(numVertices==1 || v<0 || v>=numVertices)
		return false;
	//先调整结点
	numVertices--;
	VerticesList[v] = VerticesList[numVertices];
	//再调整边
	for(int i=0;i<numVertices;i++){
		if(Edge[i][v] >= 0){
			numEdges--;  //先把边数减掉
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

//删除边
template<typename VertexType,typename EdgeType>
bool MyMatrixGraph<VertexType,EdgeType>::removeEdge(int v1,int v2){
	if(v1>-1 && v1<numVertices && v2>-1 &&v2<numVertices && Edge[v1][v2]>=0){
		Edge[v1][v2] = -1;
		numEdges--;
		return true;
	}else{
		cout<<"该边不存在或输入有误，请检查"<<endl;
		return false;
	}
}

//图输入
template<typename VertexType,typename EdgeType>
void MyMatrixGraph<VertexType,EdgeType>::inputGraph(){
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
			break;
		}else{
			if(this->inertEdge(m,n,weight)){
				j++;
			}
		}
	}
}

//图输出
template<typename VertexType,typename EdgeType>
void MyMatrixGraph<VertexType,EdgeType>::outputGraph(){
	int num_Vertices = this->NumofVertices(); // 结点数
	int num_Edges = this->NumofEdges();    //边数
	cout<<"该图的结点数目为："<<num_Vertices<<" "<<"边的数目为："<<num_Edges<<endl;
	
	cout<<"该图的结点分别为：";
	for(int i=0;i<num_Vertices;i++){
		cout<<VerticesList[i]<<" ";
	}
	cout<<endl;
	
	cout<<"该图的边分别为："<<endl;
	int weight;
	VertexType v1,v2;
	for(int i=0;i<num_Vertices;i++){
		for(int j=0;j<num_Vertices;j++){   //因为一条边只输出一次，所以用这种方法
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