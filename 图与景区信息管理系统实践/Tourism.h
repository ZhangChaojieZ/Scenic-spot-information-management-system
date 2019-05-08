#pragma once
#include<iostream>
#include<fstream>
#include"DataStruct.h"
#include"Graph.h"

using namespace std;

class Tourism
{
private:
	Graph graph;
public:
	//Tourism();
	//~Tourism();
	bool CreatGraph();//建立顶点信息库
	void ShowGraph();//测试，显示景点信息
	void GetSpotInfo();//查询景点
	void TravelPath();// (int type);//旅游景点导航
	void FingShortPath();//搜索景点间最短路径
	void DesignPath();//电路规划
};