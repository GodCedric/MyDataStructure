#ifndef __MYLINKDIRECTEDGRAPH__H__
#define __MYLINKDIRECTEDGRAPH__H__

/*********基于邻接链表的有向图类*********/
#include"MyGraph.h"
#include"VertexandEdge.h"
#include<queue>
#include<list>


//邻接链表表示的图
template<typename VertexType,typename EdgeType> 
class MyLinkDirectedGraph:public MyGraph<VertexType,EdgeType>{
public:
	//构造析构
	MyLinkDirectedGraph(int sz = DefaultVertices);
	~MyLinkDirectedGraph();
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
	//int getFirstNeighbor(int v);          //取结点v的第一个邻接点
	//int getNextNeighbor(int v,int w);     //取邻接结点w的下一个邻接结点
	bool insertVertex(const VertexType& vertex);   //插入结点
	bool insertEdge(int v1,int v2,EdgeType cost);   //插入边
	bool removeVertex(int v);             //删除结点
	bool removeEdge(int v1,int v2);       //删除边(v1,v2)
	//成员函数
	void BFS(VertexType sv);    //广度优先搜索
	void DFS();                 //深度优先搜索
	void topological_sort();    //拓扑排序
	void Kosaraju();            //Kosaraju算法求解强连通分量
	void inputGraph();
	void outputGraph();
	
private:
	Vertex<VertexType,EdgeType>* NodeTable;   //结点表 

	void DFS_visit(Vertex<typename VertexType,typename EdgeType>& u,int& time);    //深度优先搜索辅助函数
	MyLinkDirectedGraph<VertexType,EdgeType>* reverse_graph();     //求解图的转置
	void reverseindex(int num_Vertices,int num_Edges,vector<int>& finishtime,vector<int>& sortindex);   //求结束时间的逆序
	void KosarajuDFS(MyLinkDirectedGraph<VertexType,EdgeType>* GT,vector<int>& newold,list<list<VertexType>>& SCC);  //求强连通分量
	void KosarajuDFSvisit(int j,list<VertexType>& single_SCC,vector<Color> color);
};

//构造函数
template<typename VertexType,typename EdgeType> 
MyLinkDirectedGraph<VertexType,EdgeType>::MyLinkDirectedGraph(int sz){
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
MyLinkDirectedGraph<VertexType,EdgeType>::~MyLinkDirectedGraph(){
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
VertexType MyLinkDirectedGraph<VertexType,EdgeType>::getValue(int i){          //获取结点值
	return (i>=0 && i<numVertices)?NodeTable[i].data:0;
}


//返回边的权重
////v1，v2表示结点位置，如果两个结点之间存在边，则返回该边的权重，否则返回0
template<typename VertexType,typename EdgeType> 
EdgeType MyLinkDirectedGraph<VertexType,EdgeType>::getWeight(int v1,int v2){
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

/*//获取结点v的第一个邻接点
template<typename VertexType,typename EdgeType> 
int MyLinkDirectedGraph<VertexType,EdgeType>::getFirstNeighbor(int v){
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
int MyLinkDirectedGraph<VertexType,EdgeType>::getNextNeighbor(int v,int w){   //这里w要是v的一个邻接点
	if(v != -1){
		Edge<typename VertexType,typename EdgeType> *p = NodeTable[v].adj;
		while(p && p->dest!=w)    //先找到w
			p = p->link;
		if(p && p->link)
			return p->link->dest;
	}
	return -1;
}*/

//插入结点
template<typename VertexType,typename EdgeType> 
bool MyLinkDirectedGraph<VertexType,EdgeType>::insertVertex(const VertexType& vertex){    //输入值为结点名
	if(numVertices == maxVertices)
		return false;
	NodeTable[numVertices].data = vertex;
	NodeTable[numVertices].i = numVertices;
	numVertices++;
	return true;
}

//插入边
template<typename VertexType,typename EdgeType> 
bool MyLinkDirectedGraph<VertexType,EdgeType>::insertEdge(int v1,int v2,EdgeType weight){
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
		v1p->dest = v2;
		v1p->cost = weight;
		v1p->link = NodeTable[v1].adj;  //把v1结点本来的邻接表接到新建的Edge的link上
		NodeTable[v1].adj = v1p;        //并把新建的Edge放到v1结点邻接表的表头

		numEdges++; //边加1
		return true;
	}
	return false;
}

//删除结点
template<typename VertexType,typename EdgeType> 
bool MyLinkDirectedGraph<VertexType,EdgeType>::removeVertex(int v){
	//先判断下结点v是否合理
	if(v<0 || v>=numVertices || numVertices==1)  //只有1个结点先不让删除
		return false;
	//删除结点，首先要把与这个结点相关的边全删除掉
	Edge<VertexType,EdgeType> *p;

	while(NodeTable[v].adj){
		p = NodeTable[v].adj;
		NodeTable[v].adj = p->link;
		delete p;
		numEdges--;
	}
	//边删完了 现在要把点删掉，那么点的个数少了一个，就把原来放最后面的点放到v的位置，并把numVertices--
	numVertices--;
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
	return true;
}

//删除边
template<typename VertexType,typename EdgeType> 
bool MyLinkDirectedGraph<VertexType,EdgeType>::removeEdge(int v1,int v2){
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

		numEdges--;
		return true;
	}
	return false;
}

//图的输入与构造
template<typename VertexType,typename EdgeType> 
void MyLinkDirectedGraph<VertexType,EdgeType>::inputGraph(){
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
			if(this->insertEdge(m,n,weight)){
				j++;
			}
		}
	}
}

