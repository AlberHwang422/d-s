#include "stack.h"
#include"Clint.h"
#include"tool.h"

void Stack::drawPeopleInStack(int& count,int y) {
	Posi z = _top;
	while (z != nullptr) {
		count++;
		Clint clint = *(z->data);
		drawPeopleInLift(count, y, clint.getOutfloor());
		z = z->next;
	}
}
Stack::Stack() {
	_top = nullptr;
	_size = 0;
}

Clint Stack::top() {
	if (_top)
		return *(_top->data);
}

bool Stack::push(Clint& clint) {
	Posi z = new node;
	(z->data) = &clint;
	z->next = _top;
	_top = z;
	_size++;
	return true;
};

bool Stack::pop() {
	if (_top != nullptr) {
		Posi z = _top;
		_top = _top->next;
		z->next = nullptr;
		delete z;
		return true;
	}
	else
		return false;
	
}

bool Stack::empty() {
	if (_top == nullptr)	return true;
	else
		return false;
}

bool Stack::free() {
	while (_top!=nullptr){
		Posi z = _top;
		_top = _top->next;
		z->next = nullptr;
		delete z;
	}
	if (_top == nullptr)	return true;
}

int Stack::size() {
	return _size;
}




