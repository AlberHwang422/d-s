#pragma once
#define WIN32
using namespace std;
class Lift;

class Clint {
private:
	//乘客的动作
	typedef enum ClintAction {
		MO = 0,
		M1 = 1,	//进入系统生成乘客
		M2 = 1,	//按动电钮 上升或者下降
		M3 = 3,	//进入排队队列
		M4 = 4,	//放弃
		M5 = 5,	//进入电梯
		M6 = 6,	//离开
	}ClintAction;

	ClintAction _action;

	int _InFloor,	//乘客出生楼层
		_OutFloor;
	int _inTime,
		_GiveUpTime;

public:
	Clint(int InFloor, int OutFloor, int GiveUp,int intime);	//构造函数

	bool canNotBear();			//判断是否无法忍受
	void _M2(Lift& lift);
	void _M3(Lift& lift);		//进入排队
	void _M4(Lift& lift);		//放弃排队
	void _M5(Lift& lift);		//进入电梯
	void _M6(Lift& lift);		//出电梯

	int getInfloor() { return _InFloor; };
	int getOutfloor() { return _OutFloor; };
	int getIntime() { return _inTime; };
	int getGiveupTime() { return _GiveUpTime; };
};