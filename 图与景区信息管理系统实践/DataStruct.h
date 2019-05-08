#pragma once
#include<iostream>

#define StrMAX 20
#define numMAX 20

//顶点信息
struct Vex
{
	int num;//序号
	char name[StrMAX];//景点名称
	char desc[StrMAX];//景点描述
};

//边的信息
struct Edge
{
	int vex1;
	int vex2;
	int weight;//权值
};

//深度优先遍历的路径
typedef struct Path
{
	int Vexs[numMAX] = { 0 };
	Path *next;
};//*Path;