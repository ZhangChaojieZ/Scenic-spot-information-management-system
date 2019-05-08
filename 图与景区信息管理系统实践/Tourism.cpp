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
		cout << "已经创建图，不需要重复建立！" << endl;
		return true;
	}

	ifstream FileVex;
	ifstream FileEdge;
	int vexCount;//读文件中的顶点个数
	Vex temp_vex;//读取顶点文件用
	Edge temp_Edge;//读取边文件用

	FileVex.open("Vex.txt", ios::in);
	FileEdge.open("Edge.txt", ios::in);

	if (!FileVex.is_open())
	{
		cout << "顶点信息文件打开失败！" << endl;
		return false;
	}

	if (!FileEdge.is_open())
	{
		cout << "边信息文件打开失败！" << endl;
		return false;
	}

	//FileVex.read((char*)&vexnum, sizeof(vexnum));
	FileVex >> vexCount;
	cout << "顶点数目：" << vexCount << endl;

	cout << "*******顶点信息*******" << endl;

	while (true)
	{
		//FileVex.read((char*)&temp_vex, sizeof(temp_vex));//会出现异常
		FileVex >> temp_vex.num >> temp_vex.name >> temp_vex.desc;

		if (graph.InsertVex(temp_vex))
		{			
			cout << "添加第"<<temp_vex.num<<"个顶点完成———"<<temp_vex.name << endl;
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
			cout << "添加第" << temp_Edge.vex1 << "个顶点到第"<< temp_Edge.vex2 <<"个顶点的边完成\t"<<"距离："<<temp_Edge.weight << endl;			
		}
	}

	graph.InitAdMatrix();

	graph.test();//测试用例
	ShowGraph();//测试

	FileVex.close();
	FileEdge.close();

	return true;
}

void Tourism::ShowGraph()
{
	cout << "******景点信息******" << endl;
	for (int i = 0; i < graph.GetVexNum(); i++)
	{
		cout << i << "--" << graph.GetVex(i).name << "--" << graph.GetVex(i).desc << endl;
	}
}

void Tourism::GetSpotInfo()
{
	if (graph.GetVexNum() == 0)//判断是否已经建立图
	{
		cout << "请先创建图！" << endl;
		return;
	}

	int index;
	Edge Edges[numMAX];
	Vex vex;

	cout << "******查询景点信息******" << endl;
	for (int i = 0; i < graph.GetVexNum(); i++)
		cout << graph.GetVex(i).num << "-" << graph.GetVex(i).name << endl;

	cout << "请输入要查询的顶点序号：";
	cin >> index;
	int k = graph.FindAdjSpots(index, Edges);

	vex = graph.GetVex(index);
	cout << vex.name << endl << vex.desc << endl;

	cout << "******周边风景区******" << endl;
	for (int j = 0; j < k; j++)
	{
		cout << vex.name << "->" << graph.GetVex(Edges[j].vex2).name << "\t距离：" << Edges[j].weight << endl;
	}
	
	cout << endl;
	return;
}

