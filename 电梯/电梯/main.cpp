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
	int time0,		//��һ���˴�����ʱ��
		time1,		//��ʼ���㷵��һ¥ͣ���ʱ���
		time2,		//��¼����ʼ������ǰ����ʱ�䣨���룩
		time3,		//��¼����ʼ������ǰ����ʱ�䣨�룩
		giveupfrom,	//��¼����ʱ����½�
		giveupto,	//��¼����ʱ����Ͻ�
		infrom,		//��¼�½�ʱ����½�
		into,		//��¼�½�ʱ����Ͻ�
		intime,		//��¼������һ���˵�ʱ����
		endtime,	//ϵͳ������ʱ��
		NumOfClint;	//�˿�����

	
	InitLiftSys(NumOfClint, giveupfrom, 
				giveupto, infrom, into,time2,time3,endtime);
					//ϵͳ�ĳ�ʼ������

	time1 = -1;

	Lift lift = Lift(LiftSize);
	
	for (int i = 0; i < NumOfClint; i++)	//�����ܶ�˿Ͳ������ŶӶ���
		intime = initClint(lift, giveupfrom, giveupto, infrom, into);
	lift._drawPeopleInQueue();

	time0 = clock();						//��ǰ�˿����ɵĽ���ʱ��

	while (time3 <= endtime) {
		while (lift.ifOpenDoor())			//�ж��Ƿ��ţ����˽�������
		{
			lift._E3(time2, time3, intime, time0,
				giveupfrom, giveupto, infrom, into);			//����
			sleepWithOutGiveUp(20*period,						//�������ѿ��ò㲻�����˷����Ŷ�
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
			giveupfrom,giveupto,infrom,into);					//E6������control �ж���һ������
		sleep(1, time2, time3, intime, time0,
			lift, giveupfrom, giveupto, infrom, into);

		if (oldmode!=lift.getmode())		//ת����
			continue;
		if (lift.getmode() == 0)				//���ͣ��״̬
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