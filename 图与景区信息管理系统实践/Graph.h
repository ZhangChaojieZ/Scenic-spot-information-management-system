#pragma once
#include<iostream>
#include"DataStruct.h"

using namespace std;

class Graph
{
private:
	int AdMatrix[numMAX][numMAX] = { 0 };	//邻接矩阵
	Vex Vexs[numMAX];				//点的集合
	Edge Edges[numMAX];				//边的集合（自己加的）
	int VexNum=0;						//点的个数
	int EdgeNum=0;					//边的条数（自己加的）
public:
	//Graph();
	//~Graph();
	void InitAdMatrix();//初始化邻接矩阵
	void test();
	bool InsertVex(Vex svex);//添加顶点到顶点数组中
	Vex GetVex(int index);//得到指定位置顶点
	void SetVexNum(int num);//修改顶点数目
	int GetVexNum();//获得结点数
	bool InsertEdge(Edge sedge);//将边保存到邻接矩阵中
	Edge GetEdge(int vex1, int vex2);//得到指定边
	void SetEdgeNum(int num);//修改边的数目（自己加的）
	int GetEdgeNum();//得到边的数目（自己加的）
	int FindAdjSpots(int index, Edge *Edges);//查询与指定顶点相连的边
	int DFSTraverse(int nVex, Path *pList);//获得遍历结果
	int DFSTraverse2(int nVex, Path *&pList);
	int FindShortPath(int nVexStart, int nVexEnd, int aPath[][numMAX], int &number);//两点间最短路径
	void FindMinTree(Edge aPath[]);//构造最小生成树
private:
	void DFS(int nVex, bool bVisted[], int &nIndex, Path *pList);//深搜
	void DFS2(int nVex, bool bVisted[], int aPath[], int &nIndex, Path *&pList);
};
