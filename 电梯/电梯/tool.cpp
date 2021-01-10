#include"tool.h"
#include"Clint.h"
#include <stdlib.h>
#include<time.h>
#include<Windows.h>
#include<stdio.h>
#include"Lift.h"
#include<graphics.h>
#include<conio.h>
#include<iostream>
using namespace std;

/*
* 名称：Sleep
* 描述：延迟 time 毫秒，并且时刻监视
		是否已到创建一个人的时间，若是，则新建人
* 参数：延迟的时间（毫秒）
* 返回：
* 注意：
*/
void sleep(int time,		//延迟秒数
	int& time2, int& time3,	//系统已经运行时间秒,毫秒
	int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
	Lift& lift, int&giveupfrom, int&giveupto, int&infrom, int&into) 
{
	int t = clock();
	while ((clock() - t) < time) {
		Sleep(1);
		isRefreshTime(time2, time3);
		isInitClint(intime, time0, lift, giveupfrom, giveupto, infrom, into);
		isGivenUp(lift);
	}
}

/*
* 名称：sleepwithoutgiveup
* 描述：该楼层不会有人进行M6操作
		其他楼层则未必
* 参数：
* 返回：
* 注意：
*/
void sleepWithOutGiveUp(int time,	//延迟秒数
	int& time2, int& time3,	//系统已经运行时间秒,毫秒
	int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
	Lift& lift, int&giveupfrom, int&giveupto, int&infrom, int&into)
{
	int t = clock();
	while ((clock() - t) < time) {
		Sleep(1);
		isRefreshTime(time2, time3);
		isInitClint(intime, time0, lift, giveupfrom, giveupto, infrom, into);
		isGivenUp(lift, lift.getFloor());
	}
}

/*
* 名称：getRandnum
* 描述：返回某个范围内得随机数
* 参数：
* 返回：
* 注意：
*/
int getRandnum(int from, int to) {
	return (rand() % (to - from + 1)) + from;
}

/*
* 名称：intiClint
* 描述：生成一个乘客，并让该乘客加入排队队列
* 参数：
* 返回：下一额乘客生成的时间间隔
* 注意：
*/
int initClint(Lift& lift, int&giveupfrom, int&giveupto, int&infrom, int&into) {
	int infloor = getRandnum(1, 6);
	int outfloor;
	do{
		outfloor = getRandnum(1, 6);
	} while (infloor == outfloor);

	int giveuptime = getRandnum(giveupfrom, giveupto);
	Clint* clint1=new Clint(infloor, outfloor, giveuptime, clock());
	(*clint1)._M2(lift);	//按按钮
	(*clint1)._M3(lift);	//乘客执行M3排队操作

	return getRandnum(infrom, into);
}

/*
* 名称：isInitClint
* 描述：判断是否到了该新建一个人的时间
		若是则创建
* 参数：intime-下一个人出现的间隔，time0-上一个人生成的零点
		其他的为InitClint的参数
* 返回：
* 注意：
*/
void isInitClint(int& intime,int&time0,
	Lift& lift, int&giveupfrom, int&giveupto, int&infrom, int&into){
	if (clock() - time0 >= intime)
	{
		intime = initClint(lift,giveupfrom,giveupto,infrom,into);
		time0 = clock();
	}
}

/*
* 名称：RefreshTime（）
* 描述：刷新时间（演示界面）
* 参数：
* 返回：time3，表示系统运行时间
* 注意：
*/
int RefreshTime(int& time2) {
	int time3 = (clock() - time2) / 1000;
	drawTime(time3);
	return time3;
}

/*
* 名称：isRefreshTime
* 描述：判断是否应刷新显示时间
* 参数：time2-运行时间秒，
* 返回：
* 注意：
*/
void isRefreshTime(int&time2,int& time3) {
	if (clock() - time2 != time3)
		time3 = RefreshTime(time2);
}

/*
* 名称：isGiveUp
* 描述：判断是否有人放弃，并离队
* 参数：
* 返回：
* 注意：
*/
void isGivenUp(Lift& lift) {
	for (int i = 1; i <= LiftSize; i++) {
		lift._WaitingUp[i].moveGiveUpClint();
		lift._WaitingDown[i].moveGiveUpClint();
	}
}

