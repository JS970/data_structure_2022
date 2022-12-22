//�ҽ��ڵ�3.3: Queue �ڷᱸ��
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
	// friend ostream& operator<<<T>(ostream& os, Queue<T>&);
	// friend istream& operator>><T>(istream& os, Queue<T>&);
private:
	T* queue;
	int front;
	int rear;
	int capacity;
};

/*
template <class T>
ostream& operator<<(ostream& os, Queue<T>& s) {

}
template <class T>
istream& operator>>(istream& os, Queue<T>& s) {

}*/
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
	return queue[(front+1) % capacity];
}

template <class T>
inline T& Queue<T>::Rear()
{
	if (IsEmpty()) throw "Queue is empty. No rear element";
	return queue[rear];
}

// doubling queue capacity - mid exam(+ template implementation)
template <class T>
void Queue<T>::Push(T const& x)
{
	// cout << "rear+1 : " << rear + 1 << ", capacity : " << capacity << ", rear : " << rear << endl;
	if ((rear+1) % capacity == 0 && rear != -1)
	{
		T* newQueue = new T[2 * capacity];
		// allocate an array with twice the capacity
		int start = (front + 1) % capacity;
		if (start < 2)
			//copy(queue + start, queue + start + capacity - 1, newQueue);
			memcpy(newQueue, queue, sizeof(T) * (start + capacity));
		else
		{
			//copy(queue + start, queue + capacity, newQueue);
			//copy(queue, queue + rear + 1, newQueue + capacity - start);
			memcpy(newQueue, queue + start, capacity);
			memcpy(newQueue + capacity - start, queue, rear + 1);
		}
		// switch to new Queue
		if (front != -1) front = 2 * capacity % capacity;
		rear = capacity - 1;
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
	queue[front].~T();
	front = (front + 1) % capacity;
	
}

void main()
{
	Queue<int> s(3);
	s.Push(2);
	s.Push(1);
	s.Push(4);
	s.Push(10); //�����ÿ� doubling ���� �������� �׽�Ʈ
	// cin >> s; //���� �ǽ�
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
	//cout << s << endl;//�����ϵ��� �ʿ��� �Լ��� �߰� �����Ѵ�
	system("pause");
}