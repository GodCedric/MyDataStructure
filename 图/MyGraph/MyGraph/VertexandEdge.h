#ifndef __VERTEXANDEDGE__H__
#define __VERTEXANDEDGE__H__

enum Color{WHITE,GRAY,BLACK};

//�����
template<typename VertexType,typename EdgeType> 
struct Edge{
	int dest;  //�ߵ���һ�����λ��
	EdgeType cost;   //�ߵ�Ȩֵ
	Edge<VertexType,EdgeType> *link;  //ָ�룬ָ����һ����

	Edge(){}    //Ĭ�Ϲ��캯��
	Edge(int num,EdgeType weight):dest(num),cost(weight),link(NULL){}   //���캯��

};

//������
template<typename VertexType,typename EdgeType> 
struct Vertex{
	VertexType data;                //�����
	//��������������
	Color color;//��ɫ
	int d;//·����(��ʵʱ��)
	int f;
	int i;
	Vertex* pi;//���ǰ��

	Edge<VertexType,EdgeType> *adj; //����ͷָ��

	Vertex():color(WHITE),d(INT_MAX),f(0),pi(NULL),adj(NULL){}
};



#endif