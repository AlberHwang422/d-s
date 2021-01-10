#pragma once
#define WIN32
using namespace std;
class Lift;

class Clint {
private:
	//�˿͵Ķ���
	typedef enum ClintAction {
		MO = 0,
		M1 = 1,	//����ϵͳ���ɳ˿�
		M2 = 1,	//������ť ���������½�
		M3 = 3,	//�����ŶӶ���
		M4 = 4,	//����
		M5 = 5,	//�������
		M6 = 6,	//�뿪
	}ClintAction;

	ClintAction _action;

	int _InFloor,	//�˿ͳ���¥��
		_OutFloor;
	int _inTime,
		_GiveUpTime;

public:
	Clint(int InFloor, int OutFloor, int GiveUp,int intime);	//���캯��

	bool canNotBear();			//�ж��Ƿ��޷�����
	void _M2(Lift& lift);
	void _M3(Lift& lift);		//�����Ŷ�
	void _M4(Lift& lift);		//�����Ŷ�
	void _M5(Lift& lift);		//�������
	void _M6(Lift& lift);		//������

	int getInfloor() { return _InFloor; };
	int getOutfloor() { return _OutFloor; };
	int getIntime() { return _inTime; };
	int getGiveupTime() { return _GiveUpTime; };
};