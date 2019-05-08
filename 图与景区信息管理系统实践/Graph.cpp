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
		cout << "������Ŀ����Ҫ��Χ��" << endl;
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
		cout << "��ӵı߲�����Ҫ�����ʧ�ܣ�" << endl;
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
	int dist[numMAX][numMAX] = { 0 };//���i��j��·������

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

	for (int i = 0; i < VexNum-1; i++)//vexNum������ѡ��vexNum-1���߾Ϳ�����
	{
		min = INT_MAX;//INT_MAXΪint��������ֵ
		for (int j = 0; j < VexNum; j++)//�������й������Ķ���
		{			
			if (bVisited[j])//�ҵ�һ���ѹ������Ľ��
			{
				for (int k = 0; k < VexNum; k++)//��������δ�������Ķ���
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

		bVisited[nVex1] = true;//��Ϊ�ѷ���
		bVisited[nVex2] = true;

	}

	return;
}

void Graph::DFS(int nVex, bool bVisted[], int &nIndex, Path *pList)
//���ݲ������ظ�·��������һ������������·�����˳�
{
	bVisted[nVex] = true;
	pList->Vexs[nIndex++] = nVex;//�˴�����ͷ��㲻Ϊ�գ���ͬ��DFS2
	
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

void Graph::DFS2(int nVex, bool bVisted[],int aPath[], int &nIndex, Path *&pList)//���ݷ�˼�룬�����ظ����
{
	bVisted[nVex] = true;
	aPath[nIndex++] = nVex;

	if (nIndex == VexNum)
	{
		//����һ���½�㣬����ǰ��aPath�е����ݱ����������˴����ѽϳ�ʱ�䣩
		//������ͷ���Ϊ�գ���ͬ��DFS
		Path *pNode = new Path;		
		for (int i = 0; i < nIndex; i++)
		{
			pNode->Vexs[i] = aPath[i];
		}
		pNode->next = NULL;
		pList->next = pNode;//����½��
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