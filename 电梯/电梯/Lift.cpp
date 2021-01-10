#define WIN32
#include"Lift.h"
#include"Clint.h"
#include<iostream>
#include<Windows.h>
#include<time.h>
#include"tool.h"

//#define clearCar(x)	_button.CallCar[x]=0
//#define pressCar(x) _button.CallCar[x]=1
//#define clearUp(x) _button.CallUp[x]=0
//#define pressUp(x) _button.CallUp[x]=1
//#define clearDown(x) _button.CallDown[x]=0
//#define pressDown(x) _button.CallDown[x]=1

using namespace std;

/*===========getter and setter=================*/
int Lift::getFloor() {
	return _floor;
}

int Lift::getPeoPleInLift() {
	return _PeopleInLift;
}

int Lift::getMaxSize() {
	return _MaxPeopleInlift;
}

bool Lift::getD1() {
	return _d1;
}

bool Lift::getD2() {
	return _d2;
}

bool Lift::getD3() {
	return _d3;
}

void Lift::setUpButton(int floor) {
	_button.CallUp[floor] = 1;
	pressUp(floor);
}

void Lift::setDownButton(int floor) {
	_button.CallDown[floor] = 1;
	pressDown(floor);
}

void Lift::setCarButton(int floor) {
	_button.CallCar[floor] = 1;
	pressCar(floor);
}

void Lift::cleanUp(int floor)
{
	_button.CallUp[floor] = 0;
	clearUp(floor);
}
void Lift::cleanDown(int floor)
{
	_button.CallDown[floor] = 0;
	clearDown(floor);
}
void Lift::cleanCar(int floor)
{
	_button.CallCar[floor] = 0;
	clearCar(floor);
}
/*
* 名称：Lift(int SizeOfLift=5)
* 描述：初始化电梯
* 参数：int
* 返回：无
* 注意：无
*/
Lift::Lift(int SizeOfFloor) {
	_LiftStack = new Stack[SizeOfFloor+1];		//设置电梯车箱数组,即电梯楼层层数
	_Waiting = new Queue[SizeOfFloor + 1];		//电梯门外排队队列
	_WaitingUp = new Queue[SizeOfFloor+1];		//设置乘客排队队列
	_WaitingDown = new Queue[SizeOfFloor+1];	//设置乘客排队队列

	_PeopleInLift = 0;								//当前电梯人数

	_floor = 1;										//设置初始电梯停留位置
	_d1 = _d2 = _d3 = true;						

	for (int i = 0; i < SizeOfFloor; i++)			//设置电梯按钮
		_button.CallCar[i] = _button.CallDown[i] = _button.CallUp[i] = 0;

	_nowAction = E1;								//电梯初始动作
	_nowStatus = Idle;								//电梯初始状态：停留
	_mode = 0;										//电梯初始状态：停留
}

/*
* 名称：Up()
* 描述：电梯上升
* 参数：int
* 返回：int
* 注意：无
*/
void Lift::Up(int& time2, int& time3,	//系统已经运行时间秒,毫秒
	int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
	int&giveupfrom, int&giveupto, int&infrom, int&into)
{
	int maxsize = LiftSize;
	moveLift(*this, _mode, _floor,time2,time3,intime,time0,
		giveupfrom,giveupto,infrom,into);
	if (_floor < maxsize)	_floor++;
}

/*
* 名称：Down()
* 描述：电梯下降
* 参数：int
* 返回：int
* 注意：无
*/
void Lift::Down(int& time2, int& time3,	//系统已经运行时间秒,毫秒
	int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
	int&giveupfrom, int&giveupto, int&infrom, int&into)
{
	moveLift(*this, _mode, _floor, time2, time3, intime, time0,
		giveupfrom, giveupto, infrom, into);
	if (_floor > 1)	_floor--;
}

/*
* 名称：_drawPeopleInLift
* 描述：画电梯中的人
* 参数：y-圆心的y值
* 返回：
* 注意：
*/
void Lift::_drawPeopleInLift(int y) {
	int count = 0;
	for (int i = 1; i <= 6; i++) {
		_LiftStack[i].drawPeopleInStack(count, y);
	}
}

