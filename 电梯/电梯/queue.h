#pragma once
#include"Clint.h"

class Queue
{
private:
	typedef struct node {
		Clint* data;
		node* next;
	}*Posi;				//��㶨��

	Posi _font,			//ͷָ��
		 _rear;			//βָ��
	int _size;
	bool free();
public:
	Queue();			//���캯��
	~Queue();			//��������
	bool push(Clint& clint);	//���
	bool pop();			//����
	Clint back();		//���ض�ͷԪ��
	bool empty();		//�ж϶����Ƿ�Ϊ��
	int size();			//���ض��еĴ�С
	void moveGiveUpClint();	//�޳������ĳ˿�
	void drawQueue();	//�ڱ����ϣ����Ŷӵĳ˿ͻ�����
};