//图的输出
template<typename VertexType,typename EdgeType> 
void MyLinkDirectedGraph<VertexType,EdgeType>::outputGraph(){
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
		for(int j=0;j<num_Vertices;j++){   //因为一条边只输出一次，所以用这种方法
			weight = this->getWeight(i,j);
			if(weight>0){
				v1 = this->getValue(i);
				v2 = this->getValue(j);
				cout<<"("<<v1<<","<<v2<<","<<weight<<")"<<endl;
			}
		}
	}
}

//图的广度优先搜索
template<typename VertexType,typename EdgeType> 
void MyLinkDirectedGraph<VertexType,EdgeType>::BFS(VertexType sv){
	int num_Vertices = this->NumofVertices(); // 结点数
	//初始化
	for(int i=0;i<num_Vertices;i++){
		NodeTable[i].color = WHITE;
		NodeTable[i].d = INT_MAX;
		NodeTable[i].pi = NULL; 
	}
	int x = getVertexPos(sv);
	if(x == -1){
		cout<<"输入有误"<<endl;
		return;
	}
	Vertex<typename VertexType,typename EdgeType>& s = NodeTable[x];
	s.color = GRAY;
	s.d = 0;
	s.pi = NULL;
	queue<Vertex<typename VertexType,typename EdgeType>> Q;
	Q.push(s);
	while(!Q.empty()){
		Vertex<typename VertexType,typename EdgeType> u = Q.front();
		Q.pop();
		Edge<typename VertexType,typename EdgeType>* uadj = u.adj;
		while(uadj!=NULL){
			Vertex<typename VertexType,typename EdgeType>& v = NodeTable[uadj->dest];
			if(v.color == WHITE){
				v.color = GRAY;
				v.d = u.d + 1;
				v.pi = &u;
				Q.push(v);
			}
			uadj = uadj->link;
		}
		u.color = BLACK;
		cout<<u.data<<"("<<u.d<<")"<<"  ";
	}
}

//图的深度优先搜索
template<typename VertexType,typename EdgeType> 
void MyLinkDirectedGraph<VertexType,EdgeType>::DFS_visit(Vertex<typename VertexType,typename EdgeType>& u,int& time){
	time = time + 1;
	u.d = time;
	u.color = GRAY;
	Edge<typename VertexType,typename EdgeType>* uadj = u.adj;
	while(uadj!=NULL){
		Vertex<typename VertexType,typename EdgeType>& v = NodeTable[uadj->dest];
		if(v.color == WHITE){
			v.pi = &u;
			DFS_visit(v,time);
		}
		uadj = uadj->link;
	}
	u.color = BLACK;
	time = time + 1;
	u.f = time;
	cout<<u.data<<"("<<u.d<<"/"<<u.f<<")"<<"  ";
}


template<typename VertexType,typename EdgeType> 
void MyLinkDirectedGraph<VertexType,EdgeType>::DFS(){
	//初始化
	int time = 0;
	int num_Vertices = this->NumofVertices(); // 结点数
	for(int i=0;i<num_Vertices;i++){
		NodeTable[i].color = WHITE;
		NodeTable[i].pi = NULL; 
	}
	for(int i=0;i<num_Vertices;i++){
		Vertex<typename VertexType,typename EdgeType>& u = NodeTable[i];
		if(u.color == WHITE)
			DFS_visit(u,time);
	}
}

//拓扑排序
template<typename VertexType,typename EdgeType> 
void MyLinkDirectedGraph<VertexType,EdgeType>::topological_sort(){
	//首先深度搜索
	this->DFS();
	//根据结束时间倒序输出
	cout<<endl;
	cout<<"拓扑排序结果"<<endl;
	int num_Vertices = this->NumofVertices(); // 结点数
	vector<int> res1(num_Vertices);
	vector<VertexType> res2(num_Vertices);
	for(int i=0;i<num_Vertices;i++){
		res1[i] = NodeTable[i].f;
		res2[i] = NodeTable[i].data;
	}
	//倒序输出
	for(int i=0;i<num_Vertices;i++){	
		int max = -1;
		int index;
		for(int j=0;j<num_Vertices;j++){
			if(res1[j] > max){
				max = res1[j];
				index = j;
			}
		}
		if(i<num_Vertices-1)
			cout<<res2[index]<<"->";
		else
			cout<<res2[index];
		res1[index] = INT_MIN;
	}
	cout<<endl;
}


