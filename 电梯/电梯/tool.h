#pragma once
#include"Lift.h"

/*
* ���ƣ�Sleep
* �������ӳ� time ���룬����ʱ�̼���
		�Ƿ��ѵ�����һ���˵�ʱ�䣬���ǣ����½��� 
* �������ӳٵ�ʱ�䣨���룩
* ���أ�
* ע�⣺
*/
void sleep(int time,	//�ӳ�����
	       int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
	       int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
		   Lift& lift, int&giveupfrom, int&giveupto, int&infrom, int&into);

/*
* ���ƣ�sleepwithoutgiveup
* ���������ӳٲ����з�������
* ������
* ���أ�
* ע�⣺
*/
void sleepWithOutGiveUp(int time,	//�ӳ�����
	int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
	int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
	Lift& lift, int&giveupfrom, int&giveupto, int&infrom, int&into);

/*
* ���ƣ�getRandnum
* ����������ĳ����Χ�ڵ������
* ������
* ���أ�
* ע�⣺
*/
int getRandnum(int from, int to);

/*
* ���ƣ�intiClint
* ����������һ���˿ͣ����øó˿ͼ����ŶӶ���
* ������
* ���أ���һ��˿����ɵ�ʱ����
* ע�⣺
*/
int initClint(Lift& lift, int&giveupfrom, int&giveupto, int&infrom, int&into);

/*
* ���ƣ�
* ������
* ������
* ���أ�
* ע�⣺
*/
void isInitClint(int& intime,int&time0,
			     Lift& lift, int&giveupfrom, int&giveupto, int&infrom, int&into);

/*
* ���ƣ�RefreshTime����
* ������ˢ��ʱ�䣨��ʾ���棩
* ������
* ���أ�time3����ʾϵͳ����ʱ��
* ע�⣺
*/
int RefreshTime(int& time2);	//ˢ��ʱ�� ��ʾ

/*
* ���ƣ�isRefreshTime
* �������ж��Ƿ�Ӧˢ����ʾʱ��
* ������time2-����ʱ���룬
* ���أ�
* ע�⣺
*/
void isRefreshTime(int &time2,int&time3);

/*
* ���ƣ�drawTime
* ����������ϵͳ����ʱ��
* ������
* ���أ�
* ע�⣺
*/
void drawTime( int time3);

/*
* ���ƣ�isGiveUp
* �������ж��Ƿ����˷����������
* ������
* ���أ�
* ע�⣺
*/
void isGivenUp(Lift& lift);

/*
* ���ƣ�isGiveUp
* �������ж��Ƿ����˷����������
* ������
* ���أ�
* ע�⣺
*/
void isGivenUp(Lift& lift, int thisfloor);

/*
* ���ƣ�background
* ��������ʼ����������
* ������
* ���أ�
* ע�⣺
*/
void background();

/*
* ���ƣ�drawClint
* ��������һ����
* ������
* ���أ�
* ע�⣺
*/
void drawClint(int x, int infloor,int outfloor);

/*
* ���ƣ�drawPeopleInLift
* ���������ڵ��ݵ���
* ������x-�����еڼ����ˣ�������_peopleinlift���
* ���أ�
* ע�⣺
*/
void drawPeopleInLift(int x, int thisfloor, int outfloor);

/*
* ���ƣ�drawLift
* ��������һ����
* ������y-¥��
* ���أ�
* ע�⣺
*/
void drawLift(int y);

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
		      Lift& lift,int&giveupfrom, int&giveupto, int&infrom, int&into);

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
	           Lift& lift,int&giveupfrom, int&giveupto, int&infrom, int&into);

/*
* ���ƣ�moveLift
* �������ƶ�����
* ������mode-�ƶ�ģʽ��y������floor�����
* ���أ�
* ע�⣺
*/
void moveLift_Pix(int mode,int& y);
void draw(int y);

/*
* ���ƣ�
* ������y1-�������ꡣy2-������
* ������
* ���أ�
* ע�⣺
*/
void movePeopleInLift_Pix(Lift&lift, int mode, int&y1,int& y2);
/*
* ���ƣ�moveLift
* �������ƶ�����
* ������mode-�ƶ�ģʽ��y������floor�����
* ���أ�
* ע�⣺
*/
void moveLift(Lift&lift,int mode,int floor,
	int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
	int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
	int&giveupfrom, int&giveupto, int&infrom, int&into);


/*
* ���ƣ�freshQueue
* �������������˽��������ˢ���ŶӶ���
* ������
* ���أ�
* ע�⣺
*/
void freshQueue(Lift&lift);

/*
* ���ƣ�pressUp
* ����������Up��ť
* ������
* ���أ�
* ע�⣺
*/
void pressUp(int floor);

/*
* ���ƣ�
* ������
* ������
* ���أ�
* ע�⣺
*/
void pressDown(int floor);

/*
* ���ƣ�pressCar
* ���������³����ڰ�ť
* ������
* ���أ�
* ע�⣺
*/
void pressCar(int floor);

/*
* ���ƣ�clearUp
* ���������up
* ������
* ���أ�
* ע�⣺
*/
void clearUp(int floor);

/*
* ���ƣ�clearDown
* ���������down
* ������
* ���أ�
* ע�⣺
*/
void clearDown(int floor);

/*
* ���ƣ�clearCar
* ���������car��ť
* ������
* ���أ�
* ע�⣺
*/
void clearCar(int floor);
//int y1 = 520;//��
//int y2 = 550;//��
//for (int i = 1; i <= 6; i++)			//�������ڰ�ť
//{
//	TCHAR title[5];
//	_stprintf_s(title, _T("%d"), i);
//	setlinecolor(LIGHTBLUE);
//	rectangle(35, y1, 65, y2);
//	y1 = y1 - 40;
//	y2 = y1 + 30;
//	settextcolor(LIGHTBLUE);
//	outtextxy(35 + 12, y2 + 17, title);
//}
//setlinecolor(WHITE);
//settextcolor(WHITE);