/*
* 名称：isGiveUp
* 描述：判断是否有人放弃，并离队
		但是不判断thisfloor
* 参数：
* 返回：
* 注意：
*/
void isGivenUp(Lift& lift, int thisfloor) {
	for (int i = 1; i <= LiftSize; i++) {
		if (i == thisfloor)
			continue;
		else 
		{
			lift._WaitingUp[i].moveGiveUpClint();
			lift._WaitingDown[i].moveGiveUpClint();
		}
	}
}

/*
* 名称：background
* 描述：初始化背景画布
* 参数：
* 返回：
* 注意：
*/
void background() {
	initgraph(750, 602);

	line(100, 0, 100, 650);						//左
	line(300, 0, 300, 650);						//右

	for (int i = 100; i <= 600; i += 100)
	{
		line(300, i, 100, i);		//楼层分割
		line(310, i, 690, i);
	}
	for (int i = 49; i <= 550; i += 100)
		fillrectangle(300, i, 304, i + 45);		//电梯门
	for(int i=1;i<=550;i+=100)
		fillrectangle(300, i, 304, i + 45);


	for (int i = 1; i <= 5; i++)				//up按钮
	{
		setlinecolor(YELLOW);
		rectangle(310, i * 100 + 10, 340, i * 100 + 40);
		settextcolor(YELLOW);
		outtextxy(310 + 8, i * 100 + 17, _T("up"));
	}
	for (int i = 0; i <= 4; i++)				//down按钮
	{			
		setlinecolor(GREEN);
		rectangle(310, i * 100 + 56, 340, i * 100 + 86);
		settextcolor(GREEN);
		outtextxy(310 , i * 100 + 56 + 7, _T("down"));
	}

	int y1 = 520;//上
	int y2 = 550;//下
	for (int i = 1; i <= 6; i++)			//电梯箱内按钮
	{
		TCHAR title[5] ;
		_stprintf_s(title, _T("%d"), i);
		setlinecolor(LIGHTBLUE);
		rectangle(35, y1, 65, y2);
		y1 = y1 - 40;
		y2 = y1 + 30;
		settextcolor(LIGHTBLUE);
		outtextxy(35 + 12, y2 +17,title);
	}
	setlinecolor(WHITE);
	settextcolor(WHITE);

	int x = 10;
	int y = 10;
	outtextxy(x, y, _T("项目:"));
	outtextxy(x, y + 20, _T("电梯模拟"));
	outtextxy(x, y + 40, _T("作者："));
	outtextxy(x, y + 60, _T("伊克买提"));
	outtextxy(x, y + 80, _T("运行时间:"));
	outtextxy(x+10, 280, _T("电梯按钮"));
}

/*
* 名称：drawTime
* 描述：画出系统运行时间
* 参数：
* 返回：
* 注意：
*/
void drawTime( int time3)
{
	TCHAR time[5];
	clearrectangle(10, 140, 90, 180);
	_stprintf_s(time, _T("%d"), time3);
	settextstyle(48, 0, 0);
	outtextxy(25, 150, time);
	settextstyle(16,0,0);
}

/*
* 名称：drawclint
* 描述：画排队的人
* 参数：x-队列中的第几个人人
* 返回：
* 注意：
*/
void drawClint(int x, int infloor,int outfloor)
{
	TCHAR num[5];
	x = (x - 1) * 32 + 370;
	_stprintf_s(num, _T("%d"), outfloor);
	int y;
	if (outfloor <= infloor) {
		y = 605-25-(infloor - 1)*102;	//down
		setlinecolor(GREEN);
		circle(x, y, 15);
	}
	else if (outfloor > infloor) {
		y = 603 -  75-(infloor-1)*102;	//up
		setlinecolor(YELLOW);
		circle(x, y, 15);
	}
	settextcolor(WHITE);
	outtextxy(x-4, y-7, num);
}
/*
* 名称：drawPeopleInLift
* 描述：画在电梯的人
* 参数：x-电梯中位置，可以有_peopleinlift算出
* 返回：
* 注意：
*/
void drawPeopleInLift(int cout, int y, int outfloor) {
	TCHAR num[5];
	_stprintf_s(num, _T("%d"), outfloor);
	if (cout <= 5) {
		int x = 125 + (cout - 1) * 33;

		setlinecolor(WHITE);
		circle(x, y, 15);
		settextcolor(WHITE);
		outtextxy(x - 4, y - 7, num);
	}
	else if (cout > 5) {
		y = y + 43;
		cout = cout - 5;
		int x = 125 + (cout - 1) * 33;
		
		setlinecolor(WHITE);
		circle(x, y, 15);
		settextcolor(WHITE);
		outtextxy(x - 4, y - 7, num);
	}
}

