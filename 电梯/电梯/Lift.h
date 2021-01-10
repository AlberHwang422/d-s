#pragma once
#define WIN32
#include"stack.h"
#include"queue.h"
using namespace std;
#define LiftSize 6			//六层楼
#define period (10)	//0.01秒

class Clint;
class Lift {
private:
	int _floor;	//电梯当前位置
	
	int _MaxPeopleInlift = 10; //最大容纳人数
	int _PeopleInLift;	//当前电梯人数

	bool _d1;	//d1=1,人在进出电梯
				//d1=0，无人进出电梯
	bool _d2;	//d2=1,电梯已经停留未超时;
				//d2=0，电梯没有在某层停留300t
	bool _d3;	//d3=1,电梯门开，但有人进出电梯
				//d3=0,电梯门开，又无人进出电梯

	//电梯箱按钮设置
	typedef struct Button {
		int CallUp[LiftSize+1],CallDown[LiftSize + 1];   //每层电梯外的上升或下降按钮
		int CallCar[LiftSize + 1];				 //电梯箱内的每层按钮
	}Button;
	Button _button;

	//电梯活动（9种状态）
	typedef enum ElevatorActivity {
		E1 = 1,	//第一层等待
		E2 = 2,	//改变状态 例如:由上升 变 下降
		E3 = 3,	//开门
		E4 = 4,	//让人出电梯，前提：1.电梯不空，2.clint.outfloor=floor
		E5 = 5,	//关门（每隔40T，检查一次D1）
		E6 = 6,	//准备移动状态
		E7 = 7,	//上升floor+1
		E8 = 8,	//下降floor-1
		E9 = 9	//不活动指示器？
	}ElevatorActivity;
	ElevatorActivity _nowAction,	//当前动作
					 _nextAction,	//下一动作
		             _thirdAction;	//第三个动作

	//电梯状态（3种状态）
	typedef enum LStatus {
		GoingUp = 1,	//上上
		GoingDown = 2,	//下降
		Idle = 0,		//停留
	}LStatus;

	int _mode;			//电梯行进模式，0-停留，1-上升，2-下降

	LStatus _nowStatus,	//当前状态
	     	_nextStaus;	//下一状态

public:
	Queue* _WaitingUp;	//乘客排队队列（上升）
	Queue* _WaitingDown;//乘客排队队列（下降）
	Queue* _Waiting;	//电梯门外排队队列
	Stack* _LiftStack;	//电梯车厢

private:
	//电梯上升
	void Up(int& time2, int& time3,	//系统已经运行时间秒,毫秒
		int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
		int&giveupfrom, int&giveupto, int&infrom, int&into);	
	//电梯下降
	void Down(int& time2, int& time3,	//系统已经运行时间秒,毫秒
		int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
		int&giveupfrom, int&giveupto, int&infrom, int&into);


public:

	void _E1(int& time2, int& time3,	//系统已经运行时间秒,毫秒
			 int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
			 int&giveupfrom, int&giveupto, int&infrom, int&into);				//一楼停侯
	void _E2();				//要改变的状态
	
	/*开门*/
	void _E3(int& time2, int& time3,	//系统已经运行时间秒,毫秒
			 int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
		   	 int&giveupfrom, int&giveupto, int&infrom, int&into);				//在某层开门

	
	/*出入*/
	void _E4(int& time2, int& time3,	//系统已经运行时间秒,毫秒
		   	 int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
			 int&giveupfrom, int&giveupto, int&infrom, int&into);
	
	/*关门*/
	void _E5(int& time2, int& time3,	//系统已经运行时间秒,毫秒
		int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
		int&giveupfrom, int&giveupto, int&infrom, int&into);
	
	/*准备移动*/
	void _E6(int& time1,int& time2, int& time3,	//系统已经运行时间秒,毫秒
			 int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
			 int&giveupfrom, int&giveupto, int&infrom, int&into);			
	
	/*up*/
	void _E7(int& time2, int& time3,	//系统已经运行时间秒,毫秒
			 int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
			 int&giveupfrom, int&giveupto, int&infrom, int&into);				
	
	/*下降*/
	void _E8(int& time2, int& time3,	//系统已经运行时间秒,毫秒
			 int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
			 int&giveupfrom, int&giveupto, int&infrom, int&into);
	
	/*移动*/
	void _Move(int& time2, int& time3,	//系统已经运行时间秒,毫秒
			   int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
			   int&giveupfrom, int&giveupto, int&infrom, int&into);
	

	int Controller(int& time1,int& time2, int& time3,	//系统已经运行时间秒,毫秒
				   int& intime, int&time0,	//下一个人刷新的时间间隔，上一个人生成的结束时间
				   int&giveupfrom, int&giveupto, int&infrom, int&into);
public:
	Lift(int SizeOfFloor);	//构造函数
	int getFloor();
	int getMaxSize();
	int getPeoPleInLift();

	void _drawPeopleInQueue();			//画排队中的人
	void _drawPeopleInLift(int y);		//画电梯中的人

	bool isFull();			//判断是否满载
	bool ifOpenDoor();		//判断是否要开门

	int getmode() { return _mode; };
	bool getD1();
	bool getD2();
	bool getD3();

	void setUpButton(int floor);
	void setDownButton(int floor);
	void setCarButton(int floor);

	void cleanUp(int floor);
	void cleanDown(int floor);
	void cleanCar(int floor);

	void clearUpButton(int floor) {
		_button.CallUp[floor] = 0;
	};
	void clearDownButton(int floor) {
		_button.CallDown[floor] = 0;
	};
	void clearCarButton(int floor) {
		_button.CallCar[floor] = 0;
	}
};

