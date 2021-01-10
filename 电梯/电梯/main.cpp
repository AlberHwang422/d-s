#include<iostream>
#include<Windows.h>
#include<stdio.h>
#include"Clint.h"
#include"Lift.h"
#include"system.h"
#include"tool.h"
#include<time.h>
using namespace std;
	

int main() {
	system("pause");
	int time0,		//上一个人创建的时间
		time1,		//开始计算返回一楼停侯的时间点
		time2,		//记录程序开始，到当前所用时间（毫秒）
		time3,		//记录程序开始，到当前所用时间（秒）
		giveupfrom,	//记录放弃时间的下界
		giveupto,	//记录放弃时间的上界
		infrom,		//记录新建时间的下界
		into,		//记录新建时间的上界
		intime,		//记录生成下一个人的时间跨度
		endtime,	//系统运行总时间
		NumOfClint;	//乘客数量

	
	InitLiftSys(NumOfClint, giveupfrom, 
				giveupto, infrom, into,time2,time3,endtime);
					//系统的初始化设置

	time1 = -1;

	Lift lift = Lift(LiftSize);
	
	for (int i = 0; i < NumOfClint; i++)	//创建很多乘客并加入排队队列
		intime = initClint(lift, giveupfrom, giveupto, infrom, into);
	lift._drawPeopleInQueue();

	time0 = clock();						//当前乘客生成的结束时间

	while (time3 <= endtime) {
		while (lift.ifOpenDoor())			//判断是否开门，让人进出电梯
		{
			lift._E3(time2, time3, intime, time0,
				giveupfrom, giveupto, infrom, into);			//开门
			sleepWithOutGiveUp(20*period,						//电梯人已开该层不会有人放弃排队
							   time2, time3, 
							   intime, time0, 
				               lift, giveupfrom, giveupto, infrom, into);
			lift._E4(time2,time3,intime,time0,
				giveupfrom,giveupto,infrom,into);
			freshQueue(lift);

			lift._E5(time2, time3, intime,time0,
				giveupfrom, giveupto, infrom, into);

			sleep(20 * period,
				time2, time3,
				intime, time0,
				lift, giveupfrom, giveupto, infrom, into);
			if (lift.isFull())
				break;
		}
		int oldmode = lift.getmode();
		lift._E6(time1,time2,time3,intime,time0,
			giveupfrom,giveupto,infrom,into);					//E6，调用control 判断下一个方向
		sleep(1, time2, time3, intime, time0,
			lift, giveupfrom, giveupto, infrom, into);

		if (oldmode!=lift.getmode())		//转向了
			continue;
		if (lift.getmode() == 0)				//变成停留状态
		{
			sleep(100, time2, time3, intime, time0,
				lift, giveupfrom, giveupto, infrom, into);
			lift._E1(time2, time3, intime, time0, giveupfrom, giveupto, infrom, into);

		}
		else
			lift._Move(time2, time3, intime, time0,
				giveupfrom, giveupto, infrom, into);
		freshQueue(lift);
		sleep(1, time2, time3, intime, time0,
			lift, giveupfrom, giveupto, infrom, into);
	}
	
	cin.get();
	cin.get();
	system("pause");
	return 0;
}