/*
* 名称：drawPeopleInQueue
* 描述：
* 参数：
* 返回：
* 注意：
*/
void Lift::_drawPeopleInQueue() 
{
	for (int i = 1; i <= 6; i++) {
		_WaitingUp[i].drawQueue();
		_WaitingDown[i].drawQueue();
	}
}



/*==============电梯活动================*/
/*
* 名称：E1
* 描述：一层停侯
* 参数：
* 返回：
* 注意：
*/
void Lift::_E1(int& time2, int& time3,	//系统已经运行时间秒,毫秒
			   int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
	           int&giveupfrom, int&giveupto, int&infrom, int&into) 
{
	if (_floor != 1)
		_E8(time2, time3, intime, time0, giveupfrom, giveupto,
			infrom, into);
}

/*
* 名称：E2
* 描述：状态即将改变
* 参数：
* 返回：
* 注意：
*/
void Lift::_E2() {
	_nowAction = E2;
}

/*	not finish 还差开门动画  sleep
* 名称：E3
* 描述：在某层开门
* 参数：
* 返回：
* 注意：
*/
void Lift::_E3(int& time2, int& time3,	//系统已经运行时间秒,毫秒
			   int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
		       int&giveupfrom, int&giveupto, int&infrom, int&into)
{
	_d1 = _d2 = 1;
	_nowAction = E3;
	openDoor(_floor,time2,time3,intime,time0,
		*this,giveupfrom,giveupto,infrom,into);						//开门动画
}

/*  				status==Idle状态还没想好
* 名称：E4
* 描述：让人出入
* 参数：			sleep
* 返回：
* 注意：乘客是先出后进
*/
void Lift :: _E4(int& time2, int& time3,	//系统已经运行时间秒,毫秒
				int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
				int&giveupfrom, int&giveupto, int&infrom, int&into)
{

	_nowAction = E4;
	_d1 = 1;
	if (_mode == 1)							//电梯是由上升到来的，清空门外上升
		cleanUp(_floor);
	else if (_mode == 2)					//电梯是由下降到来的，清空门外下降
		cleanDown(_floor);
	
											//电梯车厢内，该楼层的栈如果不空
	while (!_LiftStack[_floor].empty())		//代表有人要出电梯
	{
		Clint clint1 = _LiftStack[_floor].top();
		Clint *clint = new Clint(clint1.getInfloor(), clint1.getOutfloor(),
				clint1.getGiveupTime(), clint1.getIntime());
		(*clint)._M6(*this);					//乘客离去
		clearCar(_floor);
		_button.CallCar[_floor] = 0;
		_PeopleInLift--;
		sleep(25*period,
			time2, time3,
			intime, time0,
			*this, giveupfrom, giveupto, infrom, into);
	} 

	int y = 505 - (_floor - 1) * 100 + 20;	//乘客的位置
	_drawPeopleInLift(y);

	if (_mode == 1)
	{
		while (!_WaitingUp[_floor].empty() && !isFull()) {
			Clint clint1 = _WaitingUp[_floor].back();

			Clint *str = &clint1;

			Clint *clint = new Clint(clint1.getInfloor(), clint1.getOutfloor(),
				clint1.getGiveupTime(), clint1.getIntime());
			(*clint)._M5(*this);

			_PeopleInLift++;

			sleep(25 * period,
				time2, time3,
				intime, time0,
				*this, giveupfrom, giveupto, infrom, into);

			freshQueue(*this);
		
		}
		if (!_WaitingUp[_floor].empty()) 
		{
			setUpButton(_floor);		//如果排队的人没有全部进入电梯
										//重新按下up
			sleep(1,
				time2, time3,
				intime, time0,
				*this, giveupfrom, giveupto, infrom, into);
		}
	}
	else if (_mode == 2) {
		while (!_WaitingDown[_floor].empty() && !isFull()) {
			Clint clint1 = _WaitingDown[_floor].back();
			Clint *clint = new Clint(clint1.getInfloor(), clint1.getOutfloor(),
				clint1.getGiveupTime(), clint1.getIntime());
			(*clint)._M5(*this);

			_PeopleInLift++;
			sleep(25 * period,
				time2, time3,
				intime, time0,
				*this, giveupfrom, giveupto, infrom, into);

			freshQueue(*this);

		}
		if (!_WaitingDown[_floor].empty()) {
			
			setDownButton(_floor);		//如果排队的人没有全部进入电梯
										//重新按下down
			sleep(1,
				time2, time3,
				intime, time0,
				*this, giveupfrom, giveupto, infrom, into);
		}
	}
	else if (_mode == 0) {
		;
	}

	_d3 = 1;							//电梯门开，但没人进出电梯
	_d1 = 0;							//电梯无人进出

	//Sleep()
}

