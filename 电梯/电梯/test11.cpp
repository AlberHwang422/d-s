#include"Clint.h"
#include"stack.h"
#include"queue.h"
#include"tool.h"
#include"Lift.h"
#include<iostream>
#include<graphics.h>
#include<conio.h>
using namespace std;


int main() {
	background();

	Lift lift = Lift(6);
	Clint clint1 = Clint(1, 6, 5, 5);
	Clint clint2 = Clint(1, 2, 5, 5);
	Clint clint3 = Clint(1, 3, 5, 5);
	Clint clint4 = Clint(1, 4, 5, 5);
	//clint1._M3(lift);
	//clint2._M3(lift);
	clint3._M3(lift);
	//clint4._M3(lift);

	int a = 1, b = 1;
	for (int i = 0; i < 30; i++)
		initClint(lift, a, b, a, b);
	lift._WaitingDown[6];
	lift._WaitingDown[5];
	lift._WaitingDown[4];
	lift._WaitingDown[3];
	lift._WaitingDown[2];
	lift._WaitingDown[1];
	lift._WaitingUp[1];
	lift._WaitingUp[2];
	lift._WaitingUp[3];
	lift._WaitingUp[4];
	lift._WaitingUp[5];
	lift._WaitingUp[6];
	pressUp(5);
	pressUp(3);
	pressDown(3);
	pressDown(4);
	pressDown(2);
	pressCar(1);
	pressCar(2);
	pressCar(6);
	drawLift(5);
	Sleep(300);
	clearCar(2);
	int time = 50;
	drawTime(time);
	Sleep(300);
	time = 55;
	drawTime(time);
	while (!lift._WaitingDown[6].empty())
	{
		lift._WaitingUp[1].pop();
		lift._WaitingDown[5].pop();
		lift._WaitingDown[6].pop();
		freshQueue(lift);
		Sleep(300);
	}
	_getch();
	closegraph();
	

	cin.get();
	cin.get();
}