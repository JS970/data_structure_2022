#include <iostream>
#include <memory>

using namespace std;

template <class T>
class Deque
{
public:
	Deque();
	Deque(int dequeCapacity);
	bool IsEmpty();
	T& Front();
	T& Rear();
	void Push_front(T const& x);
	void Push_rear(T const& x);
	void Pop_front();
	void Pop_rear();
	friend ostream& operator <<<T>(ostream& os, Deque<T>&);
	// friend istream& operator <<<T>(istream& is, Deque<T>&);
private:
	T* deque;
	int front;
	int rear;
	int capacity;
};

template <class T>
ostream& operator <<(ostream& os, Deque<T>& s)
{
	for(int i = s.front; i <= s.rear; i++)
		os << s.deque[i] << " ";
	os << endl;
	return os;
}

/*
template <class T>
istream& operator >>(istream& is, Deque<T>& s)
{

}
*/

template <class T>
Deque<T>::Deque(int queueCapacity) : capacity(queueCapacity)
{
	deque = new T[capacity];
	front = rear = -1;
}

template <class T>
Deque<T>::Deque()
{
	capacity = 2;
	deque = new T[capacity];
	front = rear = -1;
}

template <class T>
inline bool Deque<T>::IsEmpty()
{
	return (front > rear) || (front == rear == -1);
}

template <class T>
inline T& Deque<T>::Front()
{
	if (IsEmpty()) throw "Queue is empty. No front element";
	return deque[front];
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
	if (front == -1)
	{
		front = rear = 0;
		deque[front] = x;
	}
	else if (front == 0)
	{
		T* newDeque = new T[2 * (capacity)];
		int start = front; int end = rear;
		memcpy(newDeque + (capacity * 2 / 3), deque + start, (end - start + 1) * sizeof(T));
		front = capacity * 2 / 3;
		rear = front + end - start;
		capacity *= 2;
		delete[] deque;
		deque = newDeque;
		deque[--front] = x;
	}
	else
	{
		deque[--front] = x;
	}
}

template <class T>
void Deque<T>::Push_rear(T const& x)
{
	if (rear == -1)
	{
		front = rear = 0;
		deque[rear] = x;
	}
	else if (rear == capacity - 1)
	{
		T* newDeque = new T[2 * (capacity)];
		int start = front; int end = rear;
		memcpy(newDeque + (capacity * 2 / 3), deque + start, (end - start + 1) * sizeof(T));
		front = capacity * 2 / 3;
		rear = front + end - start;
		capacity *= 2;
		delete[] deque;
		deque = newDeque;
		deque[++rear] = x;
	}
	else
	{
		deque[++rear] = x;
	}
}

template <class T>
void Deque<T>::Pop_front()
{
	if (IsEmpty()) throw "Deque is empty. Cannot delete.";
	front++;
	deque[front - 1].~T();
}

template <class T>
void Deque<T>::Pop_rear()
{
	if (IsEmpty()) throw "Deque is empty. Cannot delete.";
	rear--;
	deque[rear + 1].~T();
}

int main()
{
	Deque<int> s;
	s.Push_front(1);
	s.Push_rear(1);

	s.Push_front(2);
	s.Push_rear(2);

	s.Push_front(3);
	s.Push_rear(3);
	s.Push_front(4);
	s.Push_rear(4);

	s.Push_front(5);
	s.Push_rear(5);
	s.Push_front(6);
	s.Push_rear(6);
	s.Push_front(7);
	s.Push_rear(7);
	s.Push_front(8);
	s.Push_rear(8);
	s.Push_front(9);
	s.Push_rear(9);
	s.Push_front(10);
	s.Push_rear(10);
	s.Push_front(11);

	cout << s;

	return 0;
}