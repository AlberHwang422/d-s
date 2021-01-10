#include "queue.h"
#include"tool.h"


Queue::Queue()
{
	_font = nullptr;
	_rear = nullptr;
	_size = 0;
}

Queue::~Queue()
{
	free();
}

bool Queue::push(Clint& clint) {
	Posi z = new node;
	z->data = &clint;
	z->next = nullptr;
	if (_font == nullptr) {
		_rear=_font = z;
	}
	else {
		z->next = _rear;
		_rear = z;
	}
	_size++;
	return true;
}

bool Queue::pop() {
	if (empty())	return false;
	else {
		if (_size == 1) {
			Posi z = _font;
			delete z;
			_font = _rear = nullptr;
		}
		else {
			Posi z = _font;
			Posi head=_rear;
			while (head->next != z)	head = head->next;
			head->next = nullptr;
			delete z;
			_font = head;
		}
		_size--;
		return true;
	}
}

Clint Queue::back() {
	if (!empty()&&_rear!=nullptr) {
		return *(_font->data);
	}
}

bool Queue::empty() {
	if (_font == nullptr&&_rear == nullptr)
		return true;
	else if (_size == 0)
		return true;
	else
		return false;
}

bool Queue::free() {
	while (!empty())
		pop();
	if (empty())	return true;
	else
		return false;
}

int Queue::size() {
	return _size;
}

/*
* ���ƣ�moveGiveUpClint
* ������ˢ���ŶӶ���
* ������
* ���أ�
* ע�⣺Clint��M4����ʵ���Ͼ������������
		�ڲ�һ��ˢ�¶��еĶ���
*/
void Queue::moveGiveUpClint() {
	Posi z=_rear ;

	while (z != nullptr)
	{
		Clint clint = *(z->data);
		if (clint.canNotBear())		//Z�˿Ͳ�������
									//�˳�����
		{	
			if (_size == 1)			//���������ֻ��1����
			{
				_font = nullptr;
				_rear = nullptr;
				delete z;
				_size--;
				break;
			}
			if (z == _rear)			//���ɾ�����Ƕ�β
			{
				Posi h = z->next;
				delete z;
				z = h;
				_rear = h;			//�����µĶ�β
				_size--;
				continue;
			}
			else if (z == _font)
			{
				break;
			}
			else			
			{
				Posi h=z->next;		//h=z���
				Posi q = _rear;			//q=zǰ��
				while (q->next != z)	q = q->next;
				q->next = h;
				delete z;
				_size--;
				z = h;
				continue;
			}
		}

		z = z->next;
	}

}

/*
* ���ƣ�drawQueue
* ��������һ�¶������Ŷӵ�����
* ������
* ���أ�
* ע�⣺
*/
void Queue::drawQueue() {
	Posi z = _rear;
	int count=0;
	if (_rear != nullptr)	count = 1;
	while (z!=nullptr) {
		Clint clint = *(z -> data);
		drawClint(count, clint.getInfloor(), clint.getOutfloor());
		z = z->next;
		count++;
	}
}