//Kosaraju算法求解强连通分量
template<typename VertexType,typename EdgeType> 
void MyLinkDirectedGraph<VertexType,EdgeType>::Kosaraju(){
	//第一步先DFS
	this->DFS();
	//求结束时间的倒序
	int num_Vertices = this->NumofVertices();
	int num_Edges = this->NumofEdges();
	vector<int> finishtime(num_Vertices);
	vector<int> sortindex(num_Vertices);
	reverseindex(num_Vertices,num_Edges,finishtime,sortindex);
	//求转置图
	MyLinkDirectedGraph<VertexType,EdgeType>* GT = reverse_graph();
	GT->outputGraph();
	//倒序访问GT
	list<list<VertexType>> SCC;   //二维链表存储强连通分量
	KosarajuDFS(GT,sortindex,SCC);

	delete GT;  //注意释放空间
}

template<typename VertexType,typename EdgeType> 
void MyLinkDirectedGraph<VertexType,EdgeType>::reverseindex(int num_Vertices,int num_Edges,vector<int>& finishtime,vector<int>& sortindex){
	for(int i=0;i<num_Vertices;i++){
		finishtime[i] = NodeTable[i].f;
	}
	vector<int> finishtime2 = finishtime;
	for(int i=0;i<num_Vertices;i++){
		int max = -1;
		int index;
		for(int j=0;j<num_Vertices;j++){
			if(finishtime2[j] > max){
				max = finishtime2[j];
				index = j;
			}
		}
		sortindex[i] = index;
		finishtime2[index] = -1;
	}
}

template<typename VertexType,typename EdgeType> 
MyLinkDirectedGraph<VertexType,EdgeType>* MyLinkDirectedGraph<VertexType,EdgeType>::reverse_graph(){
	MyLinkDirectedGraph<VertexType,EdgeType>* GT = new MyLinkDirectedGraph<VertexType,EdgeType>();
	//std::shared_ptr<MyLinkDirectedGraph<VertexType,EdgeType>> GT(new MyLinkDirectedGraph<VertexType,EdgeType>());
	for(int i=0;i<NumofVertices();i++){
		//插入结点
		GT->insertVertex(getValue(i));
	}
	for(int i=0;i<NumofVertices();i++){
		//反向插入边
		Edge<VertexType,EdgeType> *p = NodeTable[i].adj;//取出结点对应的边链表的头指针
		while(p){
			GT->insertEdge(p->dest,i,p->cost);
			p = p->link;
		}	
	}
	return GT;
}

//求强连通分量
template<typename VertexType,typename EdgeType>
void MyLinkDirectedGraph<VertexType,EdgeType>::KosarajuDFS(MyLinkDirectedGraph<VertexType,EdgeType>* GT,vector<int>& newold,list<list<VertexType>>& SCC){
	int n = NumofVertices();
	vector<Color> color(n,WHITE);
	//循环迭代，顺序为结束时间逆序
	for(int i=0;i<n;i++){
		int j = newold[i];     //第i次访问第newold[i]个结点
		if(color[j] != WHITE)
			continue;
		//创建一个联通区域
		list<VertexType> single_SCC;
		//递归搜索
		KosarajuDFSvisit(j,single_SCC,color);
		SCC.push_back(single_SCC);
	}
}

template<typename VertexType,typename EdgeType>
void MyLinkDirectedGraph<VertexType,EdgeType>::KosarajuDFSvisit(int j,list<VertexType>& single_SCC,vector<Color> color){
	color[j] = GRAY;
	single_SCC.push_back(NodeTable[j].data);
	int cnt = 0;
	Edge<typename VertexType,typename EdgeType>* uadj = NodeTable[j].adj;
	while(uadj!=NULL){
		Vertex<typename VertexType,typename EdgeType>& v = NodeTable[uadj->dest];
		if(v.color == WHITE){
			cnt++;
		}
		uadj = uadj->link;
	}
	if(cnt == 0)
		return;
	vector<Vertex<typename VertexType,typename EdgeType>> e(cnt);
	uadj = NodeTable[j].adj;
	cnt = 0;
	while(uadj!=NULL){
		Vertex<typename VertexType,typename EdgeType>& v = NodeTable[uadj->dest];
		if(v.color == WHITE){
			e[cnt++] = v;
		}
		uadj = uadj->link;
	}
	
	int maxidx;
	for(int i=0;i<e.size();i++){
		maxidx = i;
		for(int k = i+1;k<e.size();j++){
			if(e[k].f > e[maxidx].f){
				maxidx = k;
			}
		}
		if(maxidx != i){
			swap(e[i],e[maxidx]);
		}
	}

	for(int k=0;k<e.size();k++){
		int j = e[k].i;
		KosarajuDFSvisit(j,single_SCC,color);
	}
}

#endif