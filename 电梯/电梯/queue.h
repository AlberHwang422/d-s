#pragma once
#include"Clint.h"

class Queue
{
private:
	typedef struct node {
		Clint* data;
		node* next;
	}*Posi;				//结点定义

	Posi _font,			//头指针
		 _rear;			//尾指针
	int _size;
	bool free();
public:
	Queue();			//构造函数
	~Queue();			//析构函数
	bool push(Clint& clint);	//入队
	bool pop();			//出队
	Clint back();		//返回队头元素
	bool empty();		//判断队列是否为空
	int size();			//返回队列的大小
	void moveGiveUpClint();	//剔除放弃的乘客
	void drawQueue();	//在背景上，把排队的乘客画出来
};

