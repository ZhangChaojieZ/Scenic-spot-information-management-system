#pragma once
#include<iostream>
#include"DataStruct.h"

using namespace std;

class Graph
{
private:
	int AdMatrix[numMAX][numMAX] = { 0 };	//�ڽӾ���
	Vex Vexs[numMAX];				//��ļ���
	Edge Edges[numMAX];				//�ߵļ��ϣ��Լ��ӵģ�
	int VexNum=0;						//��ĸ���
	int EdgeNum=0;					//�ߵ��������Լ��ӵģ�
public:
	//Graph();
	//~Graph();
	void InitAdMatrix();//��ʼ���ڽӾ���
	void test();
	bool InsertVex(Vex svex);//��Ӷ��㵽����������
	Vex GetVex(int index);//�õ�ָ��λ�ö���
	void SetVexNum(int num);//�޸Ķ�����Ŀ
	int GetVexNum();//��ý����
	bool InsertEdge(Edge sedge);//���߱��浽�ڽӾ�����
	Edge GetEdge(int vex1, int vex2);//�õ�ָ����
	void SetEdgeNum(int num);//�޸ıߵ���Ŀ���Լ��ӵģ�
	int GetEdgeNum();//�õ��ߵ���Ŀ���Լ��ӵģ�
	int FindAdjSpots(int index, Edge *Edges);//��ѯ��ָ�����������ı�
	int DFSTraverse(int nVex, Path *pList);//��ñ������
	int DFSTraverse2(int nVex, Path *&pList);
	int FindShortPath(int nVexStart, int nVexEnd, int aPath[][numMAX], int &number);//��������·��
	void FindMinTree(Edge aPath[]);//������С������
private:
	void DFS(int nVex, bool bVisted[], int &nIndex, Path *pList);//����
	void DFS2(int nVex, bool bVisted[], int aPath[], int &nIndex, Path *&pList);
};
