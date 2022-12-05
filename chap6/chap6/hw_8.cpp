#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
const int HeapSize = 100;

template <class Type>
class Element
{
public:
	Type key;
	Element() { }
	Element(Type key) : key(key) { }
};

// Min Priority Queue
template <class Type>
class MinPQ
{
public:
	virtual void Insert(const Element<Type>&) = 0;
	virtual Element<Type>* DeleteMin(Element<Type>&) = 0;
};

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
		if (x.key >= heap[i / 2].key) break;
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
			if (heap[j].key > heap[j + 1].key) j++;
		// j points to the smaller child
		if (k.key <= heap[j].key) break;
		heap[i] = heap[j];
		i = j;
		j *= 2;
	}
	heap[i] = k;
	return &x;
}

class Sets
{
public:
	Sets(int);
	void display();
	void SimpleUnion(int, int);
	int SimpleFind(int);
	void WeightedUnion(int, int);
	int CollapsingFind(int);
private:
	int* parent;
	int n;
};

Sets::Sets(int sz = HeapSize)
{
	n = sz;
	parent = new int[sz + 1]; // Don't want to use parent[0]
	for (int i = 1; i <= n; i++)
		parent[i] = -1;
}

// Replace the disjoint sets with roots i and j, i != j with their union
void Sets::SimpleUnion(int i, int j)
{
	parent[j] = i;
}

// Find the root of the tree containing element i
int Sets::SimpleFind(int i)
{
	while (parent[i] > 0) i = parent[i];
	return i;
}

void Sets::WeightedUnion(int i, int j)
{
	int temp = parent[i] + parent[j];
	if (parent[i] > parent[j])
	{
		// i has fewer nodes
		parent[i] = j;
		parent[j] = temp;
	}
	else
	{
		// j has fewer nodes
		parent[j] = i;
		parent[i] = temp;
	}
}

int Sets::CollapsingFind(int i)
{
	int r;
	for (r = i; parent[r] > 0; r = parent[r]); // find root
	while (i != r)
	{
		int s = parent[i];
		parent[i] = r;
		i = s;
	}
	return r;
}

void Sets::display()
{
	cout << "display:index=  ";
	for (int i = 1; i <= n; i++) printf("%2d ", i);
	cout << endl;
	cout << "display: value= ";
	for (int i = 1; i <= n; i++) printf("%2d ", parent[i]);
	cout << endl;
}

int main(void)
{

	return 0;
}