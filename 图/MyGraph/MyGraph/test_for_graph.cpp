#include<iostream>
#include"MyLinkDirectedGraph.h"
#include"MyLinkUnDirectedGraph.h"
#include"MyMatrixDirectedGraph.h"
#include"MyMatrixUnDirectedGraph.h"

using namespace std;

int main(){
	//ͼ
	//////�����ڽ����������ͼ
	cout<<"�����ڽ����������ͼ"<<endl;
	MyLinkUnDirectedGraph<char,int> g(30);
	//����ͼ�Ļ������ʵ���֤
	/*char ch1,ch2;
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

	//����ͼ�㷨��֤
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
	//�����������
	cout<<"�����������"<<endl;
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
	//�����������
	cout<<"�����������"<<endl;
	g2.DFS();*/

	
	//////�����ڽ����������ͼ
	cout<<endl;
	cout<<endl;
	cout<<"�����ڽ����������ͼ:"<<endl;
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
	//cout<<"�����������"<<endl;
	//g3.DFS();
	cout<<"��������"<<endl;
	cout<<endl;
	g3.topological_sort();



	/*//////���ھ��������ͼ
	MyMatrixDirectedGraph<char,int> r(30);
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
    r.outputGraph();*/

	//////���ھ��������ͼ
	/*MyMatrixUnDirectedGraph<char,int> r(30);
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
    r.outputGraph();*/



}