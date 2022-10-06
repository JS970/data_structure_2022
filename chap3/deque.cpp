#include <iostream>
#include <memory>

using namespace std;

template <class T>
class Deque
{
public:
	Deque(int dequeCapacity = 2);
	bool IsEmpty();
	T& Front();
	T& Rear();
	void Push_front(T const& x);
	void Push_rear(T const& x);
	void Pop_front();
	void Pop_rear();
	friend ostream& operator <<<T>(ostream& os, Deque<T>&);
	friend istream& operator <<<T>(istream& is, Deque<T>&);

private:
	T* deque;
	int front;
	int rear;
	int capacity;
};

template <class T>
ostream& operator <<(ostream& os, Deque<T>& s)
{

}

template <class T>
istream& operator >>(istream& is, Deque<T>& s)
{

}

template <class T>
Deque<T>::Deque(int queueCapacity) : capacity(queueCapacity)
{
	queue = new T[capacity];
	front = rear = -1;
}

template <class T>
inline bool Deque<T>::IsEmpty()
{
	return front == rear;
}

template <class T>
inline T& Deque<T>::Front()
{
	if (IsEmpty()) throw "Queue is empty. No front element";
	return deque[(front + 1) % capacity];
}

template <class T>
inline T& Deque<T>::Rear()
{
	if (IsEmpty()) throw "Queue is empty. No rear element";
	return deque[rear];
}

template <class T>
void Deque<T>::Push_front(T const& x)
{
	if ((rear + 1) % capacity == front)
	{
		T* newDeque = new T[2 * capacity];
		int start = (front + 1) % capacity;
		if (start < 2)
			memcpy(newDeque, deque + start, start + capacity - 1);
		else
		{
			memcpy(newDeque, deque + start, capacity);
			memcpy(newDeque + capacity - start, deque, rear + 1);
		}
		front = 2 * capacity - 1;
		rear = capacity - 2;
		capacity *= 2;
		delete[] deque;
		deque = newDeque;
	}
	front = (front - 1) % capacity;
	deque[front] = x;
}

template <class T>
void Deque<T>::Push_rear(T const& x)
{
	if ((rear + 1) % capacity == front)
	{
		T* newDeque = new T[2 * capacity];
		int start = (front + 1) % capacity;
		if (start < 2)
			memcpy(newDeque, deque + start, start + capacity - 1);
		else
		{
			memcpy(newDeque, deque + start, capacity);
			memcpy(newDeque + capacity - start, deque, rear + 1);
		}
		front = 2 * capacity - 1;
		rear = capacity - 2;
		capacity *= 2;
		delete[] queue;
		deque = newDeque;
	}
	rear = (rear + 1) % capacity;
	deque[rear] = x;
}

template <class T>
void Deque<T>::Pop_front()
{
	If(IsEmpty()) throw "Deque is empty. Cannot delete.";
	rear = (rear - 1) % capacity;
	deque[rear].~T();
}

template <class T>
void Deque<T>::Pop_rear()
{
	if (IsEmpty()) throw "Deque is empty. Cannot delete.";
	front = (front + 1) % capacity;
	deque[front].~T();
}