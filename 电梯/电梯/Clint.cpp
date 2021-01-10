#include<iostream>
#include"Lift.h"
#include"Clint.h"
#include<time.h>
using namespace std;

#define LiftFloor (lift.getFloor())
#define Down ((_InFloor > _OutFloor)?1:0)
#define Up  ((_InFloor < _OutFloor)?1:0)

/*
* ���ƣ�Clint
* ����������һ���˿�
* ������
* ���أ�
* ע�⣺
*/
Clint::Clint(int InFloor, int OutFloor, int GiveUp,int intime )
{
	_InFloor = InFloor;
	_OutFloor = OutFloor;
	_GiveUpTime = GiveUp;
	_inTime = intime;
}

/*
* ���ƣ�canNotBear
* �������ж��Ƿ��޷����ܷ���
* ������
* ���أ�
* ע�⣺
*/
bool Clint::canNotBear() {
	int t = clock();
	if (t - _inTime >= _GiveUpTime)	
		return true;
	else
		return false;
}
/*
* ���ƣ�_M2
* �����������ݼ�
* ������
* ���أ�
* ע�⣺
*/
void Clint::_M2(Lift& lift) {
	if (Down)
		lift.setDownButton(_InFloor);
	else if (Up)
		lift.setUpButton(_InFloor);
}

/*
* ���ƣ�_M3
* ������ʹ�˿ͽ����ŶӶ���
* ������
* ���أ�
* ע�⣺
*/
void Clint::_M3(Lift& lift) {
	if (Down)
		lift._WaitingDown[_InFloor].push(*this);
	if (Up)
		lift._WaitingUp[_InFloor].push(*this);
}

/*	not finish
* ���ƣ�_M4
* ������ִ�ж���M4���ж��Ƿ����
* ������
* ���أ�
* ע�⣺
*/
void Clint::_M4(Lift& lift) {
	if (_InFloor == LiftFloor && lift.getD1()) {

	}
	else {
		/*�ڶ�����ɾ������*/
		/*
			��Ҫ��дһ��������
			ʵ�ֳ˿ͷ�������
		*/
	}
}

/*
* ���ƣ�
* ������������ݡ����ŶӶ����е��������뵽����ջ�У������ݰ�ť
* ������
* ���أ�
* ע�⣺
*/
void Clint::_M5(Lift& lift) {
	if (Down) {
		lift._WaitingDown[_InFloor].pop();
		lift._LiftStack[_OutFloor].push(*this);
	}
	else if (Up) {
		lift._WaitingUp[_InFloor].pop();
		lift._LiftStack[_OutFloor].push(*this);
	}
	int y2 = 505 - (lift.getFloor() - 1) * 100 + 20;	//�˿͵�λ��Yֵ
	lift._drawPeopleInLift(y2);
	lift.setCarButton(_OutFloor);
}

/*
* ���ƣ�_M6
* �������뿪���ݣ��ӵ���ջ������ϵͳ��ɾ�����ˣ�
* ������
* ���أ�
* ע�⣺
*/
void Clint::_M6(Lift& lift) {

	lift._LiftStack[_OutFloor].pop();
	/*=======�ͷŵ������=======*/
	/*����peopleinlift*/
	int y2 = 505 - (lift.getFloor()- 1) * 100 + 20;	//�˿͵�λ��Yֵ
	lift._drawPeopleInLift(y2);
}

