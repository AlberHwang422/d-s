#pragma once
#include"Clint.h"

class Stack
{
private:
	typedef struct node {
		Clint* data;
		node* next;
	}*Posi;			//���Ķ���
	Posi _top;		//ջ��ָ��
	int _size;		//ջ�Ĵ�С

public:
	Stack();		//ջ�Ĺ��캯��
	Clint top();	//�õ�ջ��Ԫ��
	void drawPeopleInStack(int& count,int y);
					//�������ݳ����еĳ˿�
	bool push(Clint& clint);
					//��ջ
	bool pop();		//��ջ
	bool empty();	//�ж�ջ�Ƿ�Ϊ��
	bool free();	//����ջ
	int size();		//����ջ�Ĵ�С
};

