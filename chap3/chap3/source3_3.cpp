//소스코드3.3: Queue 자료구조
#include <iostream>
#include <memory>

using namespace std;

template <class T>
class Queue
{
public:
	Queue(int queueCapacity = 10);
	bool IsEmpty();
	T& Front();
	T& Rear();
	void Push(T const& x);
	void Pop();
	friend ostream& operator<<<T>(ostream& os, Queue<T>&);
	friend istream& operator>><T>(istream& os, Queue<T>&);
private:
	T* queue;
	int front;
	int rear;
	int capacity;
};
template <class T>
ostream& operator<<(ostream& os, Queue<T>& s) {

}
template <class T>
istream& operator>>(istream& os, Queue<T>& s) {

}
template <class T>
Queue<T>::Queue(int queueCapacity) : capacity(queueCapacity)
{
	queue = new T[capacity];
	front = rear = -1;
}

template <class T>
inline bool  Queue<T>::IsEmpty() { return front == rear; }

template <class T>
inline T& Queue<T>::Front()
{
	if (IsEmpty()) throw "Queue is empty. No front element";
	return queue[(front + 1) % capacity];
}

template <class T>
inline T& Queue<T>::Rear()
{
	if (IsEmpty()) throw "Queue is empty. No rear element";
	return queue[rear];
}

// doubling queue capacity
template <class T>
void Queue<T>::Push(T const& x)
{
	if ((rear + 1) % capacity == front)
	{
		T* newQueue = new T[2 * capacity];
		// allocate an array with twice the capacity
		int start = (front + 1) % capacity;
		if (start < 2)
			//copy(queue + start, queue + start + capacity - 1, newQueue);
			memcpy(newQueue, queue + start, start + capacity - 1);
		else
		{
			//copy(queue + start, queue + capacity, newQueue);
			//copy(queue, queue + rear + 1, newQueue + capacity - start);
			memcpy(newQueue, queue + start, capacity);
			memcpy(newQueue + capacity - start, queue, rear + 1);
		}
		// switch to new Queue
		front = 2 * capacity - 1;
		rear = capacity - 2;
		capacity *= 2;
		delete[] queue;
		queue = newQueue;
	}

	rear = (rear + 1) % capacity;
	queue[rear] = x;
}

template <class T>
void Queue<T>::Pop()
{
	if (IsEmpty()) throw "Queue is empty. Cannot delelte.";
	front = (front + 1) % capacity;
	queue[front].~T();
}

void main()
{
	Queue<int> s(3);
	s.Push(2);
	s.Push(1);
	s.Push(4);
	//s.Push(10); //구현시에 doubling 동작 가능한지 테스트
	cin >> s; //구현 실습
	if (s.IsEmpty()) {
		cout << "empty" << endl;
	}
	else {
		cout << "not empty" << endl;
	}

	while (!s.IsEmpty()) {
		cout << s.Front() << endl;
		s.Pop();
	}
	//cout << s << endl;//가능하도록 필요한 함수를 추가 구현한다
	system("pause");
}