#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
const int HeapSize = 100;

template <class Type> class List;
template <class Type> class ListIterator;

template <class Type>
class ListNode
{
	friend class List<Type>;
	friend class ListIterator<Type>;
private:
	Type data;
	int weight;
	ListNode* link;
	ListNode(Type);
};

template <class Type>
ListNode<Type>::ListNode(Type Default)
{
	data = Default;
	// random weight for each nodes
	weight = rand();
	link = 0;
}

template <class Type>
class List
{
	friend class ListIterator<Type>;
public:
	List() { first = 0; }
	void Insert(Type);
	void Delete(Type);
private:
	ListNode<Type>* first;
};

template <class Type>
void List<Type>::Insert(Type k)
{
	ListNode<Type>* newnode = new ListNode<Type>(k);
	newnode->link = first;
	first = newnode;
}

template <class Type>
void List<Type>::Delete(Type k)
{
	ListNode<Type>* previous = 0;
	ListNode<Type>* current = first;
	for (current = first; current && current->data != k;
		previous = current, current = current->link);
	if (current)
	{
		if (previous) previous->link = current->link;
		else first = first->link;
		delete current;
	}
}

template <class Type>
class ListIterator
{
public:
	ListIterator(const List<Type>& l) : list(l) { current = l.first; }
	Type* First();
	int* FirstWeight();
	Type* Currentdata();
	Type* Next();
	int* NextWeight();
	bool NotNull();
	bool NextNotNull();
private:
	const List<Type>& list;
	ListNode<Type>* current;
};

// Don't confuse, this method only return current data
// Only Initial call could be first.data (or after cycle)
template <class Type>
Type* ListIterator<Type>::First()
{
	if (current) return &current->data;
	else return 0;
}

template <class Type>
int* ListIterator<Type>::FirstWeight()
{
	if (current) return &current->weight;
	else return 0;
}

template <class Type>
Type* ListIterator<Type>::Currentdata()
{
	return &current->data;
}

template <class Type>
Type* ListIterator<Type>::Next()
{
	current = current->link;
	return &current->data;
}

template <class Type>
int* ListIterator<Type>::NextWeight()
{
	current = current->link;
	return &current->weight;
}

template <class Type>
bool ListIterator<Type>::NotNull()
{
	if (current) return true;
	else return false;
}

template <class Type>
bool ListIterator<Type>::NextNotNull()
{
	if (current->link) return true;
	else return false;
}

// char type list '<<' operator overloading
ostream& operator<<(ostream& os, List<char>& l)
{
	ListIterator<char> li(l);
	if (!li.NotNull()) return os;
	os << *li.First() << endl;
	while (li.NextNotNull())
		os << *li.Next() << endl;
	return os;
}

class Queue;

class QueueNode
{
	friend class Queue;
private:
	int data;
	QueueNode* link;
	QueueNode(int def = 0, QueueNode* l = 0)
	{
		data = def;
		link = l;
	}
};

class Queue
{
public:
	Queue() { front = rear = 0; }
	void Insert(int);
	int* Delete(int&);
	bool IsEmpty() { if (front == 0) return true; else return false; }
private:
	QueueNode* front;
	QueueNode* rear;
	void QueueEmpty() { cout << "Queue Empty" << endl; }
};

void Queue::Insert(int y)
{
	if (front == 0) front = rear = new QueueNode(y, 0); // Empty queue
	else rear = rear->link = new QueueNode(y, 0); // update rear
}

int* Queue::Delete(int& retvalue)
{
	if (front == 0)
	{
		QueueEmpty();
		return 0;
	}
	QueueNode* x = front;
	retvalue = front->data;
	front = x->link;
	if (front == 0) rear = 0;

	delete x;
	return &retvalue;
}

class Graph
{
public:
	Graph(int vertices = 0) : n(vertices) { HeadNodes = new List<int>[n]; /* n linkedlists */ }
	void BFS(int);
	void InsertVertex(int startNode, int endNode);
	void displayAdjacencyLists();
	void DFS(int v);
	void KruskalMST(Graph* graph);
private:
	List<int>* HeadNodes; // int type linkedlist array
	int n; // number of node(vertices)
	bool* visited; // visited array
	void _DFS(const int v);
};

void Graph::displayAdjacencyLists()
{
	for (int i = 0; i < n; i++)
	{
		// HeadNodes linkedlist iterator
		ListIterator<int> iter(HeadNodes[i]);
		if (!iter.NotNull())
		{
			cout << i << " -> null" << endl;
			continue;
		}
		cout << i;
		for (int* first = iter.First(); iter.NotNull(); first = iter.Next())
			cout << " -> " << (*first);
		cout << endl;
	}
}

// Need to configure precisely...
// I understood abstactly (12/06)
void Graph::InsertVertex(int start, int end)
{
	if (start < 0 || start >= n || end < 0 || end >= n)
	{
		cout << "the start node number is out of bound.";
		throw "";
	}
	// check if already existed
	ListIterator<int> iter(HeadNodes[start]);
	for (int* first = iter.First(); iter.NotNull(); first = iter.Next())
		if (*first == end) return;

	HeadNodes[start].Insert(end);
	HeadNodes[end].Insert(start);
}

void Graph::BFS(int v)
{
	visited = new bool[n];
	for (int i = 0; i < n; i++)
		visited[i] = false;

	visited[v] = true;
	cout << v << ",";
	Queue q;
	q.Insert(v);

	while (!q.IsEmpty())
	{
		v = *q.Delete(v);
		ListIterator<int> li(HeadNodes[v]);
		if (!li.NotNull()) continue;
		int w = *li.First();
		while (1)
		{
			if (!visited[w])
			{
				q.Insert(w);
				visited[w] = true;
				cout << w << ",";
			}
			if (li.NextNotNull())
				w = *li.Next();
			else break;
		}
	}
	delete[] visited;
}

void Graph::DFS(int v)
{
	visited = new bool[n];
	for (int i = 0; i < n; i++)
		visited[i] = false;

	_DFS(v);
	delete[] visited;
}

void Graph::_DFS(const int v)
{
	visited[v] = true;
	cout << v << ", ";
	ListIterator<int> li(HeadNodes[v]);
	if (!li.NotNull()) return;
	int w = *li.First();
	while (1)
	{
		if (!visited[w]) _DFS(w);
		if (li.NextNotNull()) w = *li.Next();
		else return;
	}
}

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

void Graph::KruskalMST(Graph* graph)
{
	// maximum edges - fully connected graph
	int* edges = new int[n * n + 1];
	int j = 0; // edge index (containing cyclic edges either)
	for (int i = 0; i < n; i++)
	{
		ListIterator<int>* li = new ListIterator<int>(HeadNodes[i]);
		while (li->NotNull())
		{
			edges[j++] = *li->NextWeight();
		}
	}

	// MinHeap for select the lowest weight edge
	// Set partition generation(vertices)
	MinHeap<int>* mh = new MinHeap<int>();
	for (int i = 0; i < j; i++)
		mh->Insert(edges[i]);

	// Spanning Tree Generating...
	int vertexcount = 0;
	for (int i = 0; i < n; i++)
	{
		ListIterator<int>* li = new ListIterator<int>(HeadNodes[i]);
		while (li->NotNull())
		{
			int vertex;
			vertex = mh->DeleteMin(vertex);
		}
	}



}

int main(void)
{

	return 0;
}