/* not finish
* 名称：E5
* 描述：关门
* 参数：
* 返回：
* 注意：每隔 40 个 t 检查 D1，直到是 D1=0
 （若 D1≠0，则仍有人出入）。置 D3 为 0 并预 
  置电梯再 20 个 t 后启动活动 E6
  E6（再关门期间，若有人到来，则如 M2 所述，门再次打开）。
*/
void Lift::_E5(int& time2, int& time3,	//系统已经运行时间秒,毫秒
	int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
	int&giveupfrom, int&giveupto, int&infrom, int&into)
{
	_nowAction = E5;
	_d3 = 0;
	closeDoor(_floor,time2,time3,intime,time0,
		*this,giveupfrom,giveupto,infrom,into);
}

/*
* 名称：E6
* 描述：电梯准备移动
* 参数：
* 返回：移动—1；本层停候—2；将要前往 1 楼停候—3
* 注意：置 CallCar[Floor]为 0，而且
		若 State==GoingDown 则置 CallDown[Floor]为 0，
	    若 State==GoingUp 则置 CallUp[Floor]为 0。
		若 State==Idle 则都为0。
		调用 Controler 函数，判断下一个方向。

*/
void Lift::_E6(int& time1,int& time2, int& time3,	//系统已经运行时间秒,毫秒
				int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
				int&giveupfrom, int&giveupto, int&infrom, int&into)
{
	_nowAction = E6;
	Controller(time1,time2,time3,
		intime,time0,
		giveupfrom,giveupto,infrom,into);

	if (_nowStatus == Idle && _d2 == true)	//被controller判断为Idle状态，且未超时
		_nowStatus = Idle;
	else if (_nowStatus == Idle && _d2 == false)
		;
	else if (_nowStatus != Idle) {
		//_Move(time2, time3, intime, time0,
		//	giveupfrom, giveupto, infrom, into);
	}	
}

