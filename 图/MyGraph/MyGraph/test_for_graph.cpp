#include<iostream>
#include"MyLinkGraph.h"
#include"MyMatrixGraph.h"

using namespace std;

int main(){
	//图
	//////基于邻接链表的图
	MyLinkGraph<char,int> g(30);
	char ch1,ch2;
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

	//////基于矩阵的图
	MyMatrixGraph<char,int> r(30);
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
    r.outputGraph();

}