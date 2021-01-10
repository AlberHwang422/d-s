#include<iostream>
#include"Lift.h"
#include"Clint.h"
#include"tool.h"
#include<time.h>
#include<Windows.h>
using namespace std;
void inlift(Lift& lift) {
	Clint clint = lift._WaitingUp[1].back();
	Clint *clint2 = new Clint(clint.getInfloor(), clint.getOutfloor(), 51, 51);
	lift._WaitingDown[1].push(*clint2);
}

void funB()
{
C1:int a = 1;
	if (a == 1)
		goto C3;
C2:cout << "a2";
C3:cout << "a3";

	cin.get();
	cin.get();
}

int main() {
	int time;
	for (int i = 0; i <= 500; i++)
	{
		time = clock() / 1000;
		Sleep(100);
		cout << time << " ";
	}
	cin.get();
	cin.get();
	return 0;
}