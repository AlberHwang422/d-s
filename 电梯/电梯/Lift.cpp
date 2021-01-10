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
* ���ƣ�Lift(int SizeOfLift=5)
* ��������ʼ������
* ������int
* ���أ���
* ע�⣺��
*/
Lift::Lift(int SizeOfFloor) {
	_LiftStack = new Stack[SizeOfFloor+1];		//���õ��ݳ�������,������¥�����
	_Waiting = new Queue[SizeOfFloor + 1];		//���������ŶӶ���
	_WaitingUp = new Queue[SizeOfFloor+1];		//���ó˿��ŶӶ���
	_WaitingDown = new Queue[SizeOfFloor+1];	//���ó˿��ŶӶ���

	_PeopleInLift = 0;								//��ǰ��������

	_floor = 1;										//���ó�ʼ����ͣ��λ��
	_d1 = _d2 = _d3 = true;						

	for (int i = 0; i < SizeOfFloor; i++)			//���õ��ݰ�ť
		_button.CallCar[i] = _button.CallDown[i] = _button.CallUp[i] = 0;

	_nowAction = E1;								//���ݳ�ʼ����
	_nowStatus = Idle;								//���ݳ�ʼ״̬��ͣ��
	_mode = 0;										//���ݳ�ʼ״̬��ͣ��
}

/*
* ���ƣ�Up()
* ��������������
* ������int
* ���أ�int
* ע�⣺��
*/
void Lift::Up(int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
	int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
	int&giveupfrom, int&giveupto, int&infrom, int&into)
{
	int maxsize = LiftSize;
	moveLift(*this, _mode, _floor,time2,time3,intime,time0,
		giveupfrom,giveupto,infrom,into);
	if (_floor < maxsize)	_floor++;
}

/*
* ���ƣ�Down()
* �����������½�
* ������int
* ���أ�int
* ע�⣺��
*/
void Lift::Down(int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
	int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
	int&giveupfrom, int&giveupto, int&infrom, int&into)
{
	moveLift(*this, _mode, _floor, time2, time3, intime, time0,
		giveupfrom, giveupto, infrom, into);
	if (_floor > 1)	_floor--;
}

/*
* ���ƣ�_drawPeopleInLift
* �������������е���
* ������y-Բ�ĵ�yֵ
* ���أ�
* ע�⣺
*/
void Lift::_drawPeopleInLift(int y) {
	int count = 0;
	for (int i = 1; i <= 6; i++) {
		_LiftStack[i].drawPeopleInStack(count, y);
	}
}

/*
* ���ƣ�drawPeopleInQueue
* ������
* ������
* ���أ�
* ע�⣺
*/
void Lift::_drawPeopleInQueue() 
{
	for (int i = 1; i <= 6; i++) {
		_WaitingUp[i].drawQueue();
		_WaitingDown[i].drawQueue();
	}
}



/*==============���ݻ================*/
/*
* ���ƣ�E1
* ������һ��ͣ��
* ������
* ���أ�
* ע�⣺
*/
void Lift::_E1(int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
			   int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
	           int&giveupfrom, int&giveupto, int&infrom, int&into) 
{
	if (_floor != 1)
		_E8(time2, time3, intime, time0, giveupfrom, giveupto,
			infrom, into);
}

/*
* ���ƣ�E2
* ������״̬�����ı�
* ������
* ���أ�
* ע�⣺
*/
void Lift::_E2() {
	_nowAction = E2;
}

/*	not finish ����Ŷ���  sleep
* ���ƣ�E3
* ��������ĳ�㿪��
* ������
* ���أ�
* ע�⣺
*/
void Lift::_E3(int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
			   int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
		       int&giveupfrom, int&giveupto, int&infrom, int&into)
{
	_d1 = _d2 = 1;
	_nowAction = E3;
	openDoor(_floor,time2,time3,intime,time0,
		*this,giveupfrom,giveupto,infrom,into);						//���Ŷ���
}

/*  				status==Idle״̬��û���
* ���ƣ�E4
* ���������˳���
* ������			sleep
* ���أ�
* ע�⣺�˿����ȳ����
*/
void Lift :: _E4(int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
				int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
				int&giveupfrom, int&giveupto, int&infrom, int&into)
{

	_nowAction = E4;
	_d1 = 1;
	if (_mode == 1)							//�����������������ģ������������
		cleanUp(_floor);
	else if (_mode == 2)					//���������½������ģ���������½�
		cleanDown(_floor);
	
											//���ݳ����ڣ���¥���ջ�������
	while (!_LiftStack[_floor].empty())		//��������Ҫ������
	{
		Clint clint1 = _LiftStack[_floor].top();
		Clint *clint = new Clint(clint1.getInfloor(), clint1.getOutfloor(),
				clint1.getGiveupTime(), clint1.getIntime());
		(*clint)._M6(*this);					//�˿���ȥ
		clearCar(_floor);
		_button.CallCar[_floor] = 0;
		_PeopleInLift--;
		sleep(25*period,
			time2, time3,
			intime, time0,
			*this, giveupfrom, giveupto, infrom, into);
	} 

	int y = 505 - (_floor - 1) * 100 + 20;	//�˿͵�λ��
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
			setUpButton(_floor);		//����Ŷӵ���û��ȫ���������
										//���°���up
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
			
			setDownButton(_floor);		//����Ŷӵ���û��ȫ���������
										//���°���down
			sleep(1,
				time2, time3,
				intime, time0,
				*this, giveupfrom, giveupto, infrom, into);
		}
	}
	else if (_mode == 0) {
		;
	}

	_d3 = 1;							//�����ſ�����û�˽�������
	_d1 = 0;							//�������˽���

	//Sleep()
}

