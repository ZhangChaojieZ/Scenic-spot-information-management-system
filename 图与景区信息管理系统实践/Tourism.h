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
	bool CreatGraph();//����������Ϣ��
	void ShowGraph();//���ԣ���ʾ������Ϣ
	void GetSpotInfo();//��ѯ����
	void TravelPath();// (int type);//���ξ��㵼��
	void FingShortPath();//������������·��
	void DesignPath();//��·�滮
};