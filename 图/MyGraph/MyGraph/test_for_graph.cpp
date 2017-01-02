#include<iostream>
#include"MyLinkGraph.h"
#include"MyMatrixGraph.h"

using namespace std;

int main(){
	//ͼ
	//////�����ڽ������ͼ
	MyLinkGraph<char,int> g(30);
	char ch1,ch2;
	int weight;
	g.inputGraph();
	g.outputGraph();
	cout<<"�������ͱ�����"<<g.NumofVertices()<<" "<<g.NumofEdges()<<endl;
	cout<<"���붥��:";  
    cin >>ch1;  
    g.insertVertex(ch1);  //�����  
    cout<<"����ߣ�"<<endl;  
    cin >>ch1>>ch2>>weight;  
	g.inertEdge(g.getVertexPos(ch1),g.getVertexPos(ch2),weight);//�����
	g.outputGraph();
	cout<<"ɾ���ߣ�";  
    cin >>ch1>>ch2;  
    g.removeEdge(g.getVertexPos(ch1),g.getVertexPos(ch2)); //ɾ����  
  
    cout<<"ɾ���㣺";  
    cin>>ch1;  
    g.removeVertex(g.getVertexPos(ch1));  
    g.outputGraph(); 

	//////���ھ����ͼ
	MyMatrixGraph<char,int> r(30);
	char ch3,ch4;
	int weight2;
	r.inputGraph();
	r.outputGraph();
	cout<<"���붥��:";  
    cin >>ch3;  
    r.insertVertex(ch3);  //�����  
    cout<<"����ߣ�"<<endl;  
    cin >>ch3>>ch4>>weight2;  
	r.inertEdge(r.getVertexPos(ch3),r.getVertexPos(ch4),weight2);//�����
	r.outputGraph();
	cout<<"ɾ���ߣ�";  
    cin >>ch3>>ch4;  
    r.removeEdge(r.getVertexPos(ch3),r.getVertexPos(ch4)); //ɾ����  
  
    cout<<"ɾ���㣺";  
    cin>>ch3;  
    r.removeVertex(r.getVertexPos(ch3));  
    r.outputGraph();

}