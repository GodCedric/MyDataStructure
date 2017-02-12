#include<iostream>
#include"MyLinkDirectedGraph.h"
#include"MyLinkUnDirectedGraph.h"
#include"MyMatrixDirectedGraph.h"
#include"MyMatrixUnDirectedGraph.h"

using namespace std;

int main(){
	//图
	//////基于邻接链表的无向图
	cout<<"基于邻接链表的无向图"<<endl;
	MyLinkUnDirectedGraph<char,int> g(30);
	//无向图的基本性质的验证
	/*char ch1,ch2;
	int weight;
	g.inputGraph();
	g.outputGraph();
	cout<<"顶点数和边数："<<g.NumofVertices()<<" "<<g.NumofEdges()<<endl;
	cout<<"插入顶点:";  
    cin >>ch1;  
    g.insertVertex(ch1);  //插入点  
    cout<<"插入边："<<endl;  
    cin >>ch1>>ch2>>weight;  
	g.inertEdge(g.getVertexPos(ch1),g.getVertexPos(ch2),weight);//插入边
	g.outputGraph();
	cout<<"删除边：";  
    cin >>ch1>>ch2;  
    g.removeEdge(g.getVertexPos(ch1),g.getVertexPos(ch2)); //删除边  
  
    cout<<"删除点：";  
    cin>>ch1;  
    g.removeVertex(g.getVertexPos(ch1));  
    g.outputGraph(); 

	//基本图算法验证
	const int m = 8;
	char vertexs[m] = {'r','s','t','u','v','w','x','y'};
	for(int i=0;i<m;i++){
		g.insertVertex(vertexs[i]);
	}
	g.inertEdge(0,1,1);
	g.inertEdge(0,4,1);
	g.inertEdge(1,5,1);
	g.inertEdge(5,2,1);
	g.inertEdge(5,6,1);
	g.inertEdge(2,6,1);
	g.inertEdge(2,3,1);
	g.inertEdge(3,6,1);
	g.inertEdge(6,7,1);
	g.inertEdge(3,7,1);
	g.outputGraph();
	//广度优先搜索
	cout<<"广度优先搜索"<<endl;
	g.BFS('s');
	cout<<endl;

	MyLinkUnDirectedGraph<char,int> g2(30);
	const int m2 = 6;
	char vertexs2[m2] = {'u','v','w','x','y','z'};
	for(int i=0;i<m2;i++){
		g2.insertVertex(vertexs2[i]);
	}
	g2.inertEdge(0,1,1);
	g2.inertEdge(0,3,1);
	g2.inertEdge(3,1,1);
	g2.inertEdge(4,3,1);
	g2.inertEdge(1,4,1);
	g2.inertEdge(2,4,1);
	g2.inertEdge(2,5,1);
	g2.inertEdge(5,5,1);
	g2.outputGraph();
	//深度优先搜索
	cout<<"深度优先搜索"<<endl;
	g2.DFS();*/

	
	//////基于邻接链表的有向图
	cout<<endl;
	cout<<endl;
	cout<<"基于邻接链表的有向图:"<<endl;
	MyLinkDirectedGraph<char,int> g3(30);
	const int m3 = 6;
	char vertexs3[m3] = {'u','v','w','x','y','z'};
	for(int i=0;i<m3;i++){
		g3.insertVertex(vertexs3[i]);
	}
	g3.inertEdge(0,1,1);
	g3.inertEdge(0,3,1);
	g3.inertEdge(3,1,1);
	g3.inertEdge(4,3,1);
	g3.inertEdge(1,4,1);
	g3.inertEdge(2,4,1);
	g3.inertEdge(2,5,1);
	g3.inertEdge(5,5,1);
	g3.outputGraph();
	//cout<<"深度优先搜索"<<endl;
	//g3.DFS();
	cout<<"拓扑排序"<<endl;
	cout<<endl;
	g3.topological_sort();



	/*//////基于矩阵的有向图
	MyMatrixDirectedGraph<char,int> r(30);
	char ch3,ch4;
	int weight2;
	r.inputGraph();
	r.outputGraph();
	cout<<"插入顶点:";  
    cin >>ch3;  
    r.insertVertex(ch3);  //插入点  
    cout<<"插入边："<<endl;  
    cin >>ch3>>ch4>>weight2;  
	r.inertEdge(r.getVertexPos(ch3),r.getVertexPos(ch4),weight2);//插入边
	r.outputGraph();
	cout<<"删除边：";  
    cin >>ch3>>ch4;  
    r.removeEdge(r.getVertexPos(ch3),r.getVertexPos(ch4)); //删除边  
  
    cout<<"删除点：";  
    cin>>ch3;  
    r.removeVertex(r.getVertexPos(ch3));  
    r.outputGraph();*/

	//////基于矩阵的无向图
	/*MyMatrixUnDirectedGraph<char,int> r(30);
	char ch3,ch4;
	int weight2;
	r.inputGraph();
	r.outputGraph();
	cout<<"插入顶点:";  
    cin >>ch3;  
    r.insertVertex(ch3);  //插入点  
    cout<<"插入边："<<endl;  
    cin >>ch3>>ch4>>weight2;  
	r.inertEdge(r.getVertexPos(ch3),r.getVertexPos(ch4),weight2);//插入边
	r.outputGraph();
	cout<<"删除边：";  
    cin >>ch3>>ch4;  
    r.removeEdge(r.getVertexPos(ch3),r.getVertexPos(ch4)); //删除边  
  
    cout<<"删除点：";  
    cin>>ch3;  
    r.removeVertex(r.getVertexPos(ch3));  
    r.outputGraph();*/



}