/*
* 名称：drawLift
* 描述：画一电梯
* 参数：1:505	2:
* 返回：
* 注意：
*/
void drawLift(int y) {
	y = 505-(y-1)*100;
	setlinecolor(YELLOW);
	rectangle(105, y, 295, y+90);
	clearrectangle(295, y, 295, y + 90);//清掉电梯内门里矩形的半条短边 
}

/*
* 名称：openDoor
* 描述：开门
* 参数：
* 返回：
* 注意：
*/
void openDoor(int floor,
	int& time2, int& time3,	//系统已经运行时间秒,毫秒
	int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
	Lift& lift,int&giveupfrom, int&giveupto, int&infrom, int&into)
{
	int y1 = 46 + (6 - floor) * 100;
	int y2 = 49 + (6 - floor) * 100;
	for (int i = 0; i <= 45; i++)
	{
		clearrectangle(300, y1-i-1, 304, y1 - i);
		clearrectangle(300, y2 + i,  304, y2 + i + 1);
		sleep(50, time2, time3, intime, time0, lift,
			giveupfrom, giveupfrom, infrom, into);
	}
}
/*
* 名称：closeDoor
* 描述：关门
* 参数：
* 返回：
* 注意：
*/
void closeDoor(int floor,
	int& time2, int& time3,	//系统已经运行时间秒,毫秒
	int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
	Lift& lift, int&giveupfrom, int&giveupto, int&infrom, int&into)
{
	int y1 = 1 + (6 - floor) * 100;
	int y2 = 104 + (6 - floor) * 100;
	setcolor(WHITE);
	for (int i = 0; i <= 45; i++)
	{
		fillrectangle(300, y1 + i , 304, y1+i+1);
		fillrectangle(300, y2 - i, 304, y2-i-1 );
		sleep(50, time2, time3, intime, time0, lift,
			giveupfrom, giveupfrom, infrom, into);
	}
}


/*
* 名称：moveLift_pix
* 描述：移动电梯 1像素
* 参数：mode-移动模式，y可以由floor算出来
* 返回：
* 注意：
*/
void moveLift_Pix(int mode,int &y) {
	if (mode==1) {
		clearrectangle(105, y, 295, y + 90);
		draw(y - 1);
		y--;
	}
	if (mode == 2||mode==0) {
		clearrectangle(105, y, 295, y + 90);
		draw(y + 1);
		y++;
	}
}
void draw(int y) {
	setlinecolor(YELLOW);
	rectangle(105, y, 295, y + 90);
	clearrectangle(295, y, 295, y + 90);//清掉电梯内门里矩形的半条短边 
}

/*
* 名称：
* 描述：
* 参数：
* 返回：
* 注意：
*/
void movePeopleInLift_Pix(Lift&lift, int mode, int&y1,int&y2) {
	if (mode == 1) {
		clearrectangle(106, y1 + 5, 290, y1 + 85);
		lift._drawPeopleInLift(y2-1);
		y2--;
	}
	if (mode == 2||mode==0) {
		clearrectangle(106, y1 + 5, 290, y1 + 85);
		lift._drawPeopleInLift(y2 + 1);
		y2++;
	}
}

