#pragma once
#include"Lift.h"

/*
* 名称：Sleep
* 描述：延迟 time 毫秒，并且时刻监视
		是否已到创建一个人的时间，若是，则新建人 
* 参数：延迟的时间（毫秒）
* 返回：
* 注意：
*/
void sleep(int time,	//延迟秒数
	       int& time2, int& time3,	//系统已经运行时间秒,毫秒
	       int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
		   Lift& lift, int&giveupfrom, int&giveupto, int&infrom, int&into);

/*
* 名称：sleepwithoutgiveup
* 描述：该延迟不进行放弃操作
* 参数：
* 返回：
* 注意：
*/
void sleepWithOutGiveUp(int time,	//延迟秒数
	int& time2, int& time3,	//系统已经运行时间秒,毫秒
	int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
	Lift& lift, int&giveupfrom, int&giveupto, int&infrom, int&into);

/*
* 名称：getRandnum
* 描述：返回某个范围内得随机数
* 参数：
* 返回：
* 注意：
*/
int getRandnum(int from, int to);

/*
* 名称：intiClint
* 描述：生成一个乘客，并让该乘客加入排队队列
* 参数：
* 返回：下一额乘客生成的时间间隔
* 注意：
*/
int initClint(Lift& lift, int&giveupfrom, int&giveupto, int&infrom, int&into);

/*
* 名称：
* 描述：
* 参数：
* 返回：
* 注意：
*/
void isInitClint(int& intime,int&time0,
			     Lift& lift, int&giveupfrom, int&giveupto, int&infrom, int&into);

/*
* 名称：RefreshTime（）
* 描述：刷新时间（演示界面）
* 参数：
* 返回：time3，表示系统运行时间
* 注意：
*/
int RefreshTime(int& time2);	//刷新时间 显示

/*
* 名称：isRefreshTime
* 描述：判断是否应刷新显示时间
* 参数：time2-运行时间秒，
* 返回：
* 注意：
*/
void isRefreshTime(int &time2,int&time3);

/*
* 名称：drawTime
* 描述：画出系统运行时间
* 参数：
* 返回：
* 注意：
*/
void drawTime( int time3);

/*
* 名称：isGiveUp
* 描述：判断是否有人放弃，并离队
* 参数：
* 返回：
* 注意：
*/
void isGivenUp(Lift& lift);

/*
* 名称：isGiveUp
* 描述：判断是否有人放弃，并离队
* 参数：
* 返回：
* 注意：
*/
void isGivenUp(Lift& lift, int thisfloor);

/*
* 名称：background
* 描述：初始化背景画布
* 参数：
* 返回：
* 注意：
*/
void background();

/*
* 名称：drawClint
* 描述：画一个人
* 参数：
* 返回：
* 注意：
*/
void drawClint(int x, int infloor,int outfloor);

/*
* 名称：drawPeopleInLift
* 描述：画在电梯的人
* 参数：x-电梯中第几个人，可以有_peopleinlift算出
* 返回：
* 注意：
*/
void drawPeopleInLift(int x, int thisfloor, int outfloor);

/*
* 名称：drawLift
* 描述：画一电梯
* 参数：y-楼层
* 返回：
* 注意：
*/
void drawLift(int y);

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
		      Lift& lift,int&giveupfrom, int&giveupto, int&infrom, int&into);

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
	           Lift& lift,int&giveupfrom, int&giveupto, int&infrom, int&into);

/*
* 名称：moveLift
* 描述：移动电梯
* 参数：mode-移动模式，y可以由floor算出来
* 返回：
* 注意：
*/
void moveLift_Pix(int mode,int& y);
void draw(int y);

/*
* 名称：
* 描述：y1-电梯坐标。y2-人坐标
* 参数：
* 返回：
* 注意：
*/
void movePeopleInLift_Pix(Lift&lift, int mode, int&y1,int& y2);
/*
* 名称：moveLift
* 描述：移动电梯
* 参数：mode-移动模式，y可以由floor算出来
* 返回：
* 注意：
*/
void moveLift(Lift&lift,int mode,int floor,
	int& time2, int& time3,	//系统已经运行时间秒,毫秒
	int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
	int&giveupfrom, int&giveupto, int&infrom, int&into);


/*
* 名称：freshQueue
* 描述：进出有人进出队伍后，刷新排队动画
* 参数：
* 返回：
* 注意：
*/
void freshQueue(Lift&lift);

/*
* 名称：pressUp
* 描述：按下Up按钮
* 参数：
* 返回：
* 注意：
*/
void pressUp(int floor);

/*
* 名称：
* 描述：
* 参数：
* 返回：
* 注意：
*/
void pressDown(int floor);

/*
* 名称：pressCar
* 描述：按下车厢内按钮
* 参数：
* 返回：
* 注意：
*/
void pressCar(int floor);

/*
* 名称：clearUp
* 描述：清空up
* 参数：
* 返回：
* 注意：
*/
void clearUp(int floor);

/*
* 名称：clearDown
* 描述：清空down
* 参数：
* 返回：
* 注意：
*/
void clearDown(int floor);

/*
* 名称：clearCar
* 描述：清空car按钮
* 参数：
* 返回：
* 注意：
*/
void clearCar(int floor);
//int y1 = 520;//上
//int y2 = 550;//下
//for (int i = 1; i <= 6; i++)			//电梯箱内按钮
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