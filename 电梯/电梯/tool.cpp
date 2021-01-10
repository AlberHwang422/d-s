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
* ���ƣ�Sleep
* �������ӳ� time ���룬����ʱ�̼���
		�Ƿ��ѵ�����һ���˵�ʱ�䣬���ǣ����½���
* �������ӳٵ�ʱ�䣨���룩
* ���أ�
* ע�⣺
*/
void sleep(int time,		//�ӳ�����
	int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
	int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
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
* ���ƣ�sleepwithoutgiveup
* ��������¥�㲻�����˽���M6����
		����¥����δ��
* ������
* ���أ�
* ע�⣺
*/
void sleepWithOutGiveUp(int time,	//�ӳ�����
	int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
	int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
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
* ���ƣ�getRandnum
* ����������ĳ����Χ�ڵ������
* ������
* ���أ�
* ע�⣺
*/
int getRandnum(int from, int to) {
	return (rand() % (to - from + 1)) + from;
}

/*
* ���ƣ�intiClint
* ����������һ���˿ͣ����øó˿ͼ����ŶӶ���
* ������
* ���أ���һ��˿����ɵ�ʱ����
* ע�⣺
*/
int initClint(Lift& lift, int&giveupfrom, int&giveupto, int&infrom, int&into) {
	int infloor = getRandnum(1, 6);
	int outfloor;
	do{
		outfloor = getRandnum(1, 6);
	} while (infloor == outfloor);

	int giveuptime = getRandnum(giveupfrom, giveupto);
	Clint* clint1=new Clint(infloor, outfloor, giveuptime, clock());
	(*clint1)._M2(lift);	//����ť
	(*clint1)._M3(lift);	//�˿�ִ��M3�ŶӲ���

	return getRandnum(infrom, into);
}

/*
* ���ƣ�isInitClint
* �������ж��Ƿ��˸��½�һ���˵�ʱ��
		�����򴴽�
* ������intime-��һ���˳��ֵļ����time0-��һ�������ɵ����
		������ΪInitClint�Ĳ���
* ���أ�
* ע�⣺
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
* ���ƣ�RefreshTime����
* ������ˢ��ʱ�䣨��ʾ���棩
* ������
* ���أ�time3����ʾϵͳ����ʱ��
* ע�⣺
*/
int RefreshTime(int& time2) {
	int time3 = (clock() - time2) / 1000;
	drawTime(time3);
	return time3;
}

/*
* ���ƣ�isRefreshTime
* �������ж��Ƿ�Ӧˢ����ʾʱ��
* ������time2-����ʱ���룬
* ���أ�
* ע�⣺
*/
void isRefreshTime(int&time2,int& time3) {
	if (clock() - time2 != time3)
		time3 = RefreshTime(time2);
}

/*
* ���ƣ�isGiveUp
* �������ж��Ƿ����˷����������
* ������
* ���أ�
* ע�⣺
*/
void isGivenUp(Lift& lift) {
	for (int i = 1; i <= LiftSize; i++) {
		lift._WaitingUp[i].moveGiveUpClint();
		lift._WaitingDown[i].moveGiveUpClint();
	}
}

/*
* ���ƣ�isGiveUp
* �������ж��Ƿ����˷����������
		���ǲ��ж�thisfloor
* ������
* ���أ�
* ע�⣺
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
* ���ƣ�background
* ��������ʼ����������
* ������
* ���أ�
* ע�⣺
*/
void background() {
	initgraph(750, 602);

	line(100, 0, 100, 650);						//��
	line(300, 0, 300, 650);						//��

	for (int i = 100; i <= 600; i += 100)
	{
		line(300, i, 100, i);		//¥��ָ�
		line(310, i, 690, i);
	}
	for (int i = 49; i <= 550; i += 100)
		fillrectangle(300, i, 304, i + 45);		//������
	for(int i=1;i<=550;i+=100)
		fillrectangle(300, i, 304, i + 45);


	for (int i = 1; i <= 5; i++)				//up��ť
	{
		setlinecolor(YELLOW);
		rectangle(310, i * 100 + 10, 340, i * 100 + 40);
		settextcolor(YELLOW);
		outtextxy(310 + 8, i * 100 + 17, _T("up"));
	}
	for (int i = 0; i <= 4; i++)				//down��ť
	{			
		setlinecolor(GREEN);
		rectangle(310, i * 100 + 56, 340, i * 100 + 86);
		settextcolor(GREEN);
		outtextxy(310 , i * 100 + 56 + 7, _T("down"));
	}

	int y1 = 520;//��
	int y2 = 550;//��
	for (int i = 1; i <= 6; i++)			//�������ڰ�ť
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
	outtextxy(x, y, _T("��Ŀ:"));
	outtextxy(x, y + 20, _T("����ģ��"));
	outtextxy(x, y + 40, _T("���ߣ�"));
	outtextxy(x, y + 60, _T("��������"));
	outtextxy(x, y + 80, _T("����ʱ��:"));
	outtextxy(x+10, 280, _T("���ݰ�ť"));
}

/*
* ���ƣ�drawTime
* ����������ϵͳ����ʱ��
* ������
* ���أ�
* ע�⣺
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
* ���ƣ�drawclint
* ���������Ŷӵ���
* ������x-�����еĵڼ�������
* ���أ�
* ע�⣺
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
* ���ƣ�drawPeopleInLift
* ���������ڵ��ݵ���
* ������x-������λ�ã�������_peopleinlift���
* ���أ�
* ע�⣺
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
* ���ƣ�drawLift
* ��������һ����
* ������1:505	2:
* ���أ�
* ע�⣺
*/
void drawLift(int y) {
	y = 505-(y-1)*100;
	setlinecolor(YELLOW);
	rectangle(105, y, 295, y+90);
	clearrectangle(295, y, 295, y + 90);//���������������εİ����̱� 
}

/*
* ���ƣ�openDoor
* ����������
* ������
* ���أ�
* ע�⣺
*/
void openDoor(int floor,
	int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
	int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
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
* ���ƣ�closeDoor
* ����������
* ������
* ���أ�
* ע�⣺
*/
void closeDoor(int floor,
	int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
	int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
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
* ���ƣ�moveLift_pix
* �������ƶ����� 1����
* ������mode-�ƶ�ģʽ��y������floor�����
* ���أ�
* ע�⣺
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
	clearrectangle(295, y, 295, y + 90);//���������������εİ����̱� 
}

/*
* ���ƣ�
* ������
* ������
* ���أ�
* ע�⣺
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
* ���ƣ�moveLift
* �������ƶ�����
* ������mode-�ƶ�ģʽ��y������floor�����
* ���أ�
* ע�⣺
*/
void moveLift(Lift&lift,int mode, int floor,
	int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
	int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
	int&giveupfrom, int&giveupto, int&infrom, int&into)
{
	int y1=505 - (floor - 1) * 100;			//���ݱ߽��λ�ã���floorȷ��
	int y2 = 505 - (floor - 1) * 100 + 20;	//�˿͵�λ��Yֵ
	for (int i = 0; i < 100; i++) {
		moveLift_Pix(mode, y1);
		movePeopleInLift_Pix(lift, mode, y1, y2);
		sleep(10, time2, time3, intime, time0,
			lift, giveupfrom, giveupto, infrom, into);
		//if i==99
	}

	setlinecolor(WHITE);
	for (int i = 100; i <= 600; i += 100)
		line(300, i, 100, i);		//¥��ָ�
}

/*
* ���ƣ�freshQueue
* �������������˽��������ˢ���ŶӶ���
* ������
* ���أ�
* ע�⣺
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
* ���ƣ�
* ������
* ������
* ���أ�
* ע�⣺
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
* ���ƣ�clearUp
* ���������up
* ������
* ���أ�
* ע�⣺
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
* ���ƣ�pressDown
* ����������down
* ������
* ���أ�
* ע�⣺
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
* ���ƣ�
* ������
* ������
* ���أ�
* ע�⣺
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
* ���ƣ�pressCar
* ���������³����ڰ�ť
* ������
* ���أ�
* ע�⣺
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
* ���ƣ�clearCar
* ���������car��ť
* ������
* ���أ�
* ע�⣺
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