void Tourism::TravelPath()//(int type)
{
	if (graph.GetVexNum() == 0)
	{
		cout << "请先创建图！" << endl;
		return;
	}
	
	int inputVexNum;//起始顶点号
	string inputPathNum;//type
	Path *pList = new Path;
	pList->next = NULL;
	Path *pHead = pList;
	int pathLength = 0;//路径长度(自己添加内容)

	cout << "******旅游景点导航******" << endl;
	for (int i = 0; i < graph.GetVexNum(); i++)
	{
		cout << i << "--" << graph.GetVex(i).name << "--" << graph.GetVex(i).desc << endl;
	}
	
	cout << "请输入起始顶点号：";
	cin >> inputVexNum;

	if (inputVexNum<0 || inputVexNum>graph.GetVexNum())
	{
		cout << "顶点输入错误！" << endl;
		return;
	}

	while (true)
	{
		cout << "*******路径条数选择******" << endl;
		cout << "\t1.单条路径\n\t2.多条路径\n\t0.退出景点导航\n";
		cout << "请输入选择：";
		cin >> inputPathNum;

		if (inputPathNum == "1")
		{
			pathLength = 0;
			graph.DFSTraverse(inputVexNum, pList);//此链表头结点不为空，不同于DFS2			
			pList = pHead;
			cout << "单条导游路线如下：" << endl;

			for (int j = 0; j < graph.GetVexNum() - 1; j++)
			{
				cout << graph.GetVex(pList->Vexs[j]).name << "-->";
				pathLength += graph.GetEdge(pList->Vexs[j], pList->Vexs[j + 1]).weight;
			}
			cout << graph.GetVex(pList->Vexs[graph.GetVexNum() - 1]).name << "\t距离为：" << pathLength << endl;

		}
		else if (inputPathNum == "2")
		{
			graph.DFSTraverse2(inputVexNum, pList);//此链表头结点为空，不同于DFS
			cout << "多条导游路线如下：" << endl;
			pList = pHead;
			int i = 1;

			while (pList->next != NULL)
			{
				pathLength = 0;
				cout << "路线" << i << "为：";
				i++;

				for (int j = 0; j < graph.GetVexNum() - 1; j++)
				{
					cout << graph.GetVex(pList->next->Vexs[j]).name << "-->";
					pathLength += graph.GetEdge(pList->Vexs[j], pList->Vexs[j + 1]).weight;
				}
				cout << graph.GetVex(pList->next->Vexs[graph.GetVexNum() - 1]).name << "\t距离为："<<pathLength<< endl;
				pList = pList->next;
			}
		}
		else if (inputPathNum == "0")
		{
			cout << "退出景点导航，谢谢使用！" << endl;
			break;
		}
		else
		{
			cout << "选择输入错误！" << endl;
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
		cout << "请先创建图！" << endl;
		return;
	}
	
	int StartVexNum;
	int EndVexNum;
	int aPath[numMAX][numMAX] = { 0 };//aPath[i][j]是相应路径上顶点j的前一个顶点的顶点号
	int number = 0;
	int PathLength = 0;//路径长度

	cout << "******景点间最短路径******" << endl;
	for (int i = 0; i < graph.GetVexNum(); i++)
	{
		cout << i << "--" << graph.GetVex(i).name << "--" << graph.GetVex(i).desc << endl;
	}

	cout << "请输入起点编号：";
	cin >> StartVexNum;
	cout << "请输入终点编号：";
	cin >> EndVexNum;

	number=graph.FindShortPath(StartVexNum, EndVexNum, aPath, number);
		
	//把最短路径暂存到另外一个数组中
	int temp[numMAX] = { 0 };//临时存放路径，用于输出
	int j = 1;
	temp[0] = EndVexNum;
	temp[j] = aPath[StartVexNum][EndVexNum];
	while (temp[j] != StartVexNum)
	{
		j++;
		temp[j] = aPath[StartVexNum][temp[j - 1]];
	}

	//输出最短路径
	cout << "最短路线为：";
	for (; j >0; j--)
	{
		cout << graph.GetVex(temp[j]).name << "->";
	}
	cout << graph.GetVex(temp[j]).name;

	cout << endl;
	cout << "最短距离为：" << number;
	cout << endl;

	cout << endl;
	return;
}

void Tourism::DesignPath()
{
	if (graph.GetVexNum() == 0)
	{
		cout << "请先创建图！" << endl;
		return;
	}

	Edge aPath[numMAX];
	int pathLength = 0;//总规划长度

	graph.FindMinTree(aPath);

	cout << "******电路规划******" << endl;
	cout << "分别在以下两点间铺设电路：" << endl;

	for (int i = 0; i < graph.GetVexNum()-1; i++)//
	{
		cout << graph.GetVex(aPath[i].vex1).name << "--";
		cout << graph.GetVex(aPath[i].vex2).name;
		cout << "\t距离：" << aPath[i].weight << "m" << endl;
		pathLength += aPath[i].weight;
	}
	cout <<"铺设电路总长度为：" << pathLength << endl;

	cout << endl;
	return;
}