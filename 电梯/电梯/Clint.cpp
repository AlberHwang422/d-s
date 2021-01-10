#include<iostream>
#include"Lift.h"
#include"Clint.h"
#include<time.h>
using namespace std;

#define LiftFloor (lift.getFloor())
#define Down ((_InFloor > _OutFloor)?1:0)
#define Up  ((_InFloor < _OutFloor)?1:0)

/*
* 名称：Clint
* 描述：生成一个乘客
* 参数：
* 返回：
* 注意：
*/
Clint::Clint(int InFloor, int OutFloor, int GiveUp,int intime )
{
	_InFloor = InFloor;
	_OutFloor = OutFloor;
	_GiveUpTime = GiveUp;
	_inTime = intime;
}

/*
* 名称：canNotBear
* 描述：判断是否无法忍受放弃
* 参数：
* 返回：
* 注意：
*/
bool Clint::canNotBear() {
	int t = clock();
	if (t - _inTime >= _GiveUpTime)	
		return true;
	else
		return false;
}
/*
* 名称：_M2
* 描述：按电梯键
* 参数：
* 返回：
* 注意：
*/
void Clint::_M2(Lift& lift) {
	if (Down)
		lift.setDownButton(_InFloor);
	else if (Up)
		lift.setUpButton(_InFloor);
}

/*
* 名称：_M3
* 描述：使乘客进入排队队列
* 参数：
* 返回：
* 注意：
*/
void Clint::_M3(Lift& lift) {
	if (Down)
		lift._WaitingDown[_InFloor].push(*this);
	if (Up)
		lift._WaitingUp[_InFloor].push(*this);
}

/*	not finish
* 名称：_M4
* 描述：执行动作M4，判断是否放弃
* 参数：
* 返回：
* 注意：
*/
void Clint::_M4(Lift& lift) {
	if (_InFloor == LiftFloor && lift.getD1()) {

	}
	else {
		/*在队列中删除该人*/
		/*
			需要重写一个单链表
			实现乘客放弃操作
		*/
	}
}

/*
* 名称：
* 描述：进入电梯。从排队队列中弹出，插入到电梯栈中，按电梯按钮
* 参数：
* 返回：
* 注意：
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
	int y2 = 505 - (lift.getFloor() - 1) * 100 + 20;	//乘客的位置Y值
	lift._drawPeopleInLift(y2);
	lift.setCarButton(_OutFloor);
}

/*
* 名称：_M6
* 描述：离开电梯（从电梯栈弹出和系统中删除该人）
* 参数：
* 返回：
* 注意：
*/
void Clint::_M6(Lift& lift) {

	lift._LiftStack[_OutFloor].pop();
	/*=======释放掉这个人=======*/
	/*动画peopleinlift*/
	int y2 = 505 - (lift.getFloor()- 1) * 100 + 20;	//乘客的位置Y值
	lift._drawPeopleInLift(y2);
}

