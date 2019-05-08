#include<iostream>
#include<string>
#include<fstream>
#include"DataStruct.h"
#include"Graph.h"
#include"Tourism.h"

using namespace std;

bool Tourism::CreatGraph()
{
	if (graph.GetVexNum() != 0)
	{
		cout << "�Ѿ�����ͼ������Ҫ�ظ�������" << endl;
		return true;
	}

	ifstream FileVex;
	ifstream FileEdge;
	int vexCount;//���ļ��еĶ������
	Vex temp_vex;//��ȡ�����ļ���
	Edge temp_Edge;//��ȡ���ļ���

	FileVex.open("Vex.txt", ios::in);
	FileEdge.open("Edge.txt", ios::in);

	if (!FileVex.is_open())
	{
		cout << "������Ϣ�ļ���ʧ�ܣ�" << endl;
		return false;
	}

	if (!FileEdge.is_open())
	{
		cout << "����Ϣ�ļ���ʧ�ܣ�" << endl;
		return false;
	}

	//FileVex.read((char*)&vexnum, sizeof(vexnum));
	FileVex >> vexCount;
	cout << "������Ŀ��" << vexCount << endl;

	cout << "*******������Ϣ*******" << endl;

	while (true)
	{
		//FileVex.read((char*)&temp_vex, sizeof(temp_vex));//������쳣
		FileVex >> temp_vex.num >> temp_vex.name >> temp_vex.desc;

		if (graph.InsertVex(temp_vex))
		{			
			cout << "��ӵ�"<<temp_vex.num<<"��������ɡ�����"<<temp_vex.name << endl;
			//i++;
		}
		if (FileVex.eof())
		{
			break;
		}
	}

	while (true)
	{
		//FileEdge.read((char*)&temp_Edge, sizeof(temp_Edge));
		FileEdge >> temp_Edge.vex1 >> temp_Edge.vex2 >> temp_Edge.weight;

		if (FileEdge.eof())
		{
			break;
		}

		if (graph.InsertEdge(temp_Edge))
		{
			cout << "��ӵ�" << temp_Edge.vex1 << "�����㵽��"<< temp_Edge.vex2 <<"������ı����\t"<<"���룺"<<temp_Edge.weight << endl;			
		}
	}

	graph.InitAdMatrix();

	graph.test();//��������
	ShowGraph();//����

	FileVex.close();
	FileEdge.close();

	return true;
}

void Tourism::ShowGraph()
{
	cout << "******������Ϣ******" << endl;
	for (int i = 0; i < graph.GetVexNum(); i++)
	{
		cout << i << "--" << graph.GetVex(i).name << "--" << graph.GetVex(i).desc << endl;
	}
}

void Tourism::GetSpotInfo()
{
	if (graph.GetVexNum() == 0)//�ж��Ƿ��Ѿ�����ͼ
	{
		cout << "���ȴ���ͼ��" << endl;
		return;
	}

	int index;
	Edge Edges[numMAX];
	Vex vex;

	cout << "******��ѯ������Ϣ******" << endl;
	for (int i = 0; i < graph.GetVexNum(); i++)
		cout << graph.GetVex(i).num << "-" << graph.GetVex(i).name << endl;

	cout << "������Ҫ��ѯ�Ķ�����ţ�";
	cin >> index;
	int k = graph.FindAdjSpots(index, Edges);

	vex = graph.GetVex(index);
	cout << vex.name << endl << vex.desc << endl;

	cout << "******�ܱ߷羰��******" << endl;
	for (int j = 0; j < k; j++)
	{
		cout << vex.name << "->" << graph.GetVex(Edges[j].vex2).name << "\t���룺" << Edges[j].weight << endl;
	}
	
	cout << endl;
	return;
}

