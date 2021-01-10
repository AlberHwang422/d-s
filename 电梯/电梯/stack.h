#pragma once
#include"Clint.h"

class Stack
{
private:
	typedef struct node {
		Clint* data;
		node* next;
	}*Posi;			//结点的定义
	Posi _top;		//栈顶指针
	int _size;		//栈的大小

public:
	Stack();		//栈的构造函数
	Clint top();	//得到栈顶元素
	void drawPeopleInStack(int& count,int y);
					//画出电梯车厢中的乘客
	bool push(Clint& clint);
					//入栈
	bool pop();		//出栈
	bool empty();	//判断栈是否为空
	bool free();	//销毁栈
	int size();		//返回栈的大小
};

