#include<iostream>
#include<string>
#include"Tourism.h"
#include"Graph.h"
#include"DataStruct.h"

using namespace std;

int main()
{
	string input;//�˵����
	Tourism tourism;
	while (true)
	{
		cout << "********������Ϣ����ϵͳ********" << endl;
		cout << "\t1.��������������Ϣͼ\n\t2.��ѯ������Ϣ\n\t3.���ξ��㵼��\n\t4.�������·��\n\t5.������·�滮\n\t0.�˳�" << endl;
		cout << "�����������ţ�0~5����" << endl;

		cin >> input;
		cin.clear();//���������
		cin.sync();//����cin��ʶ����clear������sync����һ��ʹ�ã���ջ����������ݣ�����Ӱ����һ������

		if (input == "1")
		{
			if (tourism.CreatGraph())
			{
				cout << "ͼ�����ɹ���" << endl << endl;
			}
			else
			{
				cout << "ͼ����ʧ�ܣ�" << endl << endl;
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
			cout << "�˳���������ϵͳ��ллʹ�ã�" << endl;
			return 0;
		}
	}

	return 0;
}