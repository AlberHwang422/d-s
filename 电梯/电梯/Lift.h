#pragma once
#define WIN32
#include"stack.h"
#include"queue.h"
using namespace std;
#define LiftSize 6			//����¥
#define period (10)	//0.01��

class Clint;
class Lift {
private:
	int _floor;	//���ݵ�ǰλ��
	
	int _MaxPeopleInlift = 10; //�����������
	int _PeopleInLift;	//��ǰ��������

	bool _d1;	//d1=1,���ڽ�������
				//d1=0�����˽�������
	bool _d2;	//d2=1,�����Ѿ�ͣ��δ��ʱ;
				//d2=0������û����ĳ��ͣ��300t
	bool _d3;	//d3=1,�����ſ��������˽�������
				//d3=0,�����ſ��������˽�������

	//�����䰴ť����
	typedef struct Button {
		int CallUp[LiftSize+1],CallDown[LiftSize + 1];   //ÿ���������������½���ť
		int CallCar[LiftSize + 1];				 //�������ڵ�ÿ�㰴ť
	}Button;
	Button _button;

	//���ݻ��9��״̬��
	typedef enum ElevatorActivity {
		E1 = 1,	//��һ��ȴ�
		E2 = 2,	//�ı�״̬ ����:������ �� �½�
		E3 = 3,	//����
		E4 = 4,	//���˳����ݣ�ǰ�᣺1.���ݲ��գ�2.clint.outfloor=floor
		E5 = 5,	//���ţ�ÿ��40T�����һ��D1��
		E6 = 6,	//׼���ƶ�״̬
		E7 = 7,	//����floor+1
		E8 = 8,	//�½�floor-1
		E9 = 9	//���ָʾ����
	}ElevatorActivity;
	ElevatorActivity _nowAction,	//��ǰ����
					 _nextAction,	//��һ����
		             _thirdAction;	//����������

	//����״̬��3��״̬��
	typedef enum LStatus {
		GoingUp = 1,	//����
		GoingDown = 2,	//�½�
		Idle = 0,		//ͣ��
	}LStatus;

	int _mode;			//�����н�ģʽ��0-ͣ����1-������2-�½�

	LStatus _nowStatus,	//��ǰ״̬
	     	_nextStaus;	//��һ״̬

public:
	Queue* _WaitingUp;	//�˿��ŶӶ��У�������
	Queue* _WaitingDown;//�˿��ŶӶ��У��½���
	Queue* _Waiting;	//���������ŶӶ���
	Stack* _LiftStack;	//���ݳ���

private:
	//��������
	void Up(int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
		int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
		int&giveupfrom, int&giveupto, int&infrom, int&into);	
	//�����½�
	void Down(int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
		int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
		int&giveupfrom, int&giveupto, int&infrom, int&into);


public:

	void _E1(int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
			 int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
			 int&giveupfrom, int&giveupto, int&infrom, int&into);				//һ¥ͣ��
	void _E2();				//Ҫ�ı��״̬
	
	/*����*/
	void _E3(int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
			 int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
		   	 int&giveupfrom, int&giveupto, int&infrom, int&into);				//��ĳ�㿪��

	
	/*����*/
	void _E4(int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
		   	 int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
			 int&giveupfrom, int&giveupto, int&infrom, int&into);
	
	/*����*/
	void _E5(int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
		int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
		int&giveupfrom, int&giveupto, int&infrom, int&into);
	
	/*׼���ƶ�*/
	void _E6(int& time1,int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
			 int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
			 int&giveupfrom, int&giveupto, int&infrom, int&into);			
	
	/*up*/
	void _E7(int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
			 int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
			 int&giveupfrom, int&giveupto, int&infrom, int&into);				
	
	/*�½�*/
	void _E8(int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
			 int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
			 int&giveupfrom, int&giveupto, int&infrom, int&into);
	
	/*�ƶ�*/
	void _Move(int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
			   int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
			   int&giveupfrom, int&giveupto, int&infrom, int&into);
	

	int Controller(int& time1,int& time2, int& time3,	//ϵͳ�Ѿ�����ʱ����,����
				   int& intime, int&time0,	//��һ����ˢ�µ�ʱ��������һ�������ɵĽ���ʱ��
				   int&giveupfrom, int&giveupto, int&infrom, int&into);
public:
	Lift(int SizeOfFloor);	//���캯��
	int getFloor();
	int getMaxSize();
	int getPeoPleInLift();

	void _drawPeopleInQueue();			//���Ŷ��е���
	void _drawPeopleInLift(int y);		//�������е���

	bool isFull();			//�ж��Ƿ�����
	bool ifOpenDoor();		//�ж��Ƿ�Ҫ����

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