/*
* 名称：moveLift
* 描述：移动电梯
* 参数：mode-移动模式，y可以由floor算出来
* 返回：
* 注意：
*/
void moveLift(Lift&lift,int mode, int floor,
	int& time2, int& time3,	//系统已经运行时间秒,毫秒
	int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
	int&giveupfrom, int&giveupto, int&infrom, int&into)
{
	int y1=505 - (floor - 1) * 100;			//电梯边界的位置，由floor确定
	int y2 = 505 - (floor - 1) * 100 + 20;	//乘客的位置Y值
	for (int i = 0; i < 100; i++) {
		moveLift_Pix(mode, y1);
		movePeopleInLift_Pix(lift, mode, y1, y2);
		sleep(10, time2, time3, intime, time0,
			lift, giveupfrom, giveupto, infrom, into);
		//if i==99
	}

	setlinecolor(WHITE);
	for (int i = 100; i <= 600; i += 100)
		line(300, i, 100, i);		//楼层分割
}

/*
* 名称：freshQueue
* 描述：进出有人进出队伍后，刷新排队动画
* 参数：
* 返回：
* 注意：
*/
void freshQueue(Lift&lift)
{
	clearrectangle(341, 1, 685, 600);

	for (int i = 0; i <= 600; i += 100)
	{
		line(310, i, 690, i);
		setlinecolor(WHITE);
	}
	lift._drawPeopleInQueue();
}

/*
* 名称：
* 描述：
* 参数：
* 返回：
* 注意：
*/
void pressUp(int floor)
{
	setfillcolor(YELLOW);
	int i = 6 - floor;
	fillrectangle(310, i * 100 + 10, 340, i * 100 + 40);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(310 + 8, i * 100 + 17, _T("up"));
	setfillcolor(WHITE);
	setbkmode(OPAQUE);
	settextcolor(WHITE);
}

/*
* 名称：clearUp
* 描述：清空up
* 参数：
* 返回：
* 注意：
*/
void clearUp(int floor)
{
	int i = 6 - floor;
	clearrectangle(310, i * 100 + 10, 340, i * 100 + 40);
	setlinecolor(YELLOW);
	rectangle(310, i * 100 + 10, 340, i * 100 + 40);
	settextcolor(YELLOW);
	outtextxy(310 + 8, i * 100 + 17, _T("up"));
}

/*
* 名称：pressDown
* 描述：按下down
* 参数：
* 返回：
* 注意：
*/
void pressDown(int floor)
{
	setfillcolor(GREEN);
	int i = 6 - floor;
	fillrectangle(310, i * 100 + 56, 340, i * 100 + 86);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(310, i * 100 + 56+7, _T("down"));
	setfillcolor(WHITE);
	setbkmode(OPAQUE);
	settextcolor(WHITE);
}

/*
* 名称：
* 描述：
* 参数：
* 返回：
* 注意：
*/
void clearDown(int floor)
{
	int i = 6 - floor;
	clearrectangle(310, i * 100 + 56, 340, i * 100 + 86);
	setlinecolor(GREEN);
	rectangle(310, i * 100 + 56, 340, i * 100 + 86);
	settextcolor(YELLOW);
	outtextxy(310, i * 100 + 56 + 7, _T("down"));
}

/*
* 名称：pressCar
* 描述：按下车厢内按钮
* 参数：
* 返回：
* 注意：
*/
void pressCar(int floor)
{
	TCHAR num[5];
	setfillcolor(LIGHTBLUE);
	_stprintf_s(num, _T("%d"), floor);
	int y1 = 520 - (floor - 1) * 40;
	int y2 = y1 + 30;
	fillrectangle(35, y1, 65, y2);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(35 + 12, y1+8 , num);
	setfillcolor(WHITE);
	settextcolor(WHITE);
	setbkmode(OPAQUE);
}

/*
* 名称：clearCar
* 描述：清空car按钮
* 参数：
* 返回：
* 注意：
*/
void clearCar(int floor)
{
	TCHAR num[5];
	_stprintf_s(num, _T("%d"), floor);
	int y1 = 520 - (floor - 1) * 40;
	int y2 = y1 + 30;
	clearrectangle(35, y1, 65, y2);
	setlinecolor(LIGHTBLUE);
	rectangle(35, y1, 65, y2);
	settextcolor(LIGHTBLUE);
	outtextxy(35 + 12, y1 + 8, num);
}