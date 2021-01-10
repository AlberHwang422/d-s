#include"system.h"
#include"tool.h"
#include<iostream>
#include<Windows.h>
#include<time.h>
using namespace std;
/*
* 名称：menu()
* 描述：生成系统菜单
* 参数：
* 返回：
* 注意：
*/
void menu() {
	cout << "课程名称    : 数据结构课程设计" << endl;
	cout<<"文件名称    : 电梯模拟 VS2017版.exe"<<endl;
	cout<< "测试平台    : Windows 10 Education"<<endl;
	cout<< "开发环境    : Microsoft Visual Studio 2017" <<endl;
	cout<<"作者        :黄成彬"<<endl;
}

/*
* 名称：InitLiftSys()
* 描述：对电梯系统的一些参数初始化
* 参数：
* 返回：
* 注意：
*/
void InitLiftSys(int& NumOfClint, int&giveupfrom, int&giveupto, int&infrom, int&into,int& time2,int& time3,int& endtime) {
	cout << "请输入系统模拟运行时间(秒)" <<endl <<"请输入:";
	cin >> endtime;
	cout << endl;
	
	cout << "请输入初始乘客数量（人）" << endl;
	cout << "Tips：若想测试电梯满载运行的情况，输入较大数字"
		<< endl << "      若想测试电梯间断运行的情况，输入较小数字" << endl;
	cout << "请输入：";
	cin >> NumOfClint;

	cout << endl << "请输入乘客所容忍的时间范围（s）" << endl
		<< "如：10-15" << endl;
	cout << "请输入：";
	scanf_s("%d-%d", &giveupfrom, &giveupto);

	cout << endl << "请输入新建乘客的时间间隔（s）" << endl
		<< "如：10-15" << endl;
	cout << "请输入：";
	scanf_s("%d-%d", &infrom, &into);
	giveupfrom *= 1000;
	giveupto *= 1000;
	infrom *= 1000;
	into *= 1000;
	background();
	time2 = clock();
	time3 = RefreshTime(time2);

}

