#include <iostream>
#include <string>
using namespace std;

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
	Type* Next();
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
Type* ListIterator<Type>::Next()
{
	current = current->link;
	return &current->data;
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
		for(int *first = iter.First(); iter.NotNull(); first = iter.Next())
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

void Graph::KruskalMST(Graph* graph)
{
	// maximum edges - fully connected graph
	int* edges = new int(n*n);

}

int main(void)
{

	return 0;
}