/*
* 名称：Controller
* 描述：对运行方向判断
* 参数：
* 返回：
* 注意：电梯只有在idle（停留）状态，才会改变方向
		if 函数返回5
		要重新计算time1！！！！
		time1=clock();
		time1为开始停侯的时间
*/
int Lift::Controller(int& time1,int& time2, int& time3,	//系统已经运行时间秒,毫秒
					int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
					int&giveupfrom, int&giveupto, int&infrom, int&into)
{
C1:		//[需要判断？] 若 State≠Idle，则返回
	if (_nowStatus != Idle)
		return 1;

C2:		//[应该开门？] 如果电梯处于 E1 且 CallUp[1], CallDown[1]
		//或 CallCar[1]非 0，则预置 20 个 t 后启动 E3，并返回。
	if (_nowAction == E1 &&
		(_button.CallCar[1] == 1 || _button.CallDown[1] == 1 || _button.CallUp[1] == 1))
	{
		sleep(20 * period,
			time2,time3,
			intime,time0,
			*this,giveupfrom,giveupto,infrom,into);		//需要重新封装
		_E3(time2, time3,
			intime, time0,
			giveupfrom, giveupto, infrom, into);
		return 2;
	}

C3:		//[有按钮按下？] 找最小的 j≠Floor
	int j;
	bool up=false;
	bool down = false;
	if (_mode!=2) {
	isup:
		for (j = _floor + 1; j <= LiftSize; j++) {
			if (_button.CallCar[j] == 1 || _button.CallDown[j] == 1 ||
				_button.CallUp[j] == 1)
				up = true;
		}

		if (up)						//如果上面有按钮， 则上楼
		{
			_mode=1;
			_nowStatus = GoingUp;
			return 3;
		}

		if (_mode!=2)				//电梯目前处于上升或停留，						
			goto isdown;			//若上面没人按按钮，则往下检查
		goto C4;					//当status==goingdown时，转入C4
	}
	if(_mode==2) {
	isdown:
		for (j = _floor - 1; j >= 1; j--) {
			if (_button.CallCar[j] == 1 || _button.CallDown[j] == 1 ||
				_button.CallUp[j] == 1)
				down = true;
		}

		if (down) {
			_mode=2;
			_nowStatus = GoingDown;
			return 4;
		}
		if (_mode==2)				//由isup跳转过来的不会执行这一步
									//直接进入C4
			goto isup;
		goto C4;
	}

C4:		//[置 State] 如果 Floor>j，则置 State 为 GoingDown；
		//如果 Floor<j，则置 State 为 GoingUp
	if (_button.CallUp[_floor] == 1) {
		_mode=1;
		_nowStatus = GoingUp;
		return 3;
	}
	else if (_button.CallDown[_floor] == 1) {
		_mode=2;
		_nowStatus = GoingDown;
		return 4;
	}
	else {
		_mode=0;
		time1 = clock();		//停侯开始的时间
		_nowStatus = Idle;
	}
	return 5;
}

/*
* 名称：_E7
* 描述：电梯上升
* 参数：
* 返回：
* 注意：
*/
void Lift::_E7(int& time2, int& time3,	//系统已经运行时间秒,毫秒
	int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
	int&giveupfrom, int&giveupto, int&infrom, int&into)
{
	Up(time2, time3, intime, time0, giveupfrom, giveupto, infrom, into);
	sleep(51 * period,
		time2, time3, intime, time0,
		*this, giveupfrom, giveupto, infrom, into);
}

/*
* 名称:_E8
* 描述：电梯下降
* 参数：
* 返回：
* 注意：
*/
void Lift::_E8(int& time2, int& time3,	//系统已经运行时间秒,毫秒
	int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
	int&giveupfrom, int&giveupto, int&infrom, int&into) 
{
	Down(time2,time3,intime,time0,giveupfrom,giveupto,infrom,into);
	sleep(61 * period,
		time2, time3, intime, time0,
		*this, giveupfrom, giveupto, infrom, into);
}

/*
* 名称：
* 描述：
* 参数：
* 返回：
* 注意：_Move后应该紧接 Control
*/
void Lift::_Move(int& time2, int& time3,	//系统已经运行时间秒,毫秒
	int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
	int&giveupfrom, int&giveupto, int&infrom, int&into)
{
	if (_nowStatus == GoingDown) {
		_E8(time2,time3,intime,time0,
			giveupfrom,giveupto,infrom,into);
	}
	else if (_nowStatus == GoingUp) {
		_E7(time2, time3, intime, time0,
			giveupfrom, giveupto, infrom, into);
	}
	_nowStatus = Idle;
}

/*
* 名称：ifOpenDoor
* 描述：判断此刻是否应该打开电梯门
* 参数：
* 返回：true--打开 false--不打开
* 注意：
*/
bool Lift::ifOpenDoor() {
	bool condition1 = (_mode == 1 && _button.CallUp[_floor] == 1);
	bool condition2 = (_mode == 2 && _button.CallDown[_floor] == 1);
	bool condition3 = (_button.CallCar[_floor] == 1);
	if ( condition1||condition2||condition3)									//有人要出来，开门
		return true;
	else
		return false;
}

/*
* 名称：isFull
* 描述：判断电梯是否满载
* 参数：
* 返回：
* 注意：
*/
bool Lift::isFull() {
	if (_PeopleInLift < _MaxPeopleInlift)
		return false;
	else
		return true;
}
