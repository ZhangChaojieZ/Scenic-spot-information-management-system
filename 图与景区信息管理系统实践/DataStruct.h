#pragma once
#include<iostream>

#define StrMAX 20
#define numMAX 20

//������Ϣ
struct Vex
{
	int num;//���
	char name[StrMAX];//��������
	char desc[StrMAX];//��������
};

//�ߵ���Ϣ
struct Edge
{
	int vex1;
	int vex2;
	int weight;//Ȩֵ
};

//������ȱ�����·��
typedef struct Path
{
	int Vexs[numMAX] = { 0 };
	Path *next;
};//*Path;