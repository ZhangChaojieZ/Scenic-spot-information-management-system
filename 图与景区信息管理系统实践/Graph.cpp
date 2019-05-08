#include<iostream>
#include<fstream>
#include"DataStruct.h"
#include"Graph.h"
#include"Tourism.h"

using namespace std;

void Graph::InitAdMatrix()
{
	for (int i = 0; i < EdgeNum; i++)
	{
		AdMatrix[Edges[i].vex1][Edges[i].vex2] = Edges[i].weight;
		AdMatrix[Edges[i].vex2][Edges[i].vex1] = Edges[i].weight;
	}
}

void Graph::test()
{
	for (int j = 0; j < 7; j++)
	{
		for (int k = 0; k < 7; k++)
			cout << AdMatrix[j][k] << "\t";
		cout << endl;
	}
}

bool Graph:: InsertVex(Vex svex)
{
	if (VexNum == numMAX)
	{
		cout << "顶点数目超出要求范围！" << endl;
		return false;
	}
	Vexs[VexNum] = svex;
	VexNum++;
	return true;
}

Vex Graph::GetVex(int index)
{
	return Vexs[index];
}

void Graph::SetVexNum(int num)
{
	VexNum = num;
}

int Graph::GetVexNum()
{
	return VexNum;
}

void Graph::SetEdgeNum(int num)
{
	EdgeNum = num;
}

int Graph::GetEdgeNum()
{
	return EdgeNum;
}

bool Graph::InsertEdge(Edge sedge)
{
	if (sedge.vex1 >= 0 && sedge.vex1 < VexNum&&sedge.vex2 >= 0 && sedge.vex2 < VexNum && sedge.vex1 != sedge.vex2)
	{
		//AdMatrix[sedge.vex1][sedge.vex2] = sedge.weight;
		Edges[EdgeNum++] = sedge;
		return true;
	}
	else
	{
		cout << "添加的边不符合要求，添加失败！" << endl;
		return false;
	}
}

Edge Graph::GetEdge(int vex1, int vex2)
{
	for (int i = 0; i < EdgeNum; i++)
	{
		if (Edges[i].vex1 == vex1 && Edges[i].vex2 == vex2)
			return Edges[i];
	}
}

int Graph::FindAdjSpots(int index, Edge *Edges)
{
	int k = 0;
	for (int i = 0; i < VexNum; i++)
	{
		if (AdMatrix[index][i] != 0)
		{
			Edges[k].weight = AdMatrix[index][i];
			Edges[k].vex1 = index;
			Edges[k].vex2 = i;
			k++;
		}
	}

	return k;
}

int Graph::DFSTraverse(int nVex, Path *pList)
{
	bool bVisitsd[numMAX] = { false };
	int nIndex = 0;

	DFS(nVex, bVisitsd, nIndex, pList);

	return 0;
}

int Graph::DFSTraverse2(int nVex, Path *&pList)
{
	bool bVisitsd[numMAX] = { false };
	int nIndex = 0;
	int aPath[numMAX] = { 0 };

	DFS2(nVex, bVisitsd, aPath, nIndex, pList);

	return 0;
}

int Graph::FindShortPath(int nVexStart, int nVexEnd, int aPath[][numMAX], int &number)
{
	int i, j, k;
	int dist[numMAX][numMAX] = { 0 };//存放i到j的路径距离

	for(i=0;i<VexNum;i++)
		for (j = 0; j < VexNum; j++)
		{
			if (AdMatrix[i][j] == 0)
			{
				dist[i][j] = 100000;
			}
			else
			{
				dist[i][j] = AdMatrix[i][j]; 
			}
			if (i != j && dist[i][j] < 100000)
			{
				aPath[i][j] = i;
			}
			else
			{
				aPath[i][j] = 0;
			}
		}

	for(k=0;k<VexNum;k++)
		for (i = 0; i < VexNum; i++)
			for (j = 0; j < VexNum; j++)
			{
				if (dist[i][k] + dist[k][j] < dist[i][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					aPath[i][j] = aPath[k][j];
				}
			}

	return dist[nVexStart][nVexEnd];
}

void Graph::FindMinTree(Edge aPath[])
{
	int min;
	bool bVisited[numMAX] = { false };
	bVisited[0] = true;

	int nVex1, nVex2;

	for (int i = 0; i < VexNum-1; i++)//vexNum个顶点选出vexNum-1条边就可以了
	{
		min = INT_MAX;//INT_MAX为int类型上限值
		for (int j = 0; j < VexNum; j++)//遍历所有构成树的顶点
		{			
			if (bVisited[j])//找到一个已构成树的结点
			{
				for (int k = 0; k < VexNum; k++)//遍历所有未构成树的顶点
				{
					if (!bVisited[k])
					{
						if (AdMatrix[j][k] != 0 && AdMatrix[j][k] < min)
						{
							min = AdMatrix[j][k];
							nVex1 = j;
							nVex2 = k;
						}
					}
				}
			}
		}

		aPath[i].vex1 = nVex1;
		aPath[i].vex2 = nVex2;
		aPath[i].weight = min;

		bVisited[nVex1] = true;//设为已访问
		bVisited[nVex2] = true;

	}

	return;
}

void Graph::DFS(int nVex, bool bVisted[], int &nIndex, Path *pList)
//回溯不出现重复路径，出现一条符合条件的路径就退出
{
	bVisted[nVex] = true;
	pList->Vexs[nIndex++] = nVex;//此处链表头结点不为空，不同于DFS2
	
	for (int i = 0; i < VexNum; i++)
	{
		if (AdMatrix[nVex][i] != 0 && bVisted[i] == false)
		{
			DFS(i, bVisted, nIndex, pList);
			if (nIndex == VexNum)
			{
				return;
			}
			bVisted[i] = false;
			nIndex--;
		}
	}
}

void Graph::DFS2(int nVex, bool bVisted[],int aPath[], int &nIndex, Path *&pList)//回溯法思想，不走重复结点
{
	bVisted[nVex] = true;
	aPath[nIndex++] = nVex;

	if (nIndex == VexNum)
	{
		//创建一个新结点，将当前的aPath中的数据保存起来（此处花费较长时间）
		//此链表头结点为空，不同于DFS
		Path *pNode = new Path;		
		for (int i = 0; i < nIndex; i++)
		{
			pNode->Vexs[i] = aPath[i];
		}
		pNode->next = NULL;
		pList->next = pNode;//添加新结点
		pList = pList->next;
	}
	else
	{
		for (int i = 0; i < VexNum; i++)
		{
			if (AdMatrix[nVex][i] != 0 && bVisted[i] == false)
			{
				DFS2(i, bVisted, aPath, nIndex, pList);
				bVisted[i] = false;
				nIndex--;
			}
		}
	}
}