/* not finish
* ���ƣ�E5
* ����������
* ������
* ���أ�
* ע�⣺ÿ�� 40 �� t ��� D1��ֱ���� D1=0
 ���� D1��0���������˳��룩���� D3 Ϊ 0 ��Ԥ 
  �õ����� 20 �� t ������� E6
  E6���ٹ����ڼ䣬�����˵��������� M2 ���������ٴδ򿪣���
*/
void Lift::_E5(int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
	int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
	int&giveupfrom, int&giveupto, int&infrom, int&into)
{
	_nowAction = E5;
	_d3 = 0;
	closeDoor(_floor,time2,time3,intime,time0,
		*this,giveupfrom,giveupto,infrom,into);
}

/*
* ���ƣ�E6
* ����������׼���ƶ�
* ������
* ���أ��ƶ���1������ͣ��2����Ҫǰ�� 1 ¥ͣ��3
* ע�⣺�� CallCar[Floor]Ϊ 0������
		�� State==GoingDown ���� CallDown[Floor]Ϊ 0��
	    �� State==GoingUp ���� CallUp[Floor]Ϊ 0��
		�� State==Idle ��Ϊ0��
		���� Controler �������ж���һ������

*/
void Lift::_E6(int& time1,int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
				int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
				int&giveupfrom, int&giveupto, int&infrom, int&into)
{
	_nowAction = E6;
	Controller(time1,time2,time3,
		intime,time0,
		giveupfrom,giveupto,infrom,into);

	if (_nowStatus == Idle && _d2 == true)	//��controller�ж�ΪIdle״̬����δ��ʱ
		_nowStatus = Idle;
	else if (_nowStatus == Idle && _d2 == false)
		;
	else if (_nowStatus != Idle) {
		//_Move(time2, time3, intime, time0,
		//	giveupfrom, giveupto, infrom, into);
	}	
}

/*
* ���ƣ�Controller
* �����������з����ж�
* ������
* ���أ�
* ע�⣺����ֻ����idle��ͣ����״̬���Ż�ı䷽��
		if ��������5
		Ҫ���¼���time1��������
		time1=clock();
		time1Ϊ��ʼͣ���ʱ��
*/
int Lift::Controller(int& time1,int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
					int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
					int&giveupfrom, int&giveupto, int&infrom, int&into)
{
C1:		//[��Ҫ�жϣ�] �� State��Idle���򷵻�
	if (_nowStatus != Idle)
		return 1;

C2:		//[Ӧ�ÿ��ţ�] ������ݴ��� E1 �� CallUp[1], CallDown[1]
		//�� CallCar[1]�� 0����Ԥ�� 20 �� t ������ E3�������ء�
	if (_nowAction == E1 &&
		(_button.CallCar[1] == 1 || _button.CallDown[1] == 1 || _button.CallUp[1] == 1))
	{
		sleep(20 * period,
			time2,time3,
			intime,time0,
			*this,giveupfrom,giveupto,infrom,into);		//��Ҫ���·�װ
		_E3(time2, time3,
			intime, time0,
			giveupfrom, giveupto, infrom, into);
		return 2;
	}

C3:		//[�а�ť���£�] ����С�� j��Floor
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

		if (up)						//��������а�ť�� ����¥
		{
			_mode=1;
			_nowStatus = GoingUp;
			return 3;
		}

		if (_mode!=2)				//����Ŀǰ����������ͣ����						
			goto isdown;			//������û�˰���ť�������¼��
		goto C4;					//��status==goingdownʱ��ת��C4
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
		if (_mode==2)				//��isup��ת�����Ĳ���ִ����һ��
									//ֱ�ӽ���C4
			goto isup;
		goto C4;
	}

C4:		//[�� State] ��� Floor>j������ State Ϊ GoingDown��
		//��� Floor<j������ State Ϊ GoingUp
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
		time1 = clock();		//ͣ�ʼ��ʱ��
		_nowStatus = Idle;
	}
	return 5;
}

/*
* ���ƣ�_E7
* ��������������
* ������
* ���أ�
* ע�⣺
*/
void Lift::_E7(int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
	int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
	int&giveupfrom, int&giveupto, int&infrom, int&into)
{
	Up(time2, time3, intime, time0, giveupfrom, giveupto, infrom, into);
	sleep(51 * period,
		time2, time3, intime, time0,
		*this, giveupfrom, giveupto, infrom, into);
}

/*
* ����:_E8
* �����������½�
* ������
* ���أ�
* ע�⣺
*/
void Lift::_E8(int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
	int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
	int&giveupfrom, int&giveupto, int&infrom, int&into) 
{
	Down(time2,time3,intime,time0,giveupfrom,giveupto,infrom,into);
	sleep(61 * period,
		time2, time3, intime, time0,
		*this, giveupfrom, giveupto, infrom, into);
}

/*
* ���ƣ�
* ������
* ������
* ���أ�
* ע�⣺_Move��Ӧ�ý��� Control
*/
void Lift::_Move(int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
	int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
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
* ���ƣ�ifOpenDoor
* �������жϴ˿��Ƿ�Ӧ�ô򿪵�����
* ������
* ���أ�true--�� false--����
* ע�⣺
*/
bool Lift::ifOpenDoor() {
	bool condition1 = (_mode == 1 && _button.CallUp[_floor] == 1);
	bool condition2 = (_mode == 2 && _button.CallDown[_floor] == 1);
	bool condition3 = (_button.CallCar[_floor] == 1);
	if ( condition1||condition2||condition3)									//����Ҫ����������
		return true;
	else
		return false;
}

/*
* ���ƣ�isFull
* �������жϵ����Ƿ�����
* ������
* ���أ�
* ע�⣺
*/
bool Lift::isFull() {
	if (_PeopleInLift < _MaxPeopleInlift)
		return false;
	else
		return true;
}
