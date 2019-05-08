#include<iostream>
#include<string>
#include"Tourism.h"
#include"Graph.h"
#include"DataStruct.h"

using namespace std;

int main()
{
	string input;//菜单编号
	Tourism tourism;
	while (true)
	{
		cout << "********景区信息管理系统********" << endl;
		cout << "\t1.创建景区景点信息图\n\t2.查询景点信息\n\t3.旅游景点导航\n\t4.搜索最短路径\n\t5.辅助电路规划\n\t0.退出" << endl;
		cout << "请输入操作编号（0~5）：" << endl;

		cin >> input;
		cin.clear();//清空数据流
		cin.sync();//更改cin标识符，clear（）和sync（）一起使用，清空缓冲区的数据，避免影响下一次输入

		if (input == "1")
		{
			if (tourism.CreatGraph())
			{
				cout << "图创建成功！" << endl << endl;
			}
			else
			{
				cout << "图创建失败！" << endl << endl;
			}
		}
		else if (input == "2")
		{
			tourism.GetSpotInfo();
		}
		else if (input == "3")
		{
			tourism.TravelPath();
		}
		else if (input == "4")
		{
			tourism.FingShortPath();
		}
		else if (input == "5")
		{
			tourism.DesignPath();
		}
		else if (input == "0")
		{
			cout << "退出景区管理系统，谢谢使用！" << endl;
			return 0;
		}
	}

	return 0;
}