void Tourism::TravelPath()//(int type)
{
	if (graph.GetVexNum() == 0)
	{
		cout << "���ȴ���ͼ��" << endl;
		return;
	}
	
	int inputVexNum;//��ʼ�����
	string inputPathNum;//type
	Path *pList = new Path;
	pList->next = NULL;
	Path *pHead = pList;
	int pathLength = 0;//·������(�Լ��������)

	cout << "******���ξ��㵼��******" << endl;
	for (int i = 0; i < graph.GetVexNum(); i++)
	{
		cout << i << "--" << graph.GetVex(i).name << "--" << graph.GetVex(i).desc << endl;
	}
	
	cout << "��������ʼ����ţ�";
	cin >> inputVexNum;

	if (inputVexNum<0 || inputVexNum>graph.GetVexNum())
	{
		cout << "�����������" << endl;
		return;
	}

	while (true)
	{
		cout << "*******·������ѡ��******" << endl;
		cout << "\t1.����·��\n\t2.����·��\n\t0.�˳����㵼��\n";
		cout << "������ѡ��";
		cin >> inputPathNum;

		if (inputPathNum == "1")
		{
			pathLength = 0;
			graph.DFSTraverse(inputVexNum, pList);//������ͷ��㲻Ϊ�գ���ͬ��DFS2			
			pList = pHead;
			cout << "��������·�����£�" << endl;

			for (int j = 0; j < graph.GetVexNum() - 1; j++)
			{
				cout << graph.GetVex(pList->Vexs[j]).name << "-->";
				pathLength += graph.GetEdge(pList->Vexs[j], pList->Vexs[j + 1]).weight;
			}
			cout << graph.GetVex(pList->Vexs[graph.GetVexNum() - 1]).name << "\t����Ϊ��" << pathLength << endl;

		}
		else if (inputPathNum == "2")
		{
			graph.DFSTraverse2(inputVexNum, pList);//������ͷ���Ϊ�գ���ͬ��DFS
			cout << "��������·�����£�" << endl;
			pList = pHead;
			int i = 1;

			while (pList->next != NULL)
			{
				pathLength = 0;
				cout << "·��" << i << "Ϊ��";
				i++;

				for (int j = 0; j < graph.GetVexNum() - 1; j++)
				{
					cout << graph.GetVex(pList->next->Vexs[j]).name << "-->";
					pathLength += graph.GetEdge(pList->Vexs[j], pList->Vexs[j + 1]).weight;
				}
				cout << graph.GetVex(pList->next->Vexs[graph.GetVexNum() - 1]).name << "\t����Ϊ��"<<pathLength<< endl;
				pList = pList->next;
			}
		}
		else if (inputPathNum == "0")
		{
			cout << "�˳����㵼����ллʹ�ã�" << endl;
			break;
		}
		else
		{
			cout << "ѡ���������" << endl;
			continue;
		}
	}

	delete pList;

	cout << endl;

	return;
}

void Tourism::FingShortPath()
{
	if (graph.GetVexNum() == 0)
	{
		cout << "���ȴ���ͼ��" << endl;
		return;
	}
	
	int StartVexNum;
	int EndVexNum;
	int aPath[numMAX][numMAX] = { 0 };//aPath[i][j]����Ӧ·���϶���j��ǰһ������Ķ����
	int number = 0;
	int PathLength = 0;//·������

	cout << "******��������·��******" << endl;
	for (int i = 0; i < graph.GetVexNum(); i++)
	{
		cout << i << "--" << graph.GetVex(i).name << "--" << graph.GetVex(i).desc << endl;
	}

	cout << "����������ţ�";
	cin >> StartVexNum;
	cout << "�������յ��ţ�";
	cin >> EndVexNum;

	number=graph.FindShortPath(StartVexNum, EndVexNum, aPath, number);
		
	//�����·���ݴ浽����һ��������
	int temp[numMAX] = { 0 };//��ʱ���·�����������
	int j = 1;
	temp[0] = EndVexNum;
	temp[j] = aPath[StartVexNum][EndVexNum];
	while (temp[j] != StartVexNum)
	{
		j++;
		temp[j] = aPath[StartVexNum][temp[j - 1]];
	}

	//������·��
	cout << "���·��Ϊ��";
	for (; j >0; j--)
	{
		cout << graph.GetVex(temp[j]).name << "->";
	}
	cout << graph.GetVex(temp[j]).name;

	cout << endl;
	cout << "��̾���Ϊ��" << number;
	cout << endl;

	cout << endl;
	return;
}

void Tourism::DesignPath()
{
	if (graph.GetVexNum() == 0)
	{
		cout << "���ȴ���ͼ��" << endl;
		return;
	}

	Edge aPath[numMAX];
	int pathLength = 0;//�ܹ滮����

	graph.FindMinTree(aPath);

	cout << "******��·�滮******" << endl;
	cout << "�ֱ�����������������·��" << endl;

	for (int i = 0; i < graph.GetVexNum()-1; i++)//
	{
		cout << graph.GetVex(aPath[i].vex1).name << "--";
		cout << graph.GetVex(aPath[i].vex2).name;
		cout << "\t���룺" << aPath[i].weight << "m" << endl;
		pathLength += aPath[i].weight;
	}
	cout <<"�����·�ܳ���Ϊ��" << pathLength << endl;

	cout << endl;
	return;
}