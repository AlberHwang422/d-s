#include"system.h"
#include"tool.h"
#include<iostream>
#include<Windows.h>
#include<time.h>
using namespace std;
/*
* ���ƣ�menu()
* ����������ϵͳ�˵�
* ������
* ���أ�
* ע�⣺
*/
void menu() {
	cout << "�γ�����    : ���ݽṹ�γ����" << endl;
	cout<<"�ļ�����    : ����ģ�� VS2017��.exe"<<endl;
	cout<< "����ƽ̨    : Windows 10 Education"<<endl;
	cout<< "��������    : Microsoft Visual Studio 2017" <<endl;
	cout<<"����        :�Ƴɱ�"<<endl;
}

/*
* ���ƣ�InitLiftSys()
* �������Ե���ϵͳ��һЩ������ʼ��
* ������
* ���أ�
* ע�⣺
*/
void InitLiftSys(int& NumOfClint, int&giveupfrom, int&giveupto, int&infrom, int&into,int& time2,int& time3,int& endtime) {
	cout << "������ϵͳģ������ʱ��(��)" <<endl <<"������:";
	cin >> endtime;
	cout << endl;
	
	cout << "�������ʼ�˿��������ˣ�" << endl;
	cout << "Tips��������Ե����������е����������ϴ�����"
		<< endl << "      ������Ե��ݼ�����е�����������С����" << endl;
	cout << "�����룺";
	cin >> NumOfClint;

	cout << endl << "������˿������̵�ʱ�䷶Χ��s��" << endl
		<< "�磺10-15" << endl;
	cout << "�����룺";
	scanf_s("%d-%d", &giveupfrom, &giveupto);

	cout << endl << "�������½��˿͵�ʱ������s��" << endl
		<< "�磺10-15" << endl;
	cout << "�����룺";
	scanf_s("%d-%d", &infrom, &into);
	giveupfrom *= 1000;
	giveupto *= 1000;
	infrom *= 1000;
	into *= 1000;
	background();
	time2 = clock();
	time3 = RefreshTime(time2);

}

