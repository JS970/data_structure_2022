// source 5.4: Heap
#include <iostream>
#include <time.h>
#include <string>
using namespace std;

const int HeapSize = 1000;
enum Boolean { FALSE, TRUE };

template <class Type>
class Element
{
public:
	Type key;
	Element() { }
	Element(Type key) : key(key) { }
}; 

// Max Priority Queue
template <class Type>
class MaxPQ
{
public:
	virtual void Insert(const Element<Type>&) = 0;
	virtual Element<Type>* DeleteMax(Element<Type>&) = 0;
};

// Min Priority Queue
template <class Type>
class MinPQ
{
public:
	virtual void Insert(const Element<Type>&) = 0;
	virtual Element<Type>* DeleteMin(Element<Type>&) = 0;
};

// Max Heap
template <class Type>
class MaxHeap : public MaxPQ<Type>
{
public:
	MaxHeap(int sz = HeapSize)
	{
		MaxSize = sz; n = 0;
		heap = new Element<Type>[MaxSize + 1]; // Don't want to use heap[0]
	}
	void display();
	void Insert(const Element<Type>& x);
	Element<Type>* DeleteMax(Element<Type>& x);
private:
	Element<Type>* heap;
	int n; // current size of MaxHeap
	int MaxSize; // Maximum allowable size of MaxHeap
	void HeapEmpty() { cout << "Heap Empty" << endl; }
	void HeapFull() { cout << "Heap Full" << endl; }
};

template <class Type>
void MaxHeap<Type>::display()
{
	int i;
	cout << "MaxHeap:: (i, heap[i].key): ";
	for (i = 1; i <= n; i++) cout << "(" << i << ", " << heap[i].key << ") ";
	cout << endl;
}

template <class Type>
void MaxHeap<Type>::Insert(const Element<Type>& x)
{
	int i;
	if (n == MaxSize)
	{
		HeapFull();
		return;
	}
	n++;
	for (i = n; 1;)
	{
		if (i == 1) break; // at root
		if (x.key <= heap[i / 2].key) break;
		// move from parent to i
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = x;
}

template <class Type>
Element<Type>* MaxHeap<Type>::DeleteMax(Element<Type>& x)
{
	int i, j;
	if (!n) 
	{
		HeapEmpty();
		return 0;
	}
	x = heap[1];
	Element<Type> k = heap[n];
	n--;

	for (i = 1, j = 2; j <= n;)
	{
		if (j < n)
			if (heap[j].key < heap[j + 1].key) j++;
		// j points to the larger chile
		if (k.key >= heap[j].key) break;
		heap[i] = heap[j];
		i = j;
		j *= 2;
	}
	heap[i] = k;
	return &x;
}

// Min Heap
template <class Type>
class MinHeap : public MinPQ<Type>
{
public:
	MinHeap(int sz = HeapSize)
	{
		MaxSize = sz; n = 0;
		heap = new Element<Type>[MaxSize + 1]; // Don't want to use heap[0]
	}
	void display();
	void Insert(const Element<Type>& x);
	Element<Type>* DeleteMin(Element<Type>& x);
private:
	Element<Type>* heap;
	int n; // current size of MinHeap
	int MaxSize; // Minimum size of MinHeap
	void HeapEmpty() { cout << "Heap Empty" << endl; }
	void HeapFull() { cout << "Heap Full" << endl; }
};

template <class Type>
void MinHeap<Type>::display()
{
	int i;
	cout << "MinHeap:: (i, heap[i].key): ";
	for (i = 1; i <= n; i++) cout << "(" << i << ", " << heap[i].key << ") ";
	cout << endl;
}

template <class Type>
void MinHeap<Type>::Insert(const Element<Type>& x)
{
	int i;
	if (n == MaxSize)
	{
		HeapFull();
		return;
	}
	n++;
	for (i = n; 1;)
	{
		if (i == 1) break; // at root
		if (x.key <= heap[i / 2].key) break;
		// move from parent to i
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = x;
}

template <class Type>
Element<Type>* MinHeap<Type>::DeleteMin(Element<Type>& x)
{
	int i, j;
	if (!n)
	{
		HeapEmpty();
		return 0;
	}
	x = heap[1];
	Element<Type> k = heap[n];
	n--;

	for (i = 1, j = 2; j <= n;)
	{
		if (j < n)
			if (heap[j].key < heap[j + 1].key) j++;
		// j points to the larger chile
		if (k.key >= heap[j].key) break;
		heap[i] = heap[j];
		i = j;
		j *= 2;
	}
	heap[i] = k;
	return &x;
}

class Time
{
public:
	Time(int start = 0) { SimulationTime = start; }
	int CurrentTime() { return SimulationTime; }
	void TimePass(int passTime) { SimulationTime += passTime; }
	void TimePasssec() { SimulationTime += 1; }
	void TimePassmin() { SimulationTime += 60; }
private:
	int SimulationTime; // unit : second
};

// global time object
Time t = Time(0);

class AirPlane
{
public:
	AirPlane();
private:
	string airId;
	string airName;
	bool usingType;
	int planedTime;
	int remainingTime;
};

AirPlane::AirPlane()
{
	srand((unsigned int)time(NULL));
	int rnum = rand();
	
	// airID generation
	if (rnum % 2) airId = "KE";
	else airId = "AA";
	for (int i = 0; i < 3; i++)
	{
		string tmp = to_string(rnum % 899 + 100);
		airId.append(string(tmp));
	}

	// airName generation
	int i = rnum % 14;
	string plane[14] = { "BOEING727", "BOEING737", "BOEING 747", "BOEING757", "BOEING767"
					"BOEING777", "BOEING787",
					"A220", "A320", "A300", "A310", "A330", "A340", "A380" };
	airName = plane[i];

	// usingType configuration
	// usingType == false : landing plane
	// usingType == true : takeofof plane
	if (rnum % 2) usingType = false;
	else true;

	// planedTime configuration
	planedTime = rnum % 86400; // 86400 second == 24 hours

	// remainingTime configuration
	// remainingTime = planedtime - currenttime
	remainingTime = planedTime - t.CurrentTime();

}

int main()
{
	printf("time : %d\n", t.CurrentTime());
	t.TimePass(100);
	printf("time : %d\n", t.CurrentTime());